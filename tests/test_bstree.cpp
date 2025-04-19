#include "gtest.h"
#include "../lib_bstree/TBinSearchTree.h" 

class BinarySearchTreeTest : public ::testing::Test {
protected:
    BSearchTree<int> tree;

    void SetUp() override {
        // Построим тестовое дерево:
        //       50
        //     /    \
        //    30     70
        //   /  \   /  \
        // 20   40 60   80
        tree.insert(50);
        tree.insert(30);
        tree.insert(70);
        tree.insert(20);
        tree.insert(40);
        tree.insert(60);
        tree.insert(80);
    }
};

TEST_F(BinarySearchTreeTest, InitialState) {
    BSearchTree<int> emptyTree;
    EXPECT_EQ(emptyTree.search(10), nullptr);
    EXPECT_EQ(emptyTree.min(), nullptr);
    EXPECT_EQ(emptyTree.max(), nullptr);
}

TEST_F(BinarySearchTreeTest, InsertAndSearch) {
    EXPECT_NE(tree.search(50), nullptr);
    EXPECT_EQ(tree.search(50)->_value, 50);

    EXPECT_NE(tree.search(30), nullptr);
    EXPECT_EQ(tree.search(30)->_value, 30);

    EXPECT_EQ(tree.search(90), nullptr); // Проверка несуществующего элемента
}

TEST_F(BinarySearchTreeTest, MinMaxOperations) {
    EXPECT_NE(tree.min(), nullptr);
    EXPECT_EQ(tree.min()->_value, 20);

    EXPECT_NE(tree.max(), nullptr);
    EXPECT_EQ(tree.max()->_value, 80);

    tree.insert(10);
    EXPECT_EQ(tree.min()->_value, 10);

    tree.insert(100);
    EXPECT_EQ(tree.max()->_value, 100);
}

TEST_F(BinarySearchTreeTest, EraseLeafNode) {
    tree.erase(20);
    EXPECT_EQ(tree.search(20), nullptr);
    EXPECT_NE(tree.search(30), nullptr); // Родитель должен остаться

    tree.erase(80);
    EXPECT_EQ(tree.search(80), nullptr);
    EXPECT_NE(tree.search(70), nullptr);
}

TEST_F(BinarySearchTreeTest, EraseNodeWithOneChild) {
    // Создаем ситуацию с одним потомком
    tree.erase(20);
    tree.erase(30); // Теперь у 30 только правый потомок (40)

    EXPECT_EQ(tree.search(30), nullptr);
    EXPECT_NE(tree.search(40), nullptr);
    EXPECT_NE(tree.search(50), nullptr);
}

TEST_F(BinarySearchTreeTest, EraseNodeWithTwoChildren) {
    tree.erase(50); // Удаляем корень с двумя потомками

    EXPECT_EQ(tree.search(50), nullptr);
    // Минимальный элемент из правого поддерева (60) должен заменить удаленный
    EXPECT_NE(tree.search(60), nullptr);
    // Проверяем, что дерево сохранило структуру
    EXPECT_NE(tree.search(30), nullptr);
    EXPECT_NE(tree.search(70), nullptr);
}

TEST_F(BinarySearchTreeTest, ClearTree) {
    tree.clear();

    EXPECT_EQ(tree.search(50), nullptr);
    EXPECT_EQ(tree.min(), nullptr);
    EXPECT_EQ(tree.max(), nullptr);

    // Проверяем, что можно снова использовать дерево после очистки
    tree.insert(100);
    EXPECT_NE(tree.search(100), nullptr);
}

TEST_F(BinarySearchTreeTest, LevelOrderTraversal) {
    testing::internal::CaptureStdout();
    tree.levelOrder();
    std::string output = testing::internal::GetCapturedStdout();

    // Ожидаемый порядок: 50 30 70 20 40 60 80
    EXPECT_EQ(output, "50 30 70 20 40 60 80 \n");

    BSearchTree<int> emptyTree;
    testing::internal::CaptureStdout();
    emptyTree.levelOrder();
    output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.empty());
}

TEST_F(BinarySearchTreeTest, InOrderTraversal) {
    testing::internal::CaptureStdout();
    tree.print();
    std::string output = testing::internal::GetCapturedStdout();

    // Ожидаемый вывод: 20 30 40 50 60 70 80
    EXPECT_EQ(output, "20 30 40 50 60 70 80 \n");

    BSearchTree<int> emptyTree;
    testing::internal::CaptureStdout();
    emptyTree.print();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "\n"); // Пустое дерево печатает только новую строку
}

TEST_F(BinarySearchTreeTest, DuplicateInsert) {
    tree.insert(50); // Дубликат
    EXPECT_NE(tree.search(50), nullptr);

    // Проверяем, что дерево сохранило структуру
    testing::internal::CaptureStdout();
    tree.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "20 30 40 50 60 70 80 \n");
}

TEST_F(BinarySearchTreeTest, ComplexOperations) {
    // Создаем большое дерево
    BSearchTree<int> bigTree;
    for (int i = 0; i < 100; ++i) {
        bigTree.insert(i);
    }

    // Проверяем минимум и максимум
    EXPECT_EQ(bigTree.min()->_value, 0);
    EXPECT_EQ(bigTree.max()->_value, 99);

    // Удаляем каждый второй элемент
    for (int i = 0; i < 100; i += 2) {
        bigTree.erase(i);
    }

    // Проверяем оставшиеся элементы
    for (int i = 0; i < 100; ++i) {
        if (i % 2 == 0) {
            EXPECT_EQ(bigTree.search(i), nullptr);
        }
        else {
            EXPECT_NE(bigTree.search(i), nullptr);
        }
    }

    // Очищаем и проверяем
    bigTree.clear();
    EXPECT_EQ(bigTree.min(), nullptr);
    EXPECT_EQ(bigTree.max(), nullptr);
}

TEST_F(BinarySearchTreeTest, StringValues) {
    BSearchTree<std::string> stringTree;
    stringTree.insert("apple");
    stringTree.insert("banana");
    stringTree.insert("cherry");

    EXPECT_NE(stringTree.search("banana"), nullptr);
    EXPECT_EQ(stringTree.search("banana")->_value, "banana");

    EXPECT_EQ(stringTree.min()->_value, "apple");
    EXPECT_EQ(stringTree.max()->_value, "cherry");

    stringTree.erase("banana");
    EXPECT_EQ(stringTree.search("banana"), nullptr);
}