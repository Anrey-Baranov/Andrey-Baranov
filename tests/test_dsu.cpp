#include <gtest.h>
#include "dsu.h"

class TestDSU : public ::testing::Test {
protected:
    DSU dsu;

    TestDSU() : dsu(6) {  // Создаем DSU с 6 элементами
        dsu.make_set(1);
        dsu.make_set(2);
        dsu.make_set(3);
        dsu.make_set(4);
        dsu.make_set(5);
        dsu.make_set(6);
    }
};

TEST_F(TestDSU, TestMakeSet) {
    EXPECT_NO_THROW(dsu.make_set(5)); // Проверяем создание множества для существующего элемента
    EXPECT_NO_THROW(dsu.make_set(7)); // Проверяем создание нового множества
}

TEST_F(TestDSU, TestFind) {
    EXPECT_EQ(dsu.find(1), 1); // Проверяем, что элемент 1 указывает на себя
    EXPECT_EQ(dsu.find(2), 2); // Проверяем, что элемент 2 указывает на себя
}

TEST_F(TestDSU, TestUnion) {
    dsu.union_sets(1, 2); // Объединяем 1 и 2
    EXPECT_EQ(dsu.find(1), dsu.find(2)); // Проверяем, что 1 и 2 теперь в одном множестве

    dsu.union_sets(3, 4); // Объединяем 3 и 4
    EXPECT_EQ(dsu.find(3), dsu.find(4)); // Проверяем, что 3 и 4 теперь в одном множестве

    dsu.union_sets(2, 3); // Объединяем 2 и 3
    EXPECT_EQ(dsu.find(1), dsu.find(3)); // Проверяем, что 1 и 3 теперь в одном множестве
}

TEST_F(TestDSU, TestUnionDifferentSets) {
    dsu.union_sets(1, 2);
    dsu.union_sets(3, 4);
    EXPECT_NE(dsu.find(1), dsu.find(3)); // Проверяем, что 1 и 3 все еще в разных множествах
}

TEST_F(TestDSU, TestInvalidFind) {
    EXPECT_THROW(dsu.find(0), std::logic_error); // Проверка на выход за границы
    EXPECT_THROW(dsu.find(7), std::logic_error); // Проверка на выход за границы
}

TEST_F(TestDSU, TestInvalidUnion) {
    EXPECT_THROW(dsu.union_sets(0, 1), std::logic_error); // Проверка на выход за границы
    EXPECT_THROW(dsu.union_sets(1, 7), std::logic_error); // Проверка на выход за границы
}

TEST_F(TestDSU, TestMakeSetOutOfBounds) {
    EXPECT_THROW(dsu.make_set(0), std::logic_error); // Проверка на выход за границы
    EXPECT_THROW(dsu.make_set(7), std::logic_error); // Проверка на выход за границы
}
