//#include "gtest.h"
//#include "../lib_hash_tables/open_addressing_hash_table.h"
//#include <string>
//
//class TestOpenHashTable : public ::testing::Test {
//protected:
//    TOpenHashTable<std::string, int> table;
//};
//
//TEST_F(TestOpenHashTable, InsertAndFindBasic) {
//    table.insert("one", 1);
//    table.insert("two", 2);
//
//    int value;
//    EXPECT_TRUE(table.find("one", value));
//    EXPECT_EQ(value, 1);
//
//    EXPECT_TRUE(table.find("two", value));
//    EXPECT_EQ(value, 2);
//
//    EXPECT_FALSE(table.find("three", value));
//}
//
//TEST_F(TestOpenHashTable, InsertDuplicateThrows) {
//    table.insert("key", 10);
//    EXPECT_THROW(table.insert("key", 20), std::runtime_error);
//}
//
//TEST_F(TestOpenHashTable, RemoveExistingElement) {
//    table.insert("to_remove", 99);
//    EXPECT_TRUE(table.remove("to_remove"));
//    EXPECT_FALSE(table.remove("to_remove")); // Повторное удаление
//
//    int value;
//    EXPECT_FALSE(table.find("to_remove", value));
//}
//
//TEST_F(TestOpenHashTable, AutoRehashWhenFull) {
//    // Вставка достаточного количества элементов для срабатывания rehash
//    for (int i = 0; i < 20; ++i) {
//        table.insert("key_" + std::to_string(i), i);
//    }
//
//    // Проверка, что все элементы доступны после rehash
//    int value;
//    for (int i = 0; i < 20; ++i) {
//        EXPECT_TRUE(table.find("key_" + std::to_string(i), value));
//        EXPECT_EQ(value, i);
//    }
//}
//
//TEST_F(TestOpenHashTable, SizeChangesCorrectly) {
//    EXPECT_EQ(table.size(), 0);
//
//    table.insert("first", 1);
//    EXPECT_EQ(table.size(), 1);
//
//    table.insert("second", 2);
//    EXPECT_EQ(table.size(), 2);
//
//    table.remove("first");
//    EXPECT_EQ(table.size(), 1);
//
//    table.remove("second");
//    EXPECT_EQ(table.size(), 0);
//}
//
//TEST_F(TestOpenHashTable, EmptyTableBehavior) {
//    EXPECT_TRUE(table.empty());
//
//    table.insert("item", 123);
//    EXPECT_FALSE(table.empty());
//
//    table.remove("item");
//    EXPECT_TRUE(table.empty());
//}
//
//TEST_F(TestOpenHashTable, CollisionHandling) {
//    // Тестирование обработки коллизий
//    table.insert("abc", 1);
//    table.insert("bca", 2); // Возможная коллизия
//
//    int value;
//    EXPECT_TRUE(table.find("abc", value));
//    EXPECT_EQ(value, 1);
//
//    EXPECT_TRUE(table.find("bca", value));
//    EXPECT_EQ(value, 2);
//}
