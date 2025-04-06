//#include "gtest.h"
//#include "../lib_hash_tables/chaining_hash_table.h"
//#include <string>
//
//class TestChainHashTable : public ::testing::Test {
//protected:
//    TChainHashTable<std::string, int> table;
//};
//
//TEST_F(TestChainHashTable, BasicInsertAndFind) {
//    table.insert("apple", 10);
//    table.insert("banana", 20);
//
//    int value;
//    EXPECT_TRUE(table.find("apple", value));
//    EXPECT_EQ(value, 10);
//
//    EXPECT_TRUE(table.find("banana", value));
//    EXPECT_EQ(value, 20);
//
//    EXPECT_FALSE(table.find("orange", value));
//}
//
//TEST_F(TestChainHashTable, DuplicateKeyThrowsException) {
//    table.insert("unique", 100);
//    EXPECT_THROW(table.insert("unique", 200), std::runtime_error);
//}
//
//TEST_F(TestChainHashTable, RemoveOperations) {
//    table.insert("temp", 33);
//    EXPECT_TRUE(table.remove("temp"));
//
//    int value;
//    EXPECT_FALSE(table.find("temp", value));
//    EXPECT_FALSE(table.remove("temp")); // Удаление несуществующего
//}
//
//TEST_F(TestChainHashTable, RehashWhenLoadFactorHigh) {
//    // Вставка элементов для проверки автоматического rehash
//    for (int i = 0; i < 30; ++i) {
//        table.insert("item_" + std::to_string(i), i * 2);
//    }
//
//    // Проверка доступности всех элементов
//    int value;
//    for (int i = 0; i < 30; ++i) {
//        EXPECT_TRUE(table.find("item_" + std::to_string(i), value));
//        EXPECT_EQ(value, i * 2);
//    }
//}
//
//TEST_F(TestChainHashTable, SizeManagement) {
//    EXPECT_EQ(table.size(), 0);
//
//    table.insert("a", 1);
//    table.insert("b", 2);
//    EXPECT_EQ(table.size(), 2);
//
//    table.remove("a");
//    EXPECT_EQ(table.size(), 1);
//
//    table.remove("b");
//    EXPECT_EQ(table.size(), 0);
//}
//
//TEST_F(TestChainHashTable, EmptyTableOperations) {
//    EXPECT_TRUE(table.empty());
//
//    table.insert("test", 123);
//    EXPECT_FALSE(table.empty());
//
//    table.remove("test");
//    EXPECT_TRUE(table.empty());
//}
//
//TEST_F(TestChainHashTable, MultipleCollisions) {
//    // Проверка работы с множественными коллизиями
//    for (int i = 0; i < 10; ++i) {
//        table.insert(std::to_string(i), i);
//    }
//
//    // Проверка всех вставленных значений
//    int value;
//    for (int i = 0; i < 10; ++i) {
//        EXPECT_TRUE(table.find(std::to_string(i), value));
//        EXPECT_EQ(value, i);
//    }
//}
//
//TEST_F(TestChainHashTable, LongChainHandling) {
//    // Создание длинной цепочки в одной корзине
//    for (int i = 0; i < 15; ++i) {
//        table.insert("collision_" + std::to_string(i), i);
//    }
//
//    // Проверка всех элементов в длинной цепочке
//    int value;
//    for (int i = 0; i < 15; ++i) {
//        EXPECT_TRUE(table.find("collision_" + std::to_string(i), value));
//        EXPECT_EQ(value, i);
//    }
//}
