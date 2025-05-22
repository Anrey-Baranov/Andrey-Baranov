#include "gtest.h"
#include "../lib_rbtree/TRBTree.h"
#include <memory>
#include <vector>

template class RBTree<int>;
template class RBTree<std::string>;

class RBTreePrivateTest : public ::testing::Test {
protected:
    RBTree<int> tree;
    std::vector<std::unique_ptr<RBTreeNode<int>>> nodes; // Автоматическое управление памятью

    RBTreeNode<int>* createNode(int val, Color color, RBTreeNode<int>* parent = nullptr) {
        nodes.emplace_back(std::make_unique<RBTreeNode<int>>(val, color, parent));
        return nodes.back().get();
    }

    void TearDown() override {
        nodes.clear();
        tree.clear();
    }


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
    // Создаем тестовое дерево:
    //        50(B)
    //      /      \
    //   30(B)    70(B)
    //   /  \     /   \
    // 20(R)40(R)60(R)80(R)
    RBTreeNode<int>* root = new RBTreeNode<int>(50, BLACK);
    root->left = new RBTreeNode<int>(30, BLACK, root);
    root->right = new RBTreeNode<int>(70, BLACK, root);

    root->left->left = new RBTreeNode<int>(20, RED, root->left);
    root->left->right = new RBTreeNode<int>(40, RED, root->left);

    root->right->left = new RBTreeNode<int>(60, RED, root->right);
    root->right->right = new RBTreeNode<int>(80, RED, root->right);

    // Проверяем поиск существующих узлов
    EXPECT_NE(test_search(root, 20), nullptr);
    EXPECT_EQ(test_search(root, 20)->_value, 20);
    EXPECT_EQ(test_search(root, 20)->color, RED);

    EXPECT_NE(test_search(root, 40), nullptr);
    EXPECT_EQ(test_search(root, 40)->_value, 40);
    EXPECT_EQ(test_search(root, 40)->color, RED);

    EXPECT_NE(test_search(root, 60), nullptr);
    EXPECT_EQ(test_search(root, 60)->_value, 60);
    EXPECT_EQ(test_search(root, 60)->color, RED);

    EXPECT_NE(test_search(root, 80), nullptr);
    EXPECT_EQ(test_search(root, 80)->_value, 80);
    EXPECT_EQ(test_search(root, 80)->color, RED);

    // Проверяем поиск несуществующих узлов
    EXPECT_EQ(test_search(root, 10), nullptr);
    EXPECT_EQ(test_search(root, 90), nullptr);
    EXPECT_EQ(test_search(root, 35), nullptr);

    // Проверяем поиск корня и промежуточных узлов
    EXPECT_NE(test_search(root, 50), nullptr);
    EXPECT_EQ(test_search(root, 50)->_value, 50);
    EXPECT_EQ(test_search(root, 50)->color, BLACK);

    EXPECT_NE(test_search(root, 30), nullptr);
    EXPECT_EQ(test_search(root, 30)->_value, 30);
    EXPECT_EQ(test_search(root, 30)->color, BLACK);

    EXPECT_NE(test_search(root, 70), nullptr);
    EXPECT_EQ(test_search(root, 70)->_value, 70);
    EXPECT_EQ(test_search(root, 70)->color, BLACK);

}

TEST_F(RBTreePrivateTest, PrivateInsertHelper) {
    // Создаем начальное дерево с корнем
    RBTreeNode<int>* root = new RBTreeNode<int>(50, BLACK);

    // 1. Вставляем левого потомка
    RBTreeNode<int>* node1 = new RBTreeNode<int>(30, RED);
    root = test_insert(root, node1);

    // Проверяем структуру
    EXPECT_EQ(root->_value, 50);
    EXPECT_NE(root->left, nullptr);
    EXPECT_EQ(root->left->_value, 30);
    EXPECT_EQ(root->left->parent, root);
    EXPECT_EQ(root->left->color, RED);
    EXPECT_EQ(root->right, nullptr);

    // 2. Вставляем правого потомка
    RBTreeNode<int>* node2 = new RBTreeNode<int>(70, RED);
    root = test_insert(root, node2);

    // Проверяем структуру
    EXPECT_EQ(root->_value, 50);
    EXPECT_NE(root->right, nullptr);
    EXPECT_EQ(root->right->_value, 70);
    EXPECT_EQ(root->right->parent, root);
    EXPECT_EQ(root->right->color, RED);

    // 3. Проверяем что левый потомок не изменился
    EXPECT_NE(root->left, nullptr);
    EXPECT_EQ(root->left->_value, 30);

}

TEST_F(RBTreePrivateTest, PrivateRotateLeft) {
    // Исходное дерево:
    //     30(B)
    //       \
    //      50(R)
    //        \
    //       70(R)
    RBTreeNode<int>* root = new RBTreeNode<int>(30, BLACK);
    RBTreeNode<int>* child = new RBTreeNode<int>(50, RED, root);
    root->right = child;
    child->right = new RBTreeNode<int>(70, RED, child);

    test_rotateLeft(root);

    // После ротации:
    //     50(B)
    //    /    \
    // 30(R)  70(R)
    ASSERT_NE(root->parent, nullptr);
    EXPECT_EQ(root->parent->_value, 50);
    EXPECT_EQ(root->parent->color, BLACK); // Новый корень должен быть черным
    EXPECT_EQ(root->parent->left, root);
    EXPECT_EQ(root->parent->left->color, RED);
    EXPECT_EQ(root->parent->right->_value, 70);
    EXPECT_EQ(root->parent->right->color, RED);
    EXPECT_EQ(root->right, nullptr);

}

TEST_F(RBTreePrivateTest, PrivateRotateRight) {
    // Исходное дерево:
    //       50(B)
    //      /
    //   30(R)
    //   /
    //10(R)
    RBTreeNode<int>* root = new RBTreeNode<int>(50, BLACK);
    RBTreeNode<int>* child = new RBTreeNode<int>(30, RED, root);
    root->left = child;
    child->left = new RBTreeNode<int>(10, RED, child);

    test_rotateRight(root);

    // После ротации:
    //     30(B)
    //    /    \
    // 10(R)  50(R)
    RBTreeNode<int>* newRoot = root->parent;
    ASSERT_NE(newRoot, nullptr);
    EXPECT_EQ(newRoot->_value, 30);
    EXPECT_EQ(newRoot->color, BLACK); // Новый корень должен быть черным
    EXPECT_EQ(newRoot->left->_value, 10);
    EXPECT_EQ(newRoot->left->color, RED);
    EXPECT_EQ(newRoot->right->_value, 50);
    EXPECT_EQ(newRoot->right->color, RED);

}

TEST_F(RBTreePrivateTest, PrivateFixInsertCase1) {
    // Исходное дерево:
    //       50(B)
    //      /    \
    //   30(R)  70(R)
    RBTreeNode<int>* root = new RBTreeNode<int>(50, BLACK);
    RBTreeNode<int>* node30 = new RBTreeNode<int>(30, RED, root);
    RBTreeNode<int>* node70 = new RBTreeNode<int>(70, RED, root);
    root->left = node30;
    root->right = node70;

    // Добавляем новый узел (случай 1 - дядя красный)
    RBTreeNode<int>* newNode = new RBTreeNode<int>(20, RED, node30);
    node30->left = newNode;
    tree.setRoot(root);
    test_fixInsert(newNode);

    // Проверяем перекрашивание:
    EXPECT_EQ(root->color, BLACK);
    EXPECT_EQ(node30->color, BLACK); // Должен стать черным
    EXPECT_EQ(node70->color, BLACK); // Должен стать черным
    EXPECT_EQ(newNode->color, RED);  // Остается красным

}

TEST_F(RBTreePrivateTest, PrivateFixInsertCase2And3) {
    // Исходное дерево:
    //       50(B)
    //      /
    //   30(R)
    RBTreeNode<int>* root = new RBTreeNode<int>(50, BLACK);
    RBTreeNode<int>* node30 = new RBTreeNode<int>(30, RED, root);
    root->left = node30;

    tree.setRoot(root);

    // Добавляем новый узел (случай 2 и 3)
    RBTreeNode<int>* newNode = new RBTreeNode<int>(20, RED, node30);
    node30->left = newNode;

    test_fixInsert(newNode);

    // После балансировки:
    //     30(B)
    //    /    \
    // 20(R)  50(R)
    RBTreeNode<int>* newRoot = tree.getRoot();
    ASSERT_NE(newRoot, nullptr);

    EXPECT_EQ(newRoot->_value, 30);
    EXPECT_EQ(newRoot->color, BLACK); // Новый корень должен быть черным
    EXPECT_EQ(newRoot->left->_value, 20);
    EXPECT_EQ(newRoot->left->color, RED);
    EXPECT_EQ(newRoot->right->_value, 50);
    EXPECT_EQ(newRoot->right->color, RED);
}

TEST_F(RBTreePrivateTest, PrivateMinMaxValueNode) {
    // Создаем тестовое дерево:
    //        50(B)
    //      /      \
    //   30(B)    70(B)
    //   /  \     /   \
    // 20(R)40(R)60(R)80(R)
    RBTreeNode<int>* root = new RBTreeNode<int>(50, BLACK);
    root->left = new RBTreeNode<int>(30, BLACK, root);
    root->right = new RBTreeNode<int>(70, BLACK, root);
    root->left->left = new RBTreeNode<int>(20, RED, root->left);
    root->left->right = new RBTreeNode<int>(40, RED, root->left);
    root->right->left = new RBTreeNode<int>(60, RED, root->right);
    root->right->right = new RBTreeNode<int>(80, RED, root->right);

    // Проверяем минимальное и максимальное значения
    EXPECT_EQ(test_minValueNode(root)->_value, 20);
    EXPECT_EQ(test_minValueNode(root)->color, RED);

    EXPECT_EQ(test_maxValueNode(root)->_value, 80);
    EXPECT_EQ(test_maxValueNode(root)->color, RED);

    EXPECT_EQ(test_minValueNode(root->right)->_value, 60);
    EXPECT_EQ(test_minValueNode(root->right)->color, RED);

    EXPECT_EQ(test_maxValueNode(root->left)->_value, 40);
    EXPECT_EQ(test_maxValueNode(root->left)->color, RED);
}

TEST_F(RBTreePrivateTest, PrivateTransplant) {
    // Создаем тестовое дерево:
    //       50(B)
    //      /     \
    //   30(R)   70(R)
    //   /  \    /  \
    // 20(B)40(B)60(B)80(B)
    RBTreeNode<int>* root = new RBTreeNode<int>(50, BLACK);
    RBTreeNode<int>* node30 = new RBTreeNode<int>(30, RED, root);
    RBTreeNode<int>* node70 = new RBTreeNode<int>(70, RED, root);
    root->left = node30;
    root->right = node70;

    node30->left = new RBTreeNode<int>(20, BLACK, node30);
    node30->right = new RBTreeNode<int>(40, BLACK, node30);
    node70->left = new RBTreeNode<int>(60, BLACK, node70);
    node70->right = new RBTreeNode<int>(80, BLACK, node70);

    // Сохраняем оригинальные дочерние узлы node30
    RBTreeNode<int>* origLeft = node30->left;
    RBTreeNode<int>* origRight = node30->right;

    // Создаем новое поддерево для трансплантации:
    //     35(B)
    //    /   \
    // 25(R) 45(R)
    RBTreeNode<int>* newSubtree = new RBTreeNode<int>(35, BLACK);
    newSubtree->left = new RBTreeNode<int>(25, RED, newSubtree);
    newSubtree->right = new RBTreeNode<int>(45, RED, newSubtree);

    // Выполняем трансплантацию - заменяем node30 на newSubtree
    test_transplant(node30, newSubtree);

    // Проверки:

    // 1. Проверяем что родительские связи обновлены
    EXPECT_EQ(newSubtree->parent, root);
    EXPECT_EQ(root->left, newSubtree);

    // 2. Проверяем что оригинальные дети node30 больше не связаны с newSubtree
    EXPECT_NE(newSubtree->left, origLeft);
    EXPECT_NE(newSubtree->right, origRight);

    // 3. Проверяем что структура newSubtree сохранилась
    ASSERT_NE(newSubtree->left, nullptr);
    ASSERT_NE(newSubtree->right, nullptr);
    EXPECT_EQ(newSubtree->left->_value, 25);
    EXPECT_EQ(newSubtree->right->_value, 45);
    EXPECT_EQ(newSubtree->left->parent, newSubtree);
    EXPECT_EQ(newSubtree->right->parent, newSubtree);

    // 4. Проверяем что цвета сохранились
    EXPECT_EQ(newSubtree->color, BLACK);
    EXPECT_EQ(newSubtree->left->color, RED);
    EXPECT_EQ(newSubtree->right->color, RED);

    // 5. Проверяем другую часть дерева (node70) не изменилась
    EXPECT_EQ(root->right, node70);
    EXPECT_EQ(node70->parent, root);
    EXPECT_EQ(node70->left->_value, 60);
    EXPECT_EQ(node70->right->_value, 80);

    // Удаляем старый узел node30 и его поддерево
    delete origLeft;
    delete origRight;
    delete node30;
}

TEST_F(RBTreePrivateTest, PrivateFixDeleteCases) {
    // Создаем корректное тестовое дерево:
    //        50(B)
    //      /      \
    //   30(B)    70(B)  
    //     \      /   \
    //    40(R) 60(R)80(R) 
    RBTreeNode<int>* root = new RBTreeNode<int>(50, BLACK);
    RBTreeNode<int>* node30 = new RBTreeNode<int>(30, BLACK, root);
    RBTreeNode<int>* node70 = new RBTreeNode<int>(70, BLACK, root); 
    root->left = node30;
    root->right = node70;

    node30->right = new RBTreeNode<int>(40, RED, node30);
    node70->left = new RBTreeNode<int>(60, RED, node70);  
    node70->right = new RBTreeNode<int>(80, RED, node70); 

    // Устанавливаем корень дерева
    tree.setRoot(root);

    // Симулируем ситуацию после удаления (двойной чёрный узел)
    RBTreeNode<int>* x = node30->left;
    if (x == nullptr) {
        x = new RBTreeNode<int>(0, BLACK);
        x->parent = node30;
        node30->left = x;
    }

    test_fixDelete(x);

    // Проверки
    EXPECT_EQ(root->color, BLACK);
    EXPECT_EQ(node70->color, BLACK); 

    if (node30->right != nullptr) {
        EXPECT_EQ(node30->right->color, RED); // 40 остаётся красным
    }

    // Проверяем, что дети 70 остались красными
    EXPECT_EQ(node70->left->_value, 60);
    EXPECT_EQ(node70->left->color, RED);  
    EXPECT_EQ(node70->right->_value, 80);
    EXPECT_EQ(node70->right->color, RED); 
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
    tree.insert(50);  // Дубликат не будет добавлен
    auto node = tree.search(50);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->_value, 50);
    EXPECT_EQ(node->left, nullptr);   // Проверяем, что нет левого потомка
    EXPECT_EQ(node->right, nullptr);  // Проверяем, что нет правого потомка
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

    // Проверяем что удаленный узел больше не существует
    EXPECT_EQ(tree.search(50), nullptr);

    // Проверяем что остальные узлы на месте
    EXPECT_NE(tree.search(30), nullptr);
    EXPECT_NE(tree.search(70), nullptr);
    EXPECT_NE(tree.search(20), nullptr);
    EXPECT_NE(tree.search(40), nullptr);
    EXPECT_NE(tree.search(60), nullptr);
    EXPECT_NE(tree.search(80), nullptr);

}

TEST_F(RBTreeTest, EraseRoot) {
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);

    tree.erase(50);

    EXPECT_EQ(tree.search(50), nullptr);
    EXPECT_NE(tree.search(30), nullptr);
    EXPECT_NE(tree.search(70), nullptr);

    // Проверяем что новый корень черный
    auto root = tree.getRoot();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->color, BLACK);
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
    //EXPECT_NO_THROW(emptyTree.print());
}