#include "gtest.h"
#include "../lib_rbtree/TRBTree.h"

template class RBTree<int>;
template class RBTree<std::string>;

class RBTreePrivateTest : public ::testing::Test {
protected:
    RBTree<int> tree;

    RBTreeNode<int>* test_search(RBTreeNode<int>* node, int val) const {
        if (node == nullptr || node->_value == val) {
            return node;
        }
        if (val < node->_value) {
            return test_search(node->left, val);
        }
        return test_search(node->right, val);
    }

    RBTreeNode<int>* test_insert(RBTreeNode<int>* root, RBTreeNode<int>* pt) {
        if (root == nullptr) return pt;

        if (pt->_value < root->_value) {
            root->left = test_insert(root->left, pt);
            root->left->parent = root;
        }
        else if (pt->_value > root->_value) {
            root->right = test_insert(root->right, pt);
            root->right->parent = root;
        }
        return root;
    }

    void test_fixInsert(RBTreeNode<int>* k) {
        tree.fixInsert(k);
    }

    void test_rotateLeft(RBTreeNode<int>* x) {
        tree.rotateLeft(x);
    }

    void test_rotateRight(RBTreeNode<int>* x) {
        tree.rotateRight(x);
    }

    RBTreeNode<int>* test_minValueNode(RBTreeNode<int>* node) const {
        RBTreeNode<int>* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    RBTreeNode<int>* test_maxValueNode(RBTreeNode<int>* node) const {
        RBTreeNode<int>* current = node;
        while (current && current->right != nullptr) {
            current = current->right;
        }
        return current;
    }

    void test_transplant(RBTreeNode<int>* u, RBTreeNode<int>* v) {
        tree.transplant(u, v);
    }

    void test_fixDelete(RBTreeNode<int>* x) {
        tree.fixDelete(x);
    }

    RBTreeNode<int>* test_deleteHelper(RBTreeNode<int>* node, int val) {
        if (node == nullptr) return node;

        if (val < node->_value) {
            return test_deleteHelper(node->left, val);
        }
        else if (val > node->_value) {
            return test_deleteHelper(node->right, val);
        }
        else {
            if (node->left == nullptr || node->right == nullptr) {
                return node;
            }
            RBTreeNode<int>* temp = test_minValueNode(node->right);
            node->_value = temp->_value;
            return test_deleteHelper(node->right, temp->_value);
        }
    }

    void test_clearHelper(RBTreeNode<int>* node) {
        if (node == nullptr) return;
        test_clearHelper(node->left);
        test_clearHelper(node->right);
        delete node;
    }
};

TEST_F(RBTreePrivateTest, PrivateSearch) {
    RBTreeNode<int>* root = new RBTreeNode<int>(50, BLACK);
    root->left = new RBTreeNode<int>(30, RED, root);
    root->right = new RBTreeNode<int>(70, RED, root);

    ASSERT_NE(root, nullptr);
    EXPECT_NE(test_search(root, 30), nullptr);
    EXPECT_NE(test_search(root, 70), nullptr);
    EXPECT_EQ(test_search(root, 10), nullptr);

    delete root->left;
    delete root->right;
    delete root;
}

TEST_F(RBTreePrivateTest, PrivateInsertHelper) {
    RBTreeNode<int>* root = new RBTreeNode<int>(50, BLACK);
    RBTreeNode<int>* node1 = new RBTreeNode<int>(30, RED);
    RBTreeNode<int>* node2 = new RBTreeNode<int>(70, RED);

    root = test_insert(root, node1);
    root = test_insert(root, node2);

    EXPECT_NE(test_search(root, 30), nullptr);
    EXPECT_NE(test_search(root, 70), nullptr);
    EXPECT_EQ(root->_value, 50);
    EXPECT_EQ(root->left->_value, 30);
    EXPECT_EQ(root->right->_value, 70);
    EXPECT_EQ(root->left->parent, root);
    EXPECT_EQ(root->right->parent, root);

    test_clearHelper(root);
}

TEST_F(RBTreePrivateTest, PrivateRotateLeft) {
    RBTreeNode<int>* root = new RBTreeNode<int>(30, BLACK);
    root->right = new RBTreeNode<int>(50, RED, root);
    root->right->right = new RBTreeNode<int>(70, RED, root->right);

    test_rotateLeft(root);

    EXPECT_EQ(root->parent->_value, 50);
    EXPECT_EQ(root->parent->left, root);
    EXPECT_EQ(root->parent->right->_value, 70);
    EXPECT_EQ(root->right, nullptr);

    test_clearHelper(root->parent);
}

TEST_F(RBTreePrivateTest, PrivateRotateRight) {
    RBTreeNode<int>* root = new RBTreeNode<int>(50, BLACK);
    root->left = new RBTreeNode<int>(30, RED, root);
    root->left->left = new RBTreeNode<int>(10, RED, root->left);

    test_rotateRight(root);

    EXPECT_EQ(root->parent->_value, 30);
    EXPECT_EQ(root->parent->right, root);
    EXPECT_EQ(root->parent->left->_value, 10);
    EXPECT_EQ(root->left, nullptr);

    test_clearHelper(root->parent);
}

TEST_F(RBTreePrivateTest, PrivateFixInsertCase1) {
    RBTreeNode<int>* root = new RBTreeNode<int>(50, BLACK);
    RBTreeNode<int>* node1 = new RBTreeNode<int>(30, RED, root);
    RBTreeNode<int>* node2 = new RBTreeNode<int>(70, RED, root);
    root->left = node1;
    root->right = node2;

    // Случай 1: Дядя КРАСНЫЙ
    RBTreeNode<int>* newNode = new RBTreeNode<int>(20, RED, node1);
    node1->left = newNode;

    test_fixInsert(newNode);

    EXPECT_EQ(root->color, RED);
    EXPECT_EQ(node1->color, BLACK);
    EXPECT_EQ(node2->color, BLACK);
    EXPECT_EQ(newNode->color, RED);

    test_clearHelper(root);
}

TEST_F(RBTreePrivateTest, PrivateFixInsertCase2And3) {
    RBTreeNode<int>* root = new RBTreeNode<int>(50, BLACK);
    RBTreeNode<int>* node1 = new RBTreeNode<int>(30, RED, root);
    root->left = node1;

    // Случай 2 и 3: Дядя ЧЕРНЫЙ, а новый узел - левый дочерний
    RBTreeNode<int>* newNode = new RBTreeNode<int>(20, RED, node1);
    node1->left = newNode;

    test_fixInsert(newNode);

    EXPECT_EQ(root->_value, 30);
    EXPECT_EQ(root->color, BLACK);
    EXPECT_EQ(root->left->_value, 20);
    EXPECT_EQ(root->left->color, RED);
    EXPECT_EQ(root->right->_value, 50);
    EXPECT_EQ(root->right->color, RED);

    test_clearHelper(root);
}

TEST_F(RBTreePrivateTest, PrivateMinMaxValueNode) {
    RBTreeNode<int>* root = new RBTreeNode<int>(50, BLACK);
    root->left = new RBTreeNode<int>(30, RED, root);
    root->right = new RBTreeNode<int>(70, RED, root);
    root->left->left = new RBTreeNode<int>(20, BLACK, root->left);
    root->left->right = new RBTreeNode<int>(40, BLACK, root->left);

    EXPECT_EQ(test_minValueNode(root)->_value, 20);
    EXPECT_EQ(test_maxValueNode(root)->_value, 70);
    EXPECT_EQ(test_minValueNode(root->right)->_value, 70);
    EXPECT_EQ(test_maxValueNode(root->left)->_value, 40);

    test_clearHelper(root);
}

TEST_F(RBTreePrivateTest, PrivateTransplant) {
    RBTreeNode<int>* root = new RBTreeNode<int>(50, BLACK);
    root->left = new RBTreeNode<int>(30, RED, root);
    root->right = new RBTreeNode<int>(70, RED, root);

    test_transplant(root->left, root->left->right); // Неподходящий ребенок
    test_transplant(root, root->right);

    EXPECT_EQ(root->_value, 70);
    EXPECT_EQ(root->parent, nullptr);

    delete root->left;
    delete root;
}

TEST_F(RBTreePrivateTest, PrivateFixDeleteCases) {
    RBTreeNode<int>* root = new RBTreeNode<int>(50, BLACK);
    RBTreeNode<int>* node1 = new RBTreeNode<int>(30, BLACK, root);
    RBTreeNode<int>* node2 = new RBTreeNode<int>(70, BLACK, root);
    root->left = node1;
    root->right = node2;
    node1->right = new RBTreeNode<int>(40, RED, node1);

    // Случай 1: Брат красного цвета
    test_fixDelete(node1->left);

    EXPECT_EQ(root->color, BLACK);
    EXPECT_EQ(node1->color, BLACK);
    EXPECT_EQ(node2->color, BLACK);

    // Случай 2: Оба потомка брата чёрные
    node2->left = new RBTreeNode<int>(60, BLACK, node2);
    node2->right = new RBTreeNode<int>(80, BLACK, node2);
    test_fixDelete(node1->left);

    EXPECT_EQ(node2->color, RED);

    test_clearHelper(root);
}

class RBTreeTest : public ::testing::Test {
protected:
    RBTree<int> tree;
};

TEST_F(RBTreeTest, InitialState) {
    EXPECT_EQ(tree.search(10), nullptr);
}

bool checkRedBlackProperties(RBTreeNode<int>* node) {
    if (node == nullptr) return true;
    if (node->color == RED) {
        if (node->left && node->left->color == RED) return false;
        if (node->right && node->right->color == RED) return false;
    }
    return checkRedBlackProperties(node->left) && checkRedBlackProperties(node->right);
}

TEST_F(RBTreeTest, InsertAndSearch) {
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    EXPECT_NE(tree.search(50), nullptr);
    EXPECT_EQ(tree.search(50)->_value, 50);
    EXPECT_NE(tree.search(30), nullptr);
    EXPECT_NE(tree.search(70), nullptr);

    // Проверяем, что корень должен быть чёрный
    EXPECT_EQ(tree.search(50)->color, BLACK);
    EXPECT_TRUE(checkRedBlackProperties(tree.search(50)));
}

TEST_F(RBTreeTest, InsertDuplicate) {
    tree.insert(50);
    tree.insert(50);
    EXPECT_NE(tree.search(50), nullptr);
    EXPECT_EQ(tree.search(50)->_value, 50);
    EXPECT_EQ(tree.search(50)->left, nullptr);
    EXPECT_EQ(tree.search(50)->right, nullptr);
}

TEST_F(RBTreeTest, EraseLeafNode) {
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);

    tree.erase(20);
    EXPECT_EQ(tree.search(20), nullptr);
    EXPECT_NE(tree.search(30), nullptr);
    EXPECT_NE(tree.search(50), nullptr);
    EXPECT_NE(tree.search(70), nullptr);

    // Проверяем структуру дерева
    auto root = tree.search(50);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->left->_value, 30);
    EXPECT_EQ(root->right->_value, 70);
    EXPECT_EQ(root->left->left, nullptr);
}

TEST_F(RBTreeTest, EraseNodeWithOneChild) {
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);

    tree.erase(30);
    EXPECT_EQ(tree.search(30), nullptr);
    EXPECT_NE(tree.search(20), nullptr);
    EXPECT_NE(tree.search(50), nullptr);
    EXPECT_NE(tree.search(70), nullptr);

    // Проверяем структуру дерева
    auto root = tree.search(50);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->left->_value, 20);
    EXPECT_EQ(root->right->_value, 70);
    EXPECT_EQ(root->left->color, BLACK);
}

TEST_F(RBTreeTest, EraseNodeWithTwoChildren) {
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    tree.erase(50);
    EXPECT_EQ(tree.search(50), nullptr);
    EXPECT_NE(tree.search(60), nullptr);

    // Проверяем структуру дерева
    auto root = tree.search(60); // Новый корень
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->left->_value, 30);
    EXPECT_EQ(root->right->_value, 70);
    EXPECT_EQ(root->left->left->_value, 20);
    EXPECT_EQ(root->left->right->_value, 40);
    EXPECT_EQ(root->right->right->_value, 80);
    EXPECT_EQ(root->color, BLACK);
}

TEST_F(RBTreeTest, EraseRoot) {
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);

    tree.erase(50);
    EXPECT_EQ(tree.search(50), nullptr);
    EXPECT_NE(tree.search(30), nullptr);
    EXPECT_NE(tree.search(70), nullptr);

    // Проверка, новый корень чёрный
    auto root = tree.search(70);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->color, BLACK);
    EXPECT_EQ(root->left->_value, 30);
}

TEST_F(RBTreeTest, ClearTree) {
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);

    tree.clear();
    EXPECT_EQ(tree.search(50), nullptr);
}

TEST_F(RBTreeTest, LevelOrderTraversal) {
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    testing::internal::CaptureStdout();
    tree.levelOrder();
    std::string output = testing::internal::GetCapturedStdout();

    // Проверяем наличие всех значений
    EXPECT_TRUE(output.find("50") != std::string::npos);
    EXPECT_TRUE(output.find("30") != std::string::npos);
    EXPECT_TRUE(output.find("70") != std::string::npos);
    EXPECT_TRUE(output.find("20") != std::string::npos);
    EXPECT_TRUE(output.find("40") != std::string::npos);
    EXPECT_TRUE(output.find("60") != std::string::npos);
    EXPECT_TRUE(output.find("80") != std::string::npos);
}

TEST_F(RBTreeTest, MinMaxValues) {
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    EXPECT_EQ(tree.getMin()->_value, 20);
    EXPECT_EQ(tree.getMax()->_value, 80);
}

TEST_F(RBTreeTest, AllRotationCases) {
    // Тест LL поворота
    RBTree<int> llTree;
    llTree.insert(30);
    llTree.insert(20);
    llTree.insert(10);

    auto root = llTree.search(20);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->left->_value, 10);
    EXPECT_EQ(root->right->_value, 30);
    EXPECT_EQ(root->color, BLACK);
    EXPECT_EQ(root->left->color, RED);
    EXPECT_EQ(root->right->color, RED);

    // Тест RR поворота
    RBTree<int> rrTree;
    rrTree.insert(10);
    rrTree.insert(20);
    rrTree.insert(30);

    root = rrTree.search(20);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->left->_value, 10);
    EXPECT_EQ(root->right->_value, 30);
    EXPECT_EQ(root->color, BLACK);
    EXPECT_EQ(root->left->color, RED);
    EXPECT_EQ(root->right->color, RED);

    // Тест LR поворота
    RBTree<int> lrTree;
    lrTree.insert(30);
    lrTree.insert(10);
    lrTree.insert(20);

    root = lrTree.search(20);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->left->_value, 10);
    EXPECT_EQ(root->right->_value, 30);
    EXPECT_EQ(root->color, BLACK);
    EXPECT_EQ(root->left->color, RED);
    EXPECT_EQ(root->right->color, RED);

    // Тест RL поворота
    RBTree<int> rlTree;
    rlTree.insert(10);
    rlTree.insert(30);
    rlTree.insert(20);

    root = rlTree.search(20);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->left->_value, 10);
    EXPECT_EQ(root->right->_value, 30);
    EXPECT_EQ(root->color, BLACK);
    EXPECT_EQ(root->left->color, RED);
    EXPECT_EQ(root->right->color, RED);
}

TEST_F(RBTreeTest, ComplexOperations) {
    RBTree<int> bigTree;
    for (int i = 0; i < 100; ++i) {
        bigTree.insert(i);
    }

    // Проверяем, что все значения присутствуют
    for (int i = 0; i < 100; ++i) {
        EXPECT_NE(bigTree.search(i), nullptr);
    }

    // Проверка, корень должен быть чёрным
    EXPECT_EQ(bigTree.search(50)->color, BLACK);

    // Удаляем половину узлов
    for (int i = 0; i < 100; i += 2) {
        bigTree.erase(i);
    }

    // Проверяем, что остались только нечётные числа
    for (int i = 0; i < 100; ++i) {
        if (i % 2 == 0) {
            EXPECT_EQ(bigTree.search(i), nullptr);
        }
        else {
            EXPECT_NE(bigTree.search(i), nullptr);
        }
    }

    bigTree.clear();
    EXPECT_EQ(bigTree.search(1), nullptr);
}

TEST_F(RBTreeTest, StringValues) {
    RBTree<std::string> stringTree;
    stringTree.insert("apple");
    stringTree.insert("banana");
    stringTree.insert("cherry");

    EXPECT_NE(stringTree.search("banana"), nullptr);
    EXPECT_EQ(stringTree.search("banana")->_value, "banana");

    // Проверка цвета
    EXPECT_EQ(stringTree.search("banana")->color, BLACK);
    EXPECT_EQ(stringTree.search("apple")->color, RED);
    EXPECT_EQ(stringTree.search("cherry")->color, RED);
}

TEST_F(RBTreeTest, EmptyTreeOperations) {
    RBTree<int> emptyTree;
    EXPECT_EQ(emptyTree.search(10), nullptr);
    EXPECT_EQ(emptyTree.getMin(), nullptr);
    EXPECT_EQ(emptyTree.getMax(), nullptr);
    EXPECT_NO_THROW(emptyTree.erase(10));
    EXPECT_NO_THROW(emptyTree.levelOrder());
    EXPECT_NO_THROW(emptyTree.print());
}