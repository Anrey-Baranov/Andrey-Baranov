#include <gtest.h>
#include "../lib_pair/TPair.h"
#include "../lib_hash_tables/open_addressing_hash_table.h"
#include "../lib_hash_tables/open_addressing_hash_table.cpp"

class OpenAddressingHashTableTest : public ::testing::Test {
protected:
    OpenAddressingHashTable<std::string, int> table;

    void SetUp() override {
        table = OpenAddressingHashTable<std::string, int>(8);  
    }

    void TearDown() override {
        // Очистка после каждого теста
    }
};

TEST_F(OpenAddressingHashTableTest, InitialState) {
    OpenAddressingHashTable<std::string, int> newTable(4); // Явное указание размера
    EXPECT_EQ(newTable.size(), 0);
    EXPECT_TRUE(newTable.empty());
}

TEST_F(OpenAddressingHashTableTest, InsertAndFind) {
    table.insert("one", 1);
    table.insert("two", 2);
    int value;
    EXPECT_TRUE(table.find("one", value));
    EXPECT_EQ(value, 1);
    EXPECT_TRUE(table.find("two", value));
    EXPECT_EQ(value, 2);
    EXPECT_EQ(table.size(), 2);
}


TEST_F(OpenAddressingHashTableTest, InsertDuplicateThrows) {
    table.insert("one", 1);
    EXPECT_THROW(table.insert("one", 2), std::runtime_error);
}

TEST_F(OpenAddressingHashTableTest, FindNonExistent) {
    int value;
    EXPECT_FALSE(table.find("none", value));
}

TEST_F(OpenAddressingHashTableTest, RemoveExisting) {
    table.insert("one", 1);
    EXPECT_TRUE(table.remove("one"));
    EXPECT_EQ(table.size(), 0);

    int value;
    EXPECT_FALSE(table.find("one", value));
}

TEST_F(OpenAddressingHashTableTest, RemoveNonExistent) {
    EXPECT_FALSE(table.remove("none"));
}

TEST_F(OpenAddressingHashTableTest, RehashWhenFull) {
    // Проверяем, что таблица корректно расширяется
    size_t old_capacity = table.size();
    table.insert("three", 3);
    table.insert("four", 4);
    EXPECT_GT(table.size(), old_capacity);

    int value;
    EXPECT_TRUE(table.find("one", value));
    EXPECT_TRUE(table.find("two", value));
    EXPECT_TRUE(table.find("three", value));
    EXPECT_TRUE(table.find("four", value));
}

TEST_F(OpenAddressingHashTableTest, HandleCollisions) {
    OpenAddressingHashTable<int, int> smallTable(4);

    smallTable.insert(1, 100);
    smallTable.insert(5, 500); // Должен вызвать коллизию с 1 (если hash(1) == hash(5) % 4)

    int value;
    EXPECT_TRUE(smallTable.find(1, value));
    EXPECT_EQ(value, 100);
    EXPECT_TRUE(smallTable.find(5, value));
    EXPECT_EQ(value, 500);
}

TEST_F(OpenAddressingHashTableTest, RemoveAndReuseDeletedSlot) {
    table.insert("one", 1);
    table.insert("two", 2);
    table.remove("one");

    // Проверяем, что слот освободился и можно вставить новый элемент
    table.insert("three", 3);

    int value;
    EXPECT_TRUE(table.find("three", value));
    EXPECT_EQ(value, 3);
    EXPECT_FALSE(table.find("one", value));
}

TEST_F(OpenAddressingHashTableTest, PrintEmptyTable) {
    testing::internal::CaptureStdout();
    table.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.empty());
}

TEST_F(OpenAddressingHashTableTest, PrintNonEmptyTable) {
    table.insert("one", 1);
    table.insert("two", 2);

    testing::internal::CaptureStdout();
    table.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("one"), std::string::npos);
    EXPECT_NE(output.find("two"), std::string::npos);
}

TEST_F(OpenAddressingHashTableTest, TableFullException) {
    OpenAddressingHashTable<int, int> tinyTable(1);
    tinyTable.insert(1, 100);
    EXPECT_THROW(tinyTable.insert(2, 200), std::runtime_error);
}

TEST_F(OpenAddressingHashTableTest, ComplexOperations) {
    // Комплексный тест с последовательностью операций
    table.insert("a", 1);
    table.insert("b", 2);
    table.insert("c", 3);
    table.remove("b");
    table.insert("d", 4);

    int value;
    EXPECT_TRUE(table.find("a", value));
    EXPECT_EQ(value, 1);
    EXPECT_FALSE(table.find("b", value));
    EXPECT_TRUE(table.find("c", value));
    EXPECT_EQ(value, 3);
    EXPECT_TRUE(table.find("d", value));
    EXPECT_EQ(value, 4);
    EXPECT_EQ(table.size(), 3);
}