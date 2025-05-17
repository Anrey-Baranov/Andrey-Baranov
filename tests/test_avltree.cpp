//#include "gtest.h"
//#include "../lib_avltree/AVLTree.h"
//
//template class AVLTree<int>;
//
//class AVLTreePrivateTest : public ::testing::Test {
//protected:
//    AVLTree<int> tree;
//
//    AVLTreeNode<int>* test_search(AVLTreeNode<int>* node, int val) const {
//        return tree._search(node, val);
//    }
//
//    AVLTreeNode<int>* test_insert(AVLTreeNode<int>* node, int val) {
//        AVLTreeNode<int>* g = nullptr;
//        AVLTreeNode<int>* p = nullptr;
//        AVLTreeNode<int>* u = nullptr;
//        return tree._insert(node, val, g, p, u);
//    }
//
//    AVLTreeNode<int>* test_erase(AVLTreeNode<int>* node, int val) {
//        return tree._erase(node, val);
//    }
//
//    AVLTreeNode<int>* test_minValueNode(AVLTreeNode<int>* node) const {
//        return tree.minValueNode(node);
//    }
//
//    void test_clear(AVLTreeNode<int>*& node) {
//        tree._clear(node);
//    }
//
//    void test_printTree(AVLTreeNode<int>* node) const {
//        tree._printTree(node);
//    }
//
//    int test_height(AVLTreeNode<int>* node) const {
//        return tree.height(node);
//    }
//
//    int test_balanceFactor(AVLTreeNode<int>* node) const {
//        return tree.balanceFactor(node);
//    }
//
//    void test_updateHeight(AVLTreeNode<int>* node) {
//        tree.updateHeight(node);
//    }
//
//    AVLTreeNode<int>* test_rotateRight(AVLTreeNode<int>* y) {
//        return tree.rotateRight(y);
//    }
//
//    AVLTreeNode<int>* test_rotateLeft(AVLTreeNode<int>* x) {
//        return tree.rotateLeft(x);
//    }
//
//    AVLTreeNode<int>* test_balance(AVLTreeNode<int>* node) {
//        return tree.balance(node);
//    }
//
//    AVLTreeNode<int>* test_rotateLR(AVLTreeNode<int>* node) {
//        return tree._rotateLR(node);
//    }
//
//    AVLTreeNode<int>* test_rotateRL(AVLTreeNode<int>* node) {
//        return tree._rotateRL(node);
//    }
//
//    void test_getRelatives(AVLTreeNode<int>* node, int val,
//        AVLTreeNode<int>*& g, AVLTreeNode<int>*& p, AVLTreeNode<int>*& u) const {
//        tree.getRelatives(node, val, g, p, u);
//    }
//};
//
//TEST_F(AVLTreePrivateTest, PrivateSearch) {
//    AVLTreeNode<int>* root = test_insert(nullptr, 50);
//    root = test_insert(root, 30);
//    root = test_insert(root, 70);
//
//    ASSERT_NE(root, nullptr);
//    EXPECT_NE(test_search(root, 30), nullptr);
//    EXPECT_NE(test_search(root, 70), nullptr);
//    EXPECT_EQ(test_search(root, 10), nullptr);
//}
//
//TEST_F(AVLTreePrivateTest, PrivateInsert) {
//    AVLTreeNode<int>* root = test_insert(nullptr, 50);
//    root = test_insert(root, 30);
//    root = test_insert(root, 70);
//    root = test_insert(root, 20);
//    root = test_insert(root, 80);
//
//    EXPECT_NE(test_search(root, 20), nullptr);
//    EXPECT_NE(test_search(root, 80), nullptr);
//    EXPECT_TRUE(test_balanceFactor(root) >= -1 && test_balanceFactor(root) <= 1);
//
//    // Проверка структуры дерева
//    EXPECT_EQ(root->_value, 50);
//    EXPECT_EQ(root->left->_value, 30);
//    EXPECT_EQ(root->right->_value, 70);
//    EXPECT_EQ(root->left->left->_value, 20);
//    EXPECT_EQ(root->right->right->_value, 80);
//}
//
//TEST_F(AVLTreePrivateTest, PrivateErase) {
//    AVLTreeNode<int>* root = test_insert(nullptr, 50);
//    root = test_insert(root, 30);
//    root = test_insert(root, 70);
//    root = test_insert(root, 20);
//
//    root = test_erase(root, 30);
//    EXPECT_EQ(test_search(root, 30), nullptr);
//    EXPECT_TRUE(test_balanceFactor(root) >= -1 && test_balanceFactor(root) <= 1);
//
//    // Проверка структуры дерева
//    EXPECT_EQ(root->_value, 50);
//    EXPECT_EQ(root->left->_value, 20);
//    EXPECT_EQ(root->right->_value, 70);
//}
//
//TEST_F(AVLTreePrivateTest, PrivateMinValueNode) {
//    AVLTreeNode<int>* root = test_insert(nullptr, 50);
//    root = test_insert(root, 30);
//    root = test_insert(root, 70);
//    root = test_insert(root, 20);
//    root = test_insert(root, 40);
//
//    EXPECT_EQ(test_minValueNode(root)->_value, 20);
//    EXPECT_EQ(test_minValueNode(root->right)->_value, 70);
//    EXPECT_EQ(test_minValueNode(root->left->right)->_value, 40);
//}
//
//TEST_F(AVLTreePrivateTest, PrivateHeightAndBalance) {
//    AVLTreeNode<int>* root = test_insert(nullptr, 50);
//    root = test_insert(root, 30);
//    root = test_insert(root, 70);
//
//    EXPECT_EQ(test_height(root), 2);
//    EXPECT_EQ(test_balanceFactor(root), 0);
//
//    test_updateHeight(root);
//    EXPECT_EQ(root->height, 2);
//}
//
//TEST_F(AVLTreePrivateTest, PrivateRotations) {
//    // Тестирование правого поворота (LL)
//    AVLTreeNode<int>* node = new AVLTreeNode<int>(30);
//    node->left = new AVLTreeNode<int>(20);
//    node->left->left = new AVLTreeNode<int>(10);
//
//    node->left->left->height = 1;
//    node->left->height = 2;
//    node->height = 3;
//
//    node = test_rotateRight(node);
//    EXPECT_EQ(node->_value, 20);
//    EXPECT_EQ(node->right->_value, 30);
//    EXPECT_EQ(node->left->_value, 10);
//    EXPECT_EQ(test_height(node), 2);
//    EXPECT_EQ(test_balanceFactor(node), 0);
//
//    // Тестирование левого поворота (RR)
//    node = new AVLTreeNode<int>(10);
//    node->right = new AVLTreeNode<int>(20);
//    node->right->right = new AVLTreeNode<int>(30);
//
//    node->right->right->height = 1;
//    node->right->height = 2;
//    node->height = 3;
//
//    node = test_rotateLeft(node);
//    EXPECT_EQ(node->_value, 20);
//    EXPECT_EQ(node->left->_value, 10);
//    EXPECT_EQ(node->right->_value, 30);
//    EXPECT_EQ(test_height(node), 2);
//    EXPECT_EQ(test_balanceFactor(node), 0);
//}
//
//TEST_F(AVLTreePrivateTest, PrivateBalance) {
//    // LL case
//    AVLTreeNode<int>* node = new AVLTreeNode<int>(30);
//    node->left = new AVLTreeNode<int>(20);
//    node->left->left = new AVLTreeNode<int>(10);
//
//    // Обновляем высоты перед балансировкой
//    test_updateHeight(node->left->left);
//    test_updateHeight(node->left);
//    test_updateHeight(node);
//
//    node = test_balance(node);
//    EXPECT_TRUE(test_balanceFactor(node) >= -1 && test_balanceFactor(node) <= 1);
//
//    // Проверяем корректные значения после балансировки
//    EXPECT_EQ(node->_value, 20);
//    if (node->left) EXPECT_EQ(node->left->_value, 10);
//    if (node->right) EXPECT_EQ(node->right->_value, 30);
//
//    // RR case
//    node = new AVLTreeNode<int>(10);
//    node->right = new AVLTreeNode<int>(20);
//    node->right->right = new AVLTreeNode<int>(30);
//
//    // Обновляем высоты перед балансировкой
//    test_updateHeight(node->right->right);
//    test_updateHeight(node->right);
//    test_updateHeight(node);
//
//    node = test_balance(node);
//    EXPECT_TRUE(test_balanceFactor(node) >= -1 && test_balanceFactor(node) <= 1);
//    EXPECT_EQ(node->_value, 20);
//    if (node->left) EXPECT_EQ(node->left->_value, 10);
//    if (node->right) EXPECT_EQ(node->right->_value, 30);
//}
//
//TEST_F(AVLTreePrivateTest, PrivateRotateLR) {
//    // LR case
//    AVLTreeNode<int>* node = new AVLTreeNode<int>(30);
//    node->left = new AVLTreeNode<int>(10);
//    node->left->right = new AVLTreeNode<int>(20);
//
//    test_updateHeight(node->left->right);
//    test_updateHeight(node->left);
//    test_updateHeight(node);
//
//    node = test_rotateLR(node);
//    EXPECT_EQ(node->_value, 20);
//    EXPECT_EQ(node->left->_value, 10);
//    EXPECT_EQ(node->right->_value, 30);
//    EXPECT_TRUE(test_balanceFactor(node) >= -1 && test_balanceFactor(node) <= 1);
//    EXPECT_EQ(test_height(node), 2);
//}
//
//TEST_F(AVLTreePrivateTest, PrivateRotateRL) {
//    // RL case
//    AVLTreeNode<int>* node = new AVLTreeNode<int>(10);
//    node->right = new AVLTreeNode<int>(30);
//    node->right->left = new AVLTreeNode<int>(20);
//
//    test_updateHeight(node->right->left);
//    test_updateHeight(node->right);
//    test_updateHeight(node);
//
//    node = test_rotateRL(node);
//    EXPECT_EQ(node->_value, 20);
//    EXPECT_EQ(node->left->_value, 10);
//    EXPECT_EQ(node->right->_value, 30);
//    EXPECT_TRUE(test_balanceFactor(node) >= -1 && test_balanceFactor(node) <= 1);
//    EXPECT_EQ(test_height(node), 2);
//}
//
//TEST_F(AVLTreePrivateTest, PrivateGetRelatives) {
//    AVLTreeNode<int>* root = test_insert(nullptr, 30);
//    root = test_insert(root, 15);
//    root = test_insert(root, 45);
//    root = test_insert(root, 10);
//    root = test_insert(root, 20);
//    root = test_insert(root, 50);
//
//    AVLTreeNode<int>* g = nullptr;
//    AVLTreeNode<int>* p = nullptr;
//    AVLTreeNode<int>* u = nullptr;
//
//    // Для элемента 50
//    test_getRelatives(root, 50, g, p, u);
//    EXPECT_NE(p, nullptr);
//    EXPECT_NE(g, nullptr);
//    EXPECT_NE(u, nullptr);
//    EXPECT_EQ(p->_value, 45);
//    EXPECT_EQ(g->_value, 30);
//    EXPECT_EQ(u->_value, 15);
//
//    // Для элемента 10
//    test_getRelatives(root, 10, g, p, u);
//    EXPECT_NE(p, nullptr);
//    EXPECT_NE(g, nullptr);
//    EXPECT_NE(u, nullptr);
//    EXPECT_EQ(p->_value, 15);
//    EXPECT_EQ(g->_value, 30);
//    EXPECT_EQ(u->_value, 45);
//
//    // Для корня (30)
//    test_getRelatives(root, 30, g, p, u);
//    EXPECT_EQ(p, nullptr);
//    EXPECT_EQ(g, nullptr);
//    EXPECT_EQ(u, nullptr);
//}
//
//class AVLTreeTest : public ::testing::Test {
//protected:
//    AVLTree<int> tree;
//};
//
//TEST_F(AVLTreeTest, InitialState) {
//    AVLTree<int> emptyTree;
//    EXPECT_EQ(emptyTree.search(10), nullptr);
//    EXPECT_TRUE(emptyTree.isBalanced());
//}
//
//TEST_F(AVLTreeTest, InsertAndSearch) {
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//    tree.insert(20);
//    tree.insert(40);
//    tree.insert(60);
//    tree.insert(80);
//
//    EXPECT_NE(tree.search(50), nullptr);
//    EXPECT_EQ(tree.search(50)->_value, 50);
//    EXPECT_NE(tree.search(30), nullptr);
//    EXPECT_TRUE(tree.isBalanced());
//
//    // Проверка структуры дерева
//    AVLTreeNode<int>* root = tree.search(50);
//    ASSERT_NE(root, nullptr);
//    EXPECT_EQ(root->left->_value, 30);
//    EXPECT_EQ(root->right->_value, 70);
//    EXPECT_EQ(root->left->left->_value, 20);
//    EXPECT_EQ(root->left->right->_value, 40);
//    EXPECT_EQ(root->right->left->_value, 60);
//    EXPECT_EQ(root->right->right->_value, 80);
//}
//
//TEST_F(AVLTreeTest, EraseLeafNode) {
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//    tree.insert(20);
//
//    tree.erase(20);
//    EXPECT_EQ(tree.search(20), nullptr);
//    EXPECT_TRUE(tree.isBalanced());
//
//    // Проверка структуры дерева
//    AVLTreeNode<int>* root = tree.search(50);
//    ASSERT_NE(root, nullptr);
//    EXPECT_EQ(root->left->_value, 30);
//    EXPECT_EQ(root->right->_value, 70);
//    EXPECT_EQ(root->left->left, nullptr);
//}
//
//TEST_F(AVLTreeTest, EraseNodeWithOneChild) {
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//    tree.insert(20);
//
//    tree.erase(30);
//    EXPECT_EQ(tree.search(30), nullptr);
//    EXPECT_TRUE(tree.isBalanced());
//
//    // Проверка структуры дерева
//    AVLTreeNode<int>* root = tree.search(50);
//    ASSERT_NE(root, nullptr);
//    EXPECT_EQ(root->left->_value, 20);
//    EXPECT_EQ(root->right->_value, 70);
//}
//
//TEST_F(AVLTreeTest, EraseNodeWithTwoChildren) {
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//    tree.insert(20);
//    tree.insert(40);
//    tree.insert(60);
//    tree.insert(80);
//
//    tree.erase(50);
//    EXPECT_EQ(tree.search(50), nullptr);
//    EXPECT_TRUE(tree.isBalanced());
//
//    // Проверка структуры дерева
//    AVLTreeNode<int>* root = tree.search(60); // Новый корень
//    ASSERT_NE(root, nullptr);
//    EXPECT_EQ(root->left->_value, 30);
//    EXPECT_EQ(root->right->_value, 70);
//    EXPECT_EQ(root->left->left->_value, 20);
//    EXPECT_EQ(root->left->right->_value, 40);
//    EXPECT_EQ(root->right->right->_value, 80);
//}
//
//TEST_F(AVLTreeTest, ClearTree) {
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//
//    tree.clear();
//    EXPECT_EQ(tree.search(50), nullptr);
//    EXPECT_TRUE(tree.isBalanced());
//}
//
//TEST_F(AVLTreeTest, LevelOrderTraversal) {
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//    tree.insert(20);
//    tree.insert(40);
//    tree.insert(60);
//    tree.insert(80);
//
//    testing::internal::CaptureStdout();
//    tree.printLevelOrder();
//    std::string output = testing::internal::GetCapturedStdout();
//
//    // Проверяем порядок и баланс-факторы
//    EXPECT_TRUE(output.find("50(0)") != std::string::npos);
//    EXPECT_TRUE(output.find("30(0)") != std::string::npos);
//    EXPECT_TRUE(output.find("70(0)") != std::string::npos);
//    EXPECT_TRUE(output.find("20(0)") != std::string::npos);
//    EXPECT_TRUE(output.find("40(0)") != std::string::npos);
//    EXPECT_TRUE(output.find("60(0)") != std::string::npos);
//    EXPECT_TRUE(output.find("80(0)") != std::string::npos);
//}
//
//TEST_F(AVLTreeTest, InOrderTraversal) {
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//    tree.insert(20);
//    tree.insert(40);
//    tree.insert(60);
//    tree.insert(80);
//
//    testing::internal::CaptureStdout();
//    tree.printInOrder();
//    std::string output = testing::internal::GetCapturedStdout();
//
//    // Проверяем порядок обхода
//    EXPECT_TRUE(output.find("20 30 40 50 60 70 80") != std::string::npos);
//}
//
//TEST_F(AVLTreeTest, TreeVisualization) {
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//
//    testing::internal::CaptureStdout();
//    tree.printTree();
//    std::string output = testing::internal::GetCapturedStdout();
//
//    EXPECT_TRUE(output.find("Дерево с ветвями") != std::string::npos);
//    EXPECT_TRUE(output.find("50") != std::string::npos);
//    EXPECT_TRUE(output.find("30") != std::string::npos);
//    EXPECT_TRUE(output.find("70") != std::string::npos);
//}
//
//TEST_F(AVLTreeTest, RelativesCheck) {
//    tree.insert(30);
//    tree.insert(15);
//    tree.insert(45);
//    tree.insert(10);
//    tree.insert(20);
//    tree.insert(50);
//
//    AVLTreeNode<int>* g = nullptr;
//    AVLTreeNode<int>* p = nullptr;
//    AVLTreeNode<int>* u = nullptr;
//
//    // Проверка для элемента 50
//    tree.getRelatives(50, g, p, u);
//    EXPECT_NE(p, nullptr);
//    EXPECT_NE(g, nullptr);
//    EXPECT_NE(u, nullptr);
//    EXPECT_EQ(p->_value, 45);
//    EXPECT_EQ(g->_value, 30);
//    EXPECT_EQ(u->_value, 15);
//
//    // Проверка для элемента 10
//    tree.getRelatives(10, g, p, u);
//    EXPECT_NE(p, nullptr);
//    EXPECT_NE(g, nullptr);
//    EXPECT_NE(u, nullptr);
//    EXPECT_EQ(p->_value, 15);
//    EXPECT_EQ(g->_value, 30);
//    EXPECT_EQ(u->_value, 45);
//
//    // Проверка для корня (30)
//    tree.getRelatives(30, g, p, u);
//    EXPECT_EQ(p, nullptr);
//    EXPECT_EQ(g, nullptr);
//    EXPECT_EQ(u, nullptr);
//}
//
//TEST_F(AVLTreeTest, AllBalanceCases) {
//
//    // LL case
//    AVLTree<int> llTree;
//    llTree.insert(30);
//    llTree.insert(20);
//    llTree.insert(10);
//    EXPECT_TRUE(llTree.isBalanced());
//    AVLTreeNode<int>* root = llTree.search(20);
//    ASSERT_NE(root, nullptr);
//    EXPECT_EQ(root->left->_value, 10);
//    EXPECT_EQ(root->right->_value, 30);
//
//    // RR case
//    AVLTree<int> rrTree;
//    rrTree.insert(10);
//    rrTree.insert(20);
//    rrTree.insert(30);
//    EXPECT_TRUE(rrTree.isBalanced());
//    root = rrTree.search(20);
//    ASSERT_NE(root, nullptr);
//    EXPECT_EQ(root->left->_value, 10);
//    EXPECT_EQ(root->right->_value, 30);
//
//    // LR case
//    AVLTree<int> lrTree;
//    lrTree.insert(30);
//    lrTree.insert(10);
//    lrTree.insert(20);
//    EXPECT_TRUE(lrTree.isBalanced());
//    root = lrTree.search(20);
//    ASSERT_NE(root, nullptr);
//    EXPECT_EQ(root->left->_value, 10);
//    EXPECT_EQ(root->right->_value, 30);
//
//    // RL case
//    AVLTree<int> rlTree;
//    rlTree.insert(10);
//    rlTree.insert(30);
//    rlTree.insert(20);
//    EXPECT_TRUE(rlTree.isBalanced());
//    root = rlTree.search(20);
//    ASSERT_NE(root, nullptr);
//    EXPECT_EQ(root->left->_value, 10);
//    EXPECT_EQ(root->right->_value, 30);
//}
//
//TEST_F(AVLTreeTest, ComplexOperations) {
//    AVLTree<int> bigTree;
//    for (int i = 0; i < 100; ++i) {
//        bigTree.insert(i);
//    }
//    EXPECT_TRUE(bigTree.isBalanced());
//
//    // Проверка структуры после вставки
//    AVLTreeNode<int>* root = bigTree.search(50);
//    ASSERT_NE(root, nullptr);
//
//    EXPECT_TRUE(root != nullptr);
//
//    for (int i = 0; i < 100; i += 2) {
//        bigTree.erase(i);
//    }
//    EXPECT_TRUE(bigTree.isBalanced());
//
//    bigTree.clear();
//    EXPECT_TRUE(bigTree.isBalanced());
//}
//
//TEST_F(AVLTreeTest, StringValues) {
//    AVLTree<std::string> stringTree;
//    stringTree.insert("apple");
//    stringTree.insert("banana");
//    stringTree.insert("cherry");
//    EXPECT_TRUE(stringTree.isBalanced());
//    EXPECT_NE(stringTree.search("banana"), nullptr);
//
//    // Проверка структуры
//    AVLTreeNode<std::string>* root = stringTree.search("banana");
//    ASSERT_NE(root, nullptr);
//    EXPECT_EQ(root->left->_value, "apple");
//    EXPECT_EQ(root->right->_value, "cherry");
//}
//
//TEST_F(AVLTreeTest, EmptyTreeOperations) {
//    AVLTree<int> emptyTree;
//    EXPECT_EQ(emptyTree.search(10), nullptr);
//    EXPECT_TRUE(emptyTree.isBalanced());
//    EXPECT_NO_THROW(emptyTree.erase(10));
//    EXPECT_NO_THROW(emptyTree.printTree());
//    EXPECT_NO_THROW(emptyTree.printLevelOrder());
//    EXPECT_NO_THROW(emptyTree.printInOrder());
//}
//
//TEST_F(AVLTreeTest, DuplicateInsert) {
//    tree.insert(50);
//    tree.insert(50);
//    EXPECT_NE(tree.search(50), nullptr);
//    EXPECT_TRUE(tree.isBalanced());
//
//    // Проверка что дубликат не добавлен
//    AVLTreeNode<int>* root = tree.search(50);
//    ASSERT_NE(root, nullptr);
//    EXPECT_EQ(root->left, nullptr);
//    EXPECT_EQ(root->right, nullptr);
//}