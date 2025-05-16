//#include "gtest.h"
//#include "TBinSearchTree.h"
//
//template class BSearchTree<int>;
//
//class BSearchTreePrivateTest : public ::testing::Test {
//protected:
//    BSearchTree<int> tree;
//
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
//    std::string test_inOrderTraversal(BTreeNode<int>* node) const {
//        return tree._inOrderTraversal(node);
//    }
//};
//
//TEST_F(BSearchTreePrivateTest, PrivateSearch) {
//    BTreeNode<int>* root = test_insert(nullptr, 50);
//    root = test_insert(root, 30);
//    root = test_insert(root, 70);
//
//    // Проверка поиска существующих элементов
//    BTreeNode<int>* found30 = test_search(root, 30);
//    ASSERT_NE(found30, nullptr);
//    EXPECT_EQ(found30->_value, 30);
//    EXPECT_EQ(found30->left, nullptr);
//    EXPECT_EQ(found30->right, nullptr);
//
//    BTreeNode<int>* found70 = test_search(root, 70);
//    ASSERT_NE(found70, nullptr);
//    EXPECT_EQ(found70->_value, 70);
//    EXPECT_EQ(found70->left, nullptr);
//    EXPECT_EQ(found70->right, nullptr);
//
//    // Проверка поиска несуществующих элементов
//    EXPECT_EQ(test_search(root, 10), nullptr);
//    EXPECT_EQ(test_search(root->left, 70), nullptr);
//}
//
//TEST_F(BSearchTreePrivateTest, PrivateInsert) {
//    BTreeNode<int>* root = test_insert(nullptr, 50);
//    root = test_insert(root, 30);
//    root = test_insert(root, 70);
//
//    // Проверка вставки новых элементов
//    root = test_insert(root, 20);
//    root = test_insert(root, 80);
//
//    // Проверка значений и путей
//    BTreeNode<int>* found20 = test_search(root, 20);
//    ASSERT_NE(found20, nullptr);
//    EXPECT_EQ(found20->_value, 20);
//    EXPECT_EQ(root->left->left, found20);
//
//    BTreeNode<int>* found80 = test_search(root, 80);
//    ASSERT_NE(found80, nullptr);
//    EXPECT_EQ(found80->_value, 80);
//    EXPECT_EQ(root->right->right, found80);
//
//    // Проверка вставки дубликата
//    BTreeNode<int>* newRoot = test_insert(root, 50);
//    EXPECT_EQ(newRoot, root);
//    EXPECT_EQ(root->_value, 50);
//}
//
//TEST_F(BSearchTreePrivateTest, PrivateErase) {
//    BTreeNode<int>* root = test_insert(nullptr, 50);
//    root = test_insert(root, 30);
//    root = test_insert(root, 70);
//
//    // Удаление листа
//    root = test_erase(root, 30);
//    EXPECT_EQ(test_search(root, 30), nullptr);
//    EXPECT_NE(test_search(root, 50), nullptr);
//    EXPECT_NE(test_search(root, 70), nullptr);
//    
//
//    // Вставка и удаление другого листа
//    root = test_insert(root, 20);
//    root = test_erase(root, 20);
//    EXPECT_EQ(test_search(root, 20), nullptr);
//    EXPECT_NE(test_search(root, 50), nullptr);
//
//    // Удаление узла с двумя детьми
//    root = test_insert(root, 30);
//    
//    root = test_insert(root, 40);
//    root = test_insert(root, 20);
//    root = test_erase(root, 30);
//    // После удаления 30
//    ASSERT_NE(root->left, nullptr);
//    EXPECT_EQ(root->left->_value, 40);  // Проверка что 40 занял место 30
//    ASSERT_NE(root->left->left, nullptr);
//    EXPECT_EQ(root->left->left->_value, 20);
//
//    EXPECT_EQ(test_search(root, 30), nullptr);
//    EXPECT_NE(test_search(root, 20), nullptr);
//    EXPECT_NE(test_search(root, 40), nullptr);
//    EXPECT_NE(test_search(root, 50), nullptr);
//}
//
//TEST_F(BSearchTreePrivateTest, PrivateMinMaxValueNode) {
//    BTreeNode<int>* root = test_insert(nullptr, 50);
//    root = test_insert(root, 30);
//    root = test_insert(root, 70);
//
//    // Проверка минимального и максимального значений
//    EXPECT_EQ(test_minValueNode(root)->_value, 30);
//    EXPECT_EQ(test_minValueNode(root->left)->_value, 30);
//    EXPECT_EQ(test_minValueNode(root->right)->_value, 70);
//
//    EXPECT_EQ(test_maxValueNode(root)->_value, 70);
//    EXPECT_EQ(test_maxValueNode(root->left)->_value, 30);
//    EXPECT_EQ(test_maxValueNode(root->right)->_value, 70);
//
//    // Добавление новых элементов и проверка
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
//    // Проверка очистки левого поддерева
//    test_clear(root->left);
//    EXPECT_EQ(root->left, nullptr);
//    EXPECT_NE(root->right, nullptr);
//
//    // Проверка очистки правого поддерева
//    test_clear(root->right);
//    EXPECT_EQ(root->right, nullptr);
//
//    // Проверка очистки всего дерева
//    test_clear(root);
//    EXPECT_EQ(root, nullptr);
//}
//
//TEST_F(BSearchTreePrivateTest, PrivateInOrderTraversal) {
//    BTreeNode<int>* root = test_insert(nullptr, 50);
//    root = test_insert(root, 30);
//    root = test_insert(root, 70);
//
//    // Проверка обхода дерева
//    EXPECT_EQ(test_inOrderTraversal(root), "30 50 70 ");
//
//    // Проверка пустого дерева
//    EXPECT_TRUE(test_inOrderTraversal(nullptr).empty());
//}
//
//class BinarySearchTreeTest : public ::testing::Test {
//protected:
//    BSearchTree<int> tree;
//};
//
//TEST_F(BinarySearchTreeTest, InitialState) {
//    EXPECT_EQ(tree.search(10), nullptr);
//    EXPECT_EQ(tree.min(), nullptr);
//    EXPECT_EQ(tree.max(), nullptr);
//    EXPECT_EQ(tree.inOrderTraversal(), "");
//}
//
//TEST_F(BinarySearchTreeTest, InsertAndSearch) {
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//    tree.insert(20);
//    tree.insert(40);
//    tree.insert(60);
//    tree.insert(80);
//
//    // Проверка поиска существующих элементов
//    BTreeNode<int>* found50 = tree.search(50);
//    ASSERT_NE(found50, nullptr);
//    EXPECT_EQ(found50->_value, 50);
//    EXPECT_NE(found50->left, nullptr);
//    EXPECT_NE(found50->right, nullptr);
//
//    BTreeNode<int>* found30 = tree.search(30);
//    ASSERT_NE(found30, nullptr);
//    EXPECT_EQ(found30->_value, 30);
//    EXPECT_NE(found30->left, nullptr);
//    EXPECT_NE(found30->right, nullptr);
//
//    // Проверка поиска несуществующего элемента
//    EXPECT_EQ(tree.search(90), nullptr);
//}
//
//TEST_F(BinarySearchTreeTest, MinMaxOperations) {
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//    tree.insert(20);
//    tree.insert(40);
//    tree.insert(60);
//    tree.insert(80);
//
//    // Проверка минимального и максимального элементов
//    BTreeNode<int>* minNode = tree.min();
//    ASSERT_NE(minNode, nullptr);
//    EXPECT_EQ(minNode->_value, 20);
//
//    BTreeNode<int>* maxNode = tree.max();
//    ASSERT_NE(maxNode, nullptr);
//    EXPECT_EQ(maxNode->_value, 80);
//
//    // Добавление новых минимального и максимального элементов
//    tree.insert(10);
//    minNode = tree.min();
//    ASSERT_NE(minNode, nullptr);
//    EXPECT_EQ(minNode->_value, 10);
//
//    tree.insert(100);
//    maxNode = tree.max();
//    ASSERT_NE(maxNode, nullptr);
//    EXPECT_EQ(maxNode->_value, 100);
//}
//
//TEST_F(BinarySearchTreeTest, EraseLeafNode) {
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//    tree.insert(20);
//    tree.insert(40);
//    tree.insert(60);
//    tree.insert(80);
//
//    // Удаление листа и проверка структуры дерева
//    tree.erase(20);
//    EXPECT_EQ(tree.search(20), nullptr);
//    BTreeNode<int>* parent30 = tree.search(30);
//    ASSERT_NE(parent30, nullptr);
//    EXPECT_EQ(parent30->left, nullptr);
//    EXPECT_NE(parent30->right, nullptr);
//
//    tree.erase(80);
//    EXPECT_EQ(tree.search(80), nullptr);
//    BTreeNode<int>* parent70 = tree.search(70);
//    ASSERT_NE(parent70, nullptr);
//    EXPECT_NE(parent70->left, nullptr);
//    EXPECT_EQ(parent70->right, nullptr);
//}
//
//TEST_F(BinarySearchTreeTest, EraseNodeWithOneChild) {
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//    tree.insert(20);
//    tree.insert(40);
//    tree.insert(60);
//    tree.insert(80);
//
//    // Удаление узла с одним потомком
//    tree.erase(20);
//    tree.erase(30);
//    EXPECT_EQ(tree.search(30), nullptr);
//    BTreeNode<int>* parent50 = tree.search(50);
//    ASSERT_NE(parent50, nullptr);
//    EXPECT_NE(parent50->left, nullptr);
//    EXPECT_EQ(parent50->left->_value, 40);
//}
//
//TEST_F(BinarySearchTreeTest, EraseNodeWithTwoChildren) {
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//    tree.insert(20);
//    tree.insert(40);
//    tree.insert(60);
//    tree.insert(80);
//
//    // Удаление узла с двумя потомками
//    tree.erase(50);
//    EXPECT_EQ(tree.search(50), nullptr);
//    BTreeNode<int>* newRoot = tree.getRoot();
//    ASSERT_NE(newRoot, nullptr);
//    EXPECT_EQ(newRoot->_value, 60);
//    EXPECT_NE(newRoot->left, nullptr);
//    EXPECT_NE(newRoot->right, nullptr);
//}
//
//TEST_F(BinarySearchTreeTest, ClearTree) {
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//    tree.insert(20);
//    tree.insert(40);
//    tree.insert(60);
//    tree.insert(80);
//
//    // Проверка очистки дерева
//    tree.clear();
//    EXPECT_EQ(tree.getRoot(), nullptr);
//    EXPECT_EQ(tree.search(50), nullptr);
//    EXPECT_EQ(tree.min(), nullptr);
//    EXPECT_EQ(tree.max(), nullptr);
//
//    // Проверка работы после очистки
//    tree.insert(100);
//    EXPECT_NE(tree.search(100), nullptr);
//    EXPECT_EQ(tree.inOrderTraversal(), "100 ");
//}
//
//TEST_F(BinarySearchTreeTest, LevelOrderTraversal) {
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//    tree.insert(20);
//    tree.insert(40);
//    tree.insert(60);
//    tree.insert(80);
//
//    // Проверка обхода в ширину
//    testing::internal::CaptureStdout();
//    tree.levelOrder();
//    std::string output = testing::internal::GetCapturedStdout();
//    EXPECT_EQ(output, "50 30 70 20 40 60 80 \n");
//
//    // Проверка пустого дерева
//    BSearchTree<int> emptyTree;
//    testing::internal::CaptureStdout();
//    emptyTree.levelOrder();
//    output = testing::internal::GetCapturedStdout();
//    EXPECT_TRUE(output.empty());
//}
//
//TEST_F(BinarySearchTreeTest, InOrderTraversal) {
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//    tree.insert(20);
//    tree.insert(40);
//    tree.insert(60);
//    tree.insert(80);
//
//    // Проверка симметричного обхода
//    EXPECT_EQ(tree.inOrderTraversal(), "20 30 40 50 60 70 80 ");
//
//    // Проверка пустого дерева
//    BSearchTree<int> emptyTree;
//    EXPECT_EQ(emptyTree.inOrderTraversal(), "");
//}
//
//TEST_F(BinarySearchTreeTest, DuplicateInsert) {
//    tree.insert(50);
//    tree.insert(30);
//    tree.insert(70);
//    tree.insert(20);
//    tree.insert(40);
//    tree.insert(60);
//    tree.insert(80);
//
//    // Проверка вставки дубликата
//    tree.insert(50);
//    BTreeNode<int>* found50 = tree.search(50);
//    ASSERT_NE(found50, nullptr);
//    EXPECT_EQ(found50->_value, 50);
//    EXPECT_EQ(tree.inOrderTraversal(), "20 30 40 50 60 70 80 ");
//}
//
//TEST_F(BinarySearchTreeTest, ComplexOperations) {
//    BSearchTree<int> bigTree;
//    // Заполнение дерева
//    for (int i = 0; i < 100; ++i) {
//        bigTree.insert(i);
//    }
//
//    // Проверка минимального и максимального элементов
//    EXPECT_EQ(bigTree.min()->_value, 0);
//    EXPECT_EQ(bigTree.max()->_value, 99);
//
//    // Удаление четных элементов
//    for (int i = 0; i < 100; i += 2) {
//        bigTree.erase(i);
//    }
//
//    // Проверка наличия/отсутствия элементов
//    for (int i = 0; i < 100; ++i) {
//        if (i % 2 == 0) {
//            EXPECT_EQ(bigTree.search(i), nullptr);
//        }
//        else {
//            EXPECT_NE(bigTree.search(i), nullptr);
//        }
//    }
//
//    // Очистка и проверка
//    bigTree.clear();
//    EXPECT_EQ(bigTree.getRoot(), nullptr);
//    EXPECT_EQ(bigTree.min(), nullptr);
//    EXPECT_EQ(bigTree.max(), nullptr);
//}
//
//TEST_F(BinarySearchTreeTest, StringValues) {
//    BSearchTree<std::string> stringTree;
//    // Вставка строк
//    stringTree.insert("apple");
//    stringTree.insert("banana");
//    stringTree.insert("cherry");
//
//    // Проверка поиска и порядка
//    EXPECT_NE(stringTree.search("banana"), nullptr);
//    EXPECT_EQ(stringTree.search("banana")->_value, "banana");
//    EXPECT_EQ(stringTree.min()->_value, "apple");
//    EXPECT_EQ(stringTree.max()->_value, "cherry");
//    EXPECT_EQ(stringTree.inOrderTraversal(), "apple banana cherry ");
//
//    // Удаление и проверка
//    stringTree.erase("banana");
//    EXPECT_EQ(stringTree.search("banana"), nullptr);
//    EXPECT_EQ(stringTree.inOrderTraversal(), "apple cherry ");
//}
//
//TEST_F(BinarySearchTreeTest, EmptyTreeOperations) {
//    BSearchTree<int> emptyTree;
//    // Проверка операций на пустом дереве
//    EXPECT_EQ(emptyTree.getRoot(), nullptr);
//    EXPECT_EQ(emptyTree.search(10), nullptr);
//    EXPECT_EQ(emptyTree.min(), nullptr);
//    EXPECT_EQ(emptyTree.max(), nullptr);
//    EXPECT_NO_THROW(emptyTree.erase(10));
//    EXPECT_EQ(emptyTree.inOrderTraversal(), "");
//
//    // Проверка вывода пустого дерева
//    testing::internal::CaptureStdout();
//    emptyTree.print();
//    EXPECT_EQ(testing::internal::GetCapturedStdout(), "\n");
//
//    testing::internal::CaptureStdout();
//    emptyTree.levelOrder();
//    EXPECT_TRUE(testing::internal::GetCapturedStdout().empty());
//}