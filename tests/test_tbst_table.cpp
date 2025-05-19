#include "gtest.h"
#include "TBSTTable.h"

template class TBSTTable<int, int>;

class TBSTTablePrivateTest : public ::testing::Test {
protected:
    TBSTTable<int, int> table;

    void SetUp() override {
        table.insert(50, 500);
        table.insert(30, 300);
        table.insert(70, 700);
    }
};

TEST_F(TBSTTablePrivateTest, InsertAndFind) {
    int value;
    EXPECT_TRUE(table.find(50, value));
    EXPECT_EQ(value, 500);
    EXPECT_TRUE(table.find(30, value));
    EXPECT_EQ(value, 300);
    EXPECT_FALSE(table.find(10, value));
}

TEST_F(TBSTTablePrivateTest, Erase) {
    EXPECT_TRUE(table.erase(30));
    int value;
    EXPECT_FALSE(table.find(30, value));
    EXPECT_TRUE(table.find(50, value));

    EXPECT_FALSE(table.erase(100)); // Несуществующий ключ
}

TEST_F(TBSTTablePrivateTest, Clear) {
    table.clear();
    int value;
    EXPECT_FALSE(table.find(50, value));
    EXPECT_TRUE(table.empty());
}

TEST_F(TBSTTablePrivateTest, EmptyAndSize) {
    EXPECT_FALSE(table.empty());
    EXPECT_EQ(table.size(), 3);

    table.clear();
    EXPECT_TRUE(table.empty());
    EXPECT_EQ(table.size(), 0);
}

TEST_F(TBSTTablePrivateTest, Iterator) {
    std::vector<std::pair<int, int>> expected = {
        {30, 300}, {50, 500}, {70, 700}
    };

    size_t i = 0;
    for (auto it = table.begin(); it != table.end(); ++it) {
        auto pair = *it;
        EXPECT_EQ(pair.first, expected[i].first);
        EXPECT_EQ(pair.second, expected[i].second);
        i++;
    }
    EXPECT_EQ(i, expected.size());
}

class TBSTTableTest : public ::testing::Test {
protected:
    TBSTTable<int, int> table;

    void SetUp() override {
        table.insert(50, 500);
        table.insert(30, 300);
        table.insert(70, 700);
        table.insert(20, 200);
        table.insert(40, 400);
        table.insert(60, 600);
        table.insert(80, 800);
    }
};

TEST_F(TBSTTableTest, InitialState) {
    TBSTTable<int, int> emptyTable;
    int value;
    EXPECT_FALSE(emptyTable.find(10, value));
    EXPECT_TRUE(emptyTable.empty());
}

TEST_F(TBSTTableTest, InsertAndFind) {
    int value;
    EXPECT_TRUE(table.find(50, value));
    EXPECT_EQ(value, 500);
    EXPECT_TRUE(table.find(30, value));
    EXPECT_EQ(value, 300);
    EXPECT_FALSE(table.find(90, value));
}

TEST_F(TBSTTableTest, EraseLeafNode) {
    EXPECT_TRUE(table.erase(20));
    int value;
    EXPECT_FALSE(table.find(20, value));
    EXPECT_TRUE(table.find(30, value));

    EXPECT_TRUE(table.erase(80));
    EXPECT_FALSE(table.find(80, value));
    EXPECT_TRUE(table.find(70, value));
}

TEST_F(TBSTTableTest, EraseNodeWithOneChild) {
    table.erase(20);
    EXPECT_TRUE(table.erase(30));
    int value;
    EXPECT_FALSE(table.find(30, value));
    EXPECT_TRUE(table.find(40, value));
    EXPECT_TRUE(table.find(50, value));
}

TEST_F(TBSTTableTest, EraseNodeWithTwoChildren) {
    EXPECT_TRUE(table.erase(50));
    int value;
    EXPECT_FALSE(table.find(50, value));
    EXPECT_TRUE(table.find(60, value));
    EXPECT_TRUE(table.find(30, value));
    EXPECT_TRUE(table.find(70, value));
}

TEST_F(TBSTTableTest, ClearTable) {
    table.clear();
    int value;
    EXPECT_FALSE(table.find(50, value));
    EXPECT_TRUE(table.empty());

    table.insert(100, 1000);
    EXPECT_TRUE(table.find(100, value));
    EXPECT_EQ(value, 1000);
}

TEST_F(TBSTTableTest, IteratorTraversal) {
    std::vector<std::pair<int, int>> expected = {
        {20, 200}, {30, 300}, {40, 400}, {50, 500},
        {60, 600}, {70, 700}, {80, 800}
    };

    size_t i = 0;
    for (auto it = table.begin(); it != table.end(); ++it) {
        auto pair = *it;
        EXPECT_EQ(pair.first, expected[i].first);
        EXPECT_EQ(pair.second, expected[i].second);
        i++;
    }
    EXPECT_EQ(i, expected.size());
}

TEST_F(TBSTTableTest, DuplicateInsert) {
    table.insert(50, 501); // Обновление значения
    int value;
    EXPECT_TRUE(table.find(50, value));
    EXPECT_EQ(value, 501); // Проверяем, что значение обновилось
}

TEST_F(TBSTTableTest, ComplexOperations) {
    TBSTTable<int, int> bigTable;
    for (int i = 0; i < 100; ++i) {
        bigTable.insert(i, i * 10);
    }

    int value;
    EXPECT_TRUE(bigTable.find(0, value));
    EXPECT_EQ(value, 0);
    EXPECT_TRUE(bigTable.find(99, value));
    EXPECT_EQ(value, 990);

    for (int i = 0; i < 100; i += 2) {
        bigTable.erase(i);
    }

    for (int i = 0; i < 100; ++i) {
        if (i % 2 == 0) {
            EXPECT_FALSE(bigTable.find(i, value));
        }
        else {
            EXPECT_TRUE(bigTable.find(i, value));
            EXPECT_EQ(value, i * 10);
        }
    }

    bigTable.clear();
    EXPECT_TRUE(bigTable.empty());
}

TEST_F(TBSTTableTest, StringKeys) {
    TBSTTable<std::string, int> stringTable;
    stringTable.insert("apple", 1);
    stringTable.insert("banana", 2);
    stringTable.insert("cherry", 3);

    int value;
    EXPECT_TRUE(stringTable.find("banana", value));
    EXPECT_EQ(value, 2);
    EXPECT_FALSE(stringTable.find("orange", value));

    stringTable.erase("banana");
    EXPECT_FALSE(stringTable.find("banana", value));
}

TEST_F(TBSTTableTest, EmptyTableOperations) {
    TBSTTable<int, int> emptyTable;
    int value;
    EXPECT_FALSE(emptyTable.find(10, value));
    EXPECT_TRUE(emptyTable.empty());
    EXPECT_FALSE(emptyTable.erase(10)); // Удаление несуществующего ключа
    EXPECT_EQ(emptyTable.size(), 0);

    // Проверка итераторов на пустой таблице
    for (auto it = emptyTable.begin(); it != emptyTable.end(); ++it) {
        FAIL() << "Should not iterate empty table";
    }
}