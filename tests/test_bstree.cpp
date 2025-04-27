//#include "gtest.h"
//#include "TBinSearchTree.h"
//
//// явна€ специализаци€ шаблона дл€ тестов
//template class BSearchTree<int>;
//
//class BSearchTreePrivateTest : public ::testing::Test {
//protected:
//    BSearchTree<int> tree;
//
//    void SetUp() override {
//        tree.insert(50);
//        tree.insert(30);
//        tree.insert(70);
//    }
//
//    // ћетоды дл€ доступа к приватным членам
//    BTreeNode<int>* test_search(BTreeNode<int>* node, int val) const {
//        return tree._search(node, val);
//    }
//
//    BTreeNode<int>* test_insert(BTreeNode<int>* node, int val) {
//        return tree._insert(node, val);
//    }
//
//    BTreeNode<int>* test_erase(BTreeNode<int>* node, int val) {
//        return tree._erase(node, val);
//    }
//
//    BTreeNode<int>* test_minValueNode(BTreeNode<int>* node) const {
//        return tree.minValueNode(node);
//    }
//
//    BTreeNode<int>* test_maxValueNode(BTreeNode<int>* node) const {
//        return tree.maxValueNode(node);
//    }
//
//    void test_clear(BTreeNode<int>*& node) {
//        tree._clear(node);
//    }
//
//    void test_print(BTreeNode<int>* node) const {
//        tree._print(node);
//    }
//};
//
//TEST_F(BSearchTreePrivateTest, PrivateSearch) {
//    BTreeNode<int>* root = tree.search(50);
//    ASSERT_NE(root, nullptr);
//
//    EXPECT_NE(test_search(root, 30), nullptr);
//    EXPECT_NE(test_search(root, 70), nullptr);
//    EXPECT_EQ(test_search(root, 10), nullptr);
//    EXPECT_EQ(test_search(root->left, 70), nullptr);
//}
//
//TEST_F(BSearchTreePrivateTest, PrivateInsert) {
//    BTreeNode<int>* root = tree.search(50);
//    ASSERT_NE(root, nullptr);
//
//    root = test_insert(root, 20);
//    root = test_insert(root, 80);
//
//    EXPECT_NE(test_search(root, 20), nullptr);
//    EXPECT_NE(test_search(root, 80), nullptr);
//
//    BTreeNode<int>* newRoot = test_insert(root, 50);
//    EXPECT_EQ(newRoot, root);
//}
//
//TEST_F(BSearchTreePrivateTest, PrivateErase) {
//    BTreeNode<int>* root = tree.search(50);
//    ASSERT_NE(root, nullptr);
//
//    root = test_erase(root, 30);
//    EXPECT_EQ(test_search(root, 30), nullptr);
//
//    root = test_insert(root, 20);
//    root = test_erase(root, 30);
//    EXPECT_EQ(test_search(root, 30), nullptr);
//    EXPECT_NE(test_search(root, 20), nullptr);
//
//    root = test_insert(root, 40);
//    root = test_insert(root, 30);
//    root = test_erase(root, 30);
//    EXPECT_EQ(test_search(root, 30), nullptr);
//    EXPECT_NE(test_search(root, 20), nullptr);
//    EXPECT_NE(test_search(root, 40), nullptr);
//}
//
//TEST_F(BSearchTreePrivateTest, PrivateMinMaxValueNode) {
//    BTreeNode<int>* root = tree.search(50);
//    ASSERT_NE(root, nullptr);
//
//    EXPECT_EQ(test_minValueNode(root)->_value, 30);
//    EXPECT_EQ(test_minValueNode(root->left)->_value, 30);
//    EXPECT_EQ(test_minValueNode(root->right)->_value, 70);
//
//    EXPECT_EQ(test_maxValueNode(root)->_value, 70);
//    EXPECT_EQ(test_maxValueNode(root->left)->_value, 30);
//    EXPECT_EQ(test_maxValueNode(root->right)->_value, 70);
//
//    root = test_insert(root, 20);
//    root = test_insert(root, 80);
//
//    EXPECT_EQ(test_minValueNode(root)->_value, 20);
//    EXPECT_EQ(test_maxValueNode(root)->_value, 80);
//}
//
//TEST_F(BSearchTreePrivateTest, PrivateClear) {
//    BTreeNode<int>* root = new BTreeNode<int>(50);
//    root->left = new BTreeNode<int>(30);
//    root->right = new BTreeNode<int>(70);
//
//    test_clear(root->left);
//    EXPECT_EQ(root->left, nullptr);
//
//    test_clear(root->right);
//    EXPECT_EQ(root->right, nullptr);
//
//    test_clear(root);
//    EXPECT_EQ(root, nullptr);
//}
//
//TEST_F(BSearchTreePrivateTest, PrivatePrint) {
//    BTreeNode<int>* root = tree.search(50);
//    ASSERT_NE(root, nullptr);
//
//    testing::internal::CaptureStdout();
//    test_print(root);
//    std::string output = testing::internal::GetCapturedStdout();
//    EXPECT_EQ(output, "30 50 70 ");
//
//    testing::internal::CaptureStdout();
//    test_print(nullptr);
//    output = testing::internal::GetCapturedStdout();
//    EXPECT_TRUE(output.empty());
//}
//
//class BinarySearchTreeTest : public ::testing::Test {
//protected:
//    BSearchTree<int> tree;
//
//    void SetUp() override {
//        tree.insert(50);
//        tree.insert(30);
//        tree.insert(70);
//        tree.insert(20);
//        tree.insert(40);
//        tree.insert(60);
//        tree.insert(80);
//    }
//};
//
//TEST_F(BinarySearchTreeTest, InitialState) {
//    BSearchTree<int> emptyTree;
//    EXPECT_EQ(emptyTree.search(10), nullptr);
//    EXPECT_EQ(emptyTree.min(), nullptr);
//    EXPECT_EQ(emptyTree.max(), nullptr);
//}
//
//TEST_F(BinarySearchTreeTest, InsertAndSearch) {
//    EXPECT_NE(tree.search(50), nullptr);
//    EXPECT_EQ(tree.search(50)->_value, 50);
//    EXPECT_NE(tree.search(30), nullptr);
//    EXPECT_EQ(tree.search(30)->_value, 30);
//    EXPECT_EQ(tree.search(90), nullptr);
//}
//
//TEST_F(BinarySearchTreeTest, MinMaxOperations) {
//    EXPECT_NE(tree.min(), nullptr);
//    EXPECT_EQ(tree.min()->_value, 20);
//    EXPECT_NE(tree.max(), nullptr);
//    EXPECT_EQ(tree.max()->_value, 80);
//
//    tree.insert(10);
//    EXPECT_EQ(tree.min()->_value, 10);
//    tree.insert(100);
//    EXPECT_EQ(tree.max()->_value, 100);
//}
//
//TEST_F(BinarySearchTreeTest, EraseLeafNode) {
//    tree.erase(20);
//    EXPECT_EQ(tree.search(20), nullptr);
//    EXPECT_NE(tree.search(30), nullptr);
//
//    tree.erase(80);
//    EXPECT_EQ(tree.search(80), nullptr);
//    EXPECT_NE(tree.search(70), nullptr);
//}
//
//TEST_F(BinarySearchTreeTest, EraseNodeWithOneChild) {
//    tree.erase(20);
//    tree.erase(30);
//    EXPECT_EQ(tree.search(30), nullptr);
//    EXPECT_NE(tree.search(40), nullptr);
//    EXPECT_NE(tree.search(50), nullptr);
//}
//
//TEST_F(BinarySearchTreeTest, EraseNodeWithTwoChildren) {
//    tree.erase(50);
//    EXPECT_EQ(tree.search(50), nullptr);
//    EXPECT_NE(tree.search(60), nullptr);
//    EXPECT_NE(tree.search(30), nullptr);
//    EXPECT_NE(tree.search(70), nullptr);
//}
//
//TEST_F(BinarySearchTreeTest, ClearTree) {
//    tree.clear();
//    EXPECT_EQ(tree.search(50), nullptr);
//    EXPECT_EQ(tree.min(), nullptr);
//    EXPECT_EQ(tree.max(), nullptr);
//
//    tree.insert(100);
//    EXPECT_NE(tree.search(100), nullptr);
//}
//
//TEST_F(BinarySearchTreeTest, LevelOrderTraversal) {
//    testing::internal::CaptureStdout();
//    tree.levelOrder();
//    std::string output = testing::internal::GetCapturedStdout();
//    EXPECT_EQ(output, "50 30 70 20 40 60 80 \n");
//
//    BSearchTree<int> emptyTree;
//    testing::internal::CaptureStdout();
//    emptyTree.levelOrder();
//    output = testing::internal::GetCapturedStdout();
//    EXPECT_TRUE(output.empty());
//}
//
//TEST_F(BinarySearchTreeTest, InOrderTraversal) {
//    testing::internal::CaptureStdout();
//    tree.print();
//    std::string output = testing::internal::GetCapturedStdout();
//    EXPECT_EQ(output, "20 30 40 50 60 70 80 \n");
//
//    BSearchTree<int> emptyTree;
//    testing::internal::CaptureStdout();
//    emptyTree.print();
//    output = testing::internal::GetCapturedStdout();
//    EXPECT_EQ(output, "\n");
//}
//
//TEST_F(BinarySearchTreeTest, DuplicateInsert) {
//    tree.insert(50);
//    EXPECT_NE(tree.search(50), nullptr);
//
//    testing::internal::CaptureStdout();
//    tree.print();
//    std::string output = testing::internal::GetCapturedStdout();
//    EXPECT_EQ(output, "20 30 40 50 60 70 80 \n");
//}
//
//TEST_F(BinarySearchTreeTest, ComplexOperations) {
//    BSearchTree<int> bigTree;
//    for (int i = 0; i < 100; ++i) {
//        bigTree.insert(i);
//    }
//
//    EXPECT_EQ(bigTree.min()->_value, 0);
//    EXPECT_EQ(bigTree.max()->_value, 99);
//
//    for (int i = 0; i < 100; i += 2) {
//        bigTree.erase(i);
//    }
//
//    for (int i = 0; i < 100; ++i) {
//        if (i % 2 == 0) {
//            EXPECT_EQ(bigTree.search(i), nullptr);
//        }
//        else {
//            EXPECT_NE(bigTree.search(i), nullptr);
//        }
//    }
//
//    bigTree.clear();
//    EXPECT_EQ(bigTree.min(), nullptr);
//    EXPECT_EQ(bigTree.max(), nullptr);
//}
//
//TEST_F(BinarySearchTreeTest, StringValues) {
//    BSearchTree<std::string> stringTree;
//    stringTree.insert("apple");
//    stringTree.insert("banana");
//    stringTree.insert("cherry");
//
//    EXPECT_NE(stringTree.search("banana"), nullptr);
//    EXPECT_EQ(stringTree.search("banana")->_value, "banana");
//    EXPECT_EQ(stringTree.min()->_value, "apple");
//    EXPECT_EQ(stringTree.max()->_value, "cherry");
//
//    stringTree.erase("banana");
//    EXPECT_EQ(stringTree.search("banana"), nullptr);
//}
//
//TEST_F(BinarySearchTreeTest, EmptyTreeOperations) {
//    BSearchTree<int> emptyTree;
//    EXPECT_EQ(emptyTree.search(10), nullptr);
//    EXPECT_EQ(emptyTree.min(), nullptr);
//    EXPECT_EQ(emptyTree.max(), nullptr);
//    EXPECT_NO_THROW(emptyTree.erase(10));
//
//    testing::internal::CaptureStdout();
//    emptyTree.print();
//    EXPECT_EQ(testing::internal::GetCapturedStdout(), "\n");
//
//    testing::internal::CaptureStdout();
//    emptyTree.levelOrder();
//    EXPECT_TRUE(testing::internal::GetCapturedStdout().empty());
//}