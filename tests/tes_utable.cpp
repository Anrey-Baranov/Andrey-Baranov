#include "gtest.h"
#include "../lib_unsort_tabel/UTable.h"
#include <stdexcept>

template class TUnsortedTable<int, std::string>;
//template class TUnsortedTable<std::string, double>;

class TUnsortedTableTest : public ::testing::Test {
protected:
    TUnsortedTable<int, std::string> table;
    TUnsortedTable<int, int> intTable;

    void SetUp() override {
        // Начальная инициализация для некоторых тестов
        table.insert(1, "one");
        table.insert(2, "two");
        table.insert(3, "three");
    }

    void TearDown() override {
        // Очистка после каждого теста
        table.erase(1);
        table.erase(2);
        table.erase(3);
    }
};

TEST_F(TUnsortedTableTest, DefaultConstructor) {
    TUnsortedTable<int, std::string> newTable;
    EXPECT_EQ(newTable.size(), 0);
}

TEST_F(TUnsortedTableTest, InsertWithGeneratedKey) {
    std::string value = "test_value";
    int key = table.insert(value);  // Явно указываем тип int для ключа
    EXPECT_GT(key, 0);
    EXPECT_EQ(table.find(key), value);
}

TEST_F(TUnsortedTableTest, InsertWithExistingKeyUpdatesValue) {
    // Проверяем исходное значение
    EXPECT_EQ(table.find(1), "one");

    // Обновляем значение
    table.insert(1, "updated_one");

    // Проверяем обновление
    EXPECT_EQ(table.find(1), "updated_one");

    // Проверяем что другие значения не изменились
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(3), "three");
}

TEST_F(TUnsortedTableTest, InsertWithNewKeyAddsElement) {
    size_t initialSize = table.size();
    table.insert(4, "four");

    EXPECT_EQ(table.size(), initialSize + 1);
    EXPECT_EQ(table.find(4), "four");
}

TEST_F(TUnsortedTableTest, EraseExistingKey) {
    size_t initialSize = table.size();
    table.erase(2);

    EXPECT_EQ(table.size(), initialSize - 1);
    EXPECT_THROW(table.find(2), std::logic_error);

    // Проверяем что другие элементы остались
    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(3), "three");
}

TEST_F(TUnsortedTableTest, EraseNonExistingKeyThrows) {
    EXPECT_THROW(table.erase(999), std::logic_error);
}

TEST_F(TUnsortedTableTest, EraseFromEmptyTableThrows) {
    TUnsortedTable<int, std::string> emptyTable;
    EXPECT_THROW(emptyTable.erase(1), std::logic_error);
}

TEST_F(TUnsortedTableTest, FindExistingKey) {
    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(3), "three");
}

TEST_F(TUnsortedTableTest, FindNonExistingKeyThrows) {
    EXPECT_THROW(table.find(999), std::logic_error);
}

TEST_F(TUnsortedTableTest, FindInEmptyTableThrows) {
    TUnsortedTable<int, std::string> emptyTable;
    EXPECT_THROW(emptyTable.find(1), std::logic_error);
}

TEST_F(TUnsortedTableTest, SizeReturnsCorrectValue) {
    EXPECT_EQ(table.size(), 3);

    table.insert(4, "four");
    EXPECT_EQ(table.size(), 4);

    table.erase(1);
    EXPECT_EQ(table.size(), 3);

    TUnsortedTable<int, std::string> emptyTable;
    EXPECT_EQ(emptyTable.size(), 0);
}

TEST_F(TUnsortedTableTest, GenerateKeyProducesIncrementingValues) {
    TUnsortedTable<int, int> newTable;
    int key1 = newTable.generate_key();  // Явно указываем тип int для ключа
    int key2 = newTable.generate_key();
    int key3 = newTable.generate_key();

    EXPECT_EQ(key2, key1 + 1);
    EXPECT_EQ(key3, key2 + 1);
}

TEST_F(TUnsortedTableTest, MultipleInsertAndEraseOperations) {
    TUnsortedTable<int, std::string> testTable;

    // Добавляем несколько элементов
    testTable.insert(1, "first");
    testTable.insert(2, "second");
    testTable.insert(3, "third");

    EXPECT_EQ(testTable.size(), 3);

    // Обновляем значение
    testTable.insert(2, "updated_second");
    EXPECT_EQ(testTable.find(2), "updated_second");
    EXPECT_EQ(testTable.size(), 3); // Размер не должен измениться

    // Удаляем элемент
    testTable.erase(1);
    EXPECT_EQ(testTable.size(), 2);
    EXPECT_THROW(testTable.find(1), std::logic_error);

    // Добавляем новый элемент
    testTable.insert(4, "fourth");
    EXPECT_EQ(testTable.size(), 3);
    EXPECT_EQ(testTable.find(4), "fourth");

    // Удаляем все оставшиеся элементы
    testTable.erase(2);
    testTable.erase(3);
    testTable.erase(4);

    EXPECT_EQ(testTable.size(), 0);
    EXPECT_THROW(testTable.find(2), std::logic_error);
    EXPECT_THROW(testTable.find(3), std::logic_error);
    EXPECT_THROW(testTable.find(4), std::logic_error);
}

TEST_F(TUnsortedTableTest, StressTest) {
    TUnsortedTable<int, int> stressTable;
    const int COUNT = 1000;

    // Добавляем много элементов
    for (int i = 0; i < COUNT; ++i) {
        stressTable.insert(i, i * 10);
    }

    EXPECT_EQ(stressTable.size(), COUNT);

    // Проверяем все элементы
    for (int i = 0; i < COUNT; ++i) {
        EXPECT_EQ(stressTable.find(i), i * 10);
    }

    // Удаляем половину элементов
    for (int i = 0; i < COUNT; i += 2) {
        stressTable.erase(i);
    }

    EXPECT_EQ(stressTable.size(), COUNT / 2);

    // Проверяем оставшиеся элементы
    for (int i = 1; i < COUNT; i += 2) {
        EXPECT_EQ(stressTable.find(i), i * 10);
    }

    // Проверяем что удаленные элементы отсутствуют
    for (int i = 0; i < COUNT; i += 2) {
        EXPECT_THROW(stressTable.find(i), std::logic_error);
    }
}

TEST_F(TUnsortedTableTest, CopyConstructor) {
    // Создаем копию таблицы
    TUnsortedTable<int, std::string> copiedTable(table);

    // Проверяем что размер совпадает
    EXPECT_EQ(copiedTable.size(), table.size());

    // Проверяем что все элементы скопированы
    EXPECT_EQ(copiedTable.find(1), "one");
    EXPECT_EQ(copiedTable.find(2), "two");
    EXPECT_EQ(copiedTable.find(3), "three");

    // Модифицируем оригинальную таблицу
    table.insert(4, "four");

    // Проверяем что копия не изменилась
    EXPECT_EQ(copiedTable.size(), 3);
    EXPECT_THROW(copiedTable.find(4), std::logic_error);
}

TEST_F(TUnsortedTableTest, AssignmentOperator) {
    TUnsortedTable<int, std::string> assignedTable;
    assignedTable.insert(10, "ten");

    // Присваиваем таблицу
    assignedTable = table;

    // Проверяем что размер совпадает
    EXPECT_EQ(assignedTable.size(), table.size());

    // Проверяем что старые элементы заменены
    EXPECT_THROW(assignedTable.find(10), std::logic_error);

    // Проверяем что все элементы скопированы
    EXPECT_EQ(assignedTable.find(1), "one");
    EXPECT_EQ(assignedTable.find(2), "two");
    EXPECT_EQ(assignedTable.find(3), "three");

    // Модифицируем оригинальную таблицу
    table.insert(4, "four");

    // Проверяем что присвоенная таблица не изменилась
    EXPECT_EQ(assignedTable.size(), 3);
    EXPECT_THROW(assignedTable.find(4), std::logic_error);
}