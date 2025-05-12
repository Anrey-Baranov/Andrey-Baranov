#include "gtest.h"
#include "../lib_avltree/AVLTree.h"

template class AVLTree<int>;

class AVLTreePrivateTest : public ::testing::Test {
protected:
    AVLTree<int> tree;

    void SetUp() override {
        tree.insert(50);
        tree.insert(30);
        tree.insert(70);
    }

    // Методы для доступа к приватным членам
    AVLTreeNode<int>* test_search(AVLTreeNode<int>* node, int val) const {
        return tree._search(node, val);
    }

    AVLTreeNode<int>* test_insert(AVLTreeNode<int>* node, int val) {
        return tree._insert(node, val);
    }

    AVLTreeNode<int>* test_erase(AVLTreeNode<int>* node, int val) {
        return tree._erase(node, val);
    }

    AVLTreeNode<int>* test_minValueNode(AVLTreeNode<int>* node) const {
        return tree.minValueNode(node);
    }

    void test_clear(AVLTreeNode<int>*& node) {
        tree._clear(node);
    }

    void test_printTree(AVLTreeNode<int>* node) const {
        tree._printTree(node);
    }

    int test_height(AVLTreeNode<int>* node) const {
        return tree.height(node);
    }

    int test_balanceFactor(AVLTreeNode<int>* node) const {
        return tree.balanceFactor(node);
    }

    void test_updateHeight(AVLTreeNode<int>* node) {
        tree.updateHeight(node);
    }

    AVLTreeNode<int>* test_rotateRight(AVLTreeNode<int>* y) {
        return tree.rotateRight(y);
    }

    AVLTreeNode<int>* test_rotateLeft(AVLTreeNode<int>* x) {
        return tree.rotateLeft(x);
    }

    AVLTreeNode<int>* test_balance(AVLTreeNode<int>* node) {
        return tree.balance(node);
    }
    AVLTreeNode<int>* test_rotateLR(AVLTreeNode<int>* node) {
        return tree._rotateLR(node);
    }

    AVLTreeNode<int>* test_rotateRL(AVLTreeNode<int>* node) {
        return tree._rotateRL(node);
    }
};

TEST_F(AVLTreePrivateTest, PrivateSearch) {
    AVLTreeNode<int>* root = tree.search(50);
    ASSERT_NE(root, nullptr);

    EXPECT_NE(test_search(root, 30), nullptr);
    EXPECT_NE(test_search(root, 70), nullptr);
    EXPECT_EQ(test_search(root, 10), nullptr);
}

TEST_F(AVLTreePrivateTest, PrivateInsert) {
    AVLTreeNode<int>* root = tree.search(50);
    root = test_insert(root, 20);
    root = test_insert(root, 80);

    EXPECT_NE(test_search(root, 20), nullptr);
    EXPECT_NE(test_search(root, 80), nullptr);
    EXPECT_TRUE(test_balanceFactor(root) >= -1 && test_balanceFactor(root) <= 1);
}

TEST_F(AVLTreePrivateTest, PrivateErase) {
    AVLTreeNode<int>* root = tree.search(50);
    root = test_erase(root, 30);
    EXPECT_EQ(test_search(root, 30), nullptr);
    EXPECT_TRUE(test_balanceFactor(root) >= -1 && test_balanceFactor(root) <= 1);
}

TEST_F(AVLTreePrivateTest, PrivateMinValueNode) {
    AVLTreeNode<int>* root = tree.search(50);
    EXPECT_EQ(test_minValueNode(root)->_value, 30);
    EXPECT_EQ(test_minValueNode(root->right)->_value, 70);
}

TEST_F(AVLTreePrivateTest, PrivateHeightAndBalance) {
    AVLTreeNode<int>* root = tree.search(50);
    EXPECT_EQ(test_height(root), 2);
    EXPECT_EQ(test_balanceFactor(root), 0);

    test_updateHeight(root);
    EXPECT_EQ(root->height, 2);
}

TEST_F(AVLTreePrivateTest, PrivateRotations) {
    // Тестирование правого поворота
    AVLTreeNode<int>* node = new AVLTreeNode<int>(30);
    node->left = new AVLTreeNode<int>(20);
    node->left->left = new AVLTreeNode<int>(10);

    // Обновим высоты перед поворотом
    node->left->left->height = 1;
    node->left->height = 2;
    node->height = 3;

    node = test_rotateRight(node);
    EXPECT_EQ(node->_value, 20);
    EXPECT_EQ(node->right->_value, 30);
    EXPECT_EQ(node->left->_value, 10);

    // Тестирование левого поворота
    node = new AVLTreeNode<int>(10);
    node->right = new AVLTreeNode<int>(20);
    node->right->right = new AVLTreeNode<int>(30);

    // Обновим высоты перед поворотом
    node->right->right->height = 1;
    node->right->height = 2;
    node->height = 3;

    node = test_rotateLeft(node);
    EXPECT_EQ(node->_value, 20);
    EXPECT_EQ(node->left->_value, 10);
    EXPECT_EQ(node->right->_value, 30);
}

TEST_F(AVLTreePrivateTest, PrivateBalance) {
    AVLTreeNode<int>* node = new AVLTreeNode<int>(30);
    node->left = new AVLTreeNode<int>(20);
    node->left->left = new AVLTreeNode<int>(10);

    node = test_balance(node);
    EXPECT_TRUE(test_balanceFactor(node) >= -1 && test_balanceFactor(node) <= 1);
}
TEST_F(AVLTreePrivateTest, PrivateRotateLR) {
    // LR-ситуация: 30 -> 10 -> 20
    AVLTreeNode<int>* node = new AVLTreeNode<int>(30);
    node->left = new AVLTreeNode<int>(10);
    node->left->right = new AVLTreeNode<int>(20);

    // Обновляем высоты
    test_updateHeight(node->left->right);
    test_updateHeight(node->left);
    test_updateHeight(node);

    // Применяем LR-поворот через метод-обёртку
    node = test_rotateLR(node);

    // Проверки
    EXPECT_EQ(node->_value, 20);
    EXPECT_EQ(node->left->_value, 10);
    EXPECT_EQ(node->right->_value, 30);
    EXPECT_TRUE(test_balanceFactor(node) >= -1 && test_balanceFactor(node) <= 1);
}

TEST_F(AVLTreePrivateTest, PrivateRotateRL) {
    // RL-ситуация: 10 -> 30 -> 20
    AVLTreeNode<int>* node = new AVLTreeNode<int>(10);
    node->right = new AVLTreeNode<int>(30);
    node->right->left = new AVLTreeNode<int>(20);

    // Обновляем высоты
    test_updateHeight(node->right->left);
    test_updateHeight(node->right);
    test_updateHeight(node);

    // Применяем RL-поворот через метод-обёртку
    node = test_rotateRL(node);

    // Проверки
    EXPECT_EQ(node->_value, 20);
    EXPECT_EQ(node->left->_value, 10);
    EXPECT_EQ(node->right->_value, 30);
    EXPECT_TRUE(test_balanceFactor(node) >= -1 && test_balanceFactor(node) <= 1);
}
class AVLTreeTest : public ::testing::Test {
protected:
    AVLTree<int> tree;

    void SetUp() override {
        tree.insert(50);
        tree.insert(30);
        tree.insert(70);
        tree.insert(20);
        tree.insert(40);
        tree.insert(60);
        tree.insert(80);
    }
};

TEST_F(AVLTreeTest, InitialState) {
    AVLTree<int> emptyTree;
    EXPECT_EQ(emptyTree.search(10), nullptr);
    EXPECT_TRUE(emptyTree.isBalanced());
}

TEST_F(AVLTreeTest, InsertAndSearch) {
    EXPECT_NE(tree.search(50), nullptr);
    EXPECT_EQ(tree.search(50)->_value, 50);
    EXPECT_NE(tree.search(30), nullptr);
    EXPECT_TRUE(tree.isBalanced());
}

TEST_F(AVLTreeTest, EraseLeafNode) {
    tree.erase(20);
    EXPECT_EQ(tree.search(20), nullptr);
    EXPECT_TRUE(tree.isBalanced());
}

TEST_F(AVLTreeTest, EraseNodeWithOneChild) {
    tree.erase(20);
    tree.erase(30);
    EXPECT_EQ(tree.search(30), nullptr);
    EXPECT_TRUE(tree.isBalanced());
}

TEST_F(AVLTreeTest, EraseNodeWithTwoChildren) {
    tree.erase(50);
    EXPECT_EQ(tree.search(50), nullptr);
    EXPECT_TRUE(tree.isBalanced());
}

TEST_F(AVLTreeTest, ClearTree) {
    tree.clear();
    EXPECT_EQ(tree.search(50), nullptr);
    EXPECT_TRUE(tree.isBalanced());
}

TEST_F(AVLTreeTest, LevelOrderTraversal) {
    testing::internal::CaptureStdout();
    tree.printLevelOrder();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("50(") != std::string::npos);
}

TEST_F(AVLTreeTest, InOrderTraversal) {
    testing::internal::CaptureStdout();
    tree.printInOrder();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("20 30") != std::string::npos);
}

TEST_F(AVLTreeTest, TreeVisualization) {
    testing::internal::CaptureStdout();
    tree.printTree();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Дерево с ветвями") != std::string::npos);
}

TEST_F(AVLTreeTest, BalanceAfterOperations) {
    // Правая правая ситуация
    AVLTree<int> rrTree;
    rrTree.insert(10);
    rrTree.insert(20);
    rrTree.insert(30);
    EXPECT_TRUE(rrTree.isBalanced());

    // Левая левая ситуация
    AVLTree<int> llTree;
    llTree.insert(30);
    llTree.insert(20);
    llTree.insert(10);
    EXPECT_TRUE(llTree.isBalanced());

    // Правая левая ситуация
    AVLTree<int> rlTree;
    rlTree.insert(10);
    rlTree.insert(30);
    rlTree.insert(20);
    EXPECT_TRUE(rlTree.isBalanced());

    // Левая правая ситуация
    AVLTree<int> lrTree;
    lrTree.insert(30);
    lrTree.insert(10);
    lrTree.insert(20);
    EXPECT_TRUE(lrTree.isBalanced());
}

TEST_F(AVLTreeTest, ComplexOperations) {
    AVLTree<int> bigTree;
    for (int i = 0; i < 100; ++i) {
        bigTree.insert(i);
    }
    EXPECT_TRUE(bigTree.isBalanced());

    for (int i = 0; i < 100; i += 2) {
        bigTree.erase(i);
    }
    EXPECT_TRUE(bigTree.isBalanced());

    bigTree.clear();
    EXPECT_TRUE(bigTree.isBalanced());
}

TEST_F(AVLTreeTest, StringValues) {
    AVLTree<std::string> stringTree;
    stringTree.insert("apple");
    stringTree.insert("banana");
    stringTree.insert("cherry");
    EXPECT_TRUE(stringTree.isBalanced());
    EXPECT_NE(stringTree.search("banana"), nullptr);
}

TEST_F(AVLTreeTest, EmptyTreeOperations) {
    AVLTree<int> emptyTree;
    EXPECT_EQ(emptyTree.search(10), nullptr);
    EXPECT_TRUE(emptyTree.isBalanced());
    EXPECT_NO_THROW(emptyTree.erase(10));
    EXPECT_NO_THROW(emptyTree.printTree());
    EXPECT_NO_THROW(emptyTree.printLevelOrder());
    EXPECT_NO_THROW(emptyTree.printInOrder());
}

TEST_F(AVLTreeTest, DuplicateInsert) {
    tree.insert(50);
    EXPECT_NE(tree.search(50), nullptr);
    EXPECT_TRUE(tree.isBalanced());
}