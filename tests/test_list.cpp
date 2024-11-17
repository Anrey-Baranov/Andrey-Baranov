#include <gtest.h>
#include "../lib_list/TList.h"  // Убедитесь, что путь к заголовочному файлу правильный

class TestListLib : public ::testing::Test {
protected:
    TList<int> list1;
    TList<int> list2;

    void SetUp() override {
        list1.pushBack(1);
        list1.pushBack(2);
        list1.pushBack(3);
        list2.pushBack(4);
        list2.pushBack(5);
    }
};

TEST_F(TestListLib, CheckIsEmptyInitially) {
    TList<int> emptyList;
    EXPECT_TRUE(emptyList.isEmpty());
}

TEST_F(TestListLib, CheckPushFront) {
    list1.pushFront(0);
    EXPECT_EQ(list1.getNode(0)->getValue(), 0);
}

TEST_F(TestListLib, CheckPushBack) {
    list1.pushBack(4);
    EXPECT_EQ(list1.getNode(3)->getValue(), 4);
}

TEST_F(TestListLib, CheckRemoveFirst) {
    list1.removeFirst();
    EXPECT_EQ(list1.getNode(0)->getValue(), 2);
}

TEST_F(TestListLib, CheckRemoveLast) {
    list1.removeLast();
    EXPECT_EQ(list1.getNode(1)->getValue(), 2);
}

TEST_F(TestListLib, CheckInsert) {
    list1.insert(4, 1);  // Вставляем 4 на индекс 1
    EXPECT_EQ(list1.getNode(1)->getValue(), 4);
}

TEST_F(TestListLib, CheckFindExistingValue) {
    EXPECT_NE(list1.find(2), nullptr);
}

TEST_F(TestListLib, CheckFindNonExistingValue) {
    EXPECT_EQ(list1.find(5), nullptr);
}

TEST_F(TestListLib, CheckRemoveByIndex) {
    list1.removeBy(1);  // Удаляем элемент по индексу 1
    EXPECT_EQ(list1.getNode(1)->getValue(), 3);
}

TEST_F(TestListLib, CheckReplaceNode) {
    TNode<int>* node = list1.getNode(1);
    list1.replaceNode(node, 5);  // Заменяем значение на 5
    EXPECT_EQ(list1.getNode(1)->getValue(), 5);
}

TEST_F(TestListLib, CheckReplaceByIndex) {
    list1.replaceBy(1, 6);  // Заменяем значение по индексу 1
    EXPECT_EQ(list1.getNode(1)->getValue(), 6);
}

TEST_F(TestListLib, CheckClear) {
    list1.clear();
    EXPECT_TRUE(list1.isEmpty());
}

TEST_F(TestListLib, CheckCopyConstructor) {
    TList<int> copy(list1);
    EXPECT_EQ(copy.getNode(0)->getValue(), 1);
    EXPECT_EQ(copy.getNode(1)->getValue(), 2);
}

TEST_F(TestListLib, CheckAssignmentOperator) {
    TList<int> copy;
    copy = list1;
    EXPECT_EQ(copy.getNode(2)->getValue(), 3);
}

