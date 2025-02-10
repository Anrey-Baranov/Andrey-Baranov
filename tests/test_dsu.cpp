#include <gtest.h>
#include "dsu.h"

class TestDSU : public ::testing::Test {
protected:
    DSU dsu;

    TestDSU() : dsu(6) {  // ������� DSU � 6 ����������
        dsu.make_set(1);
        dsu.make_set(2);
        dsu.make_set(3);
        dsu.make_set(4);
        dsu.make_set(5);
        dsu.make_set(6);
    }
};

TEST_F(TestDSU, TestMakeSet) {
    EXPECT_NO_THROW(dsu.make_set(5)); // ��������� �������� ��������� ��� ������������� ��������
    EXPECT_NO_THROW(dsu.make_set(7)); // ��������� �������� ������ ���������
}

TEST_F(TestDSU, TestFind) {
    EXPECT_EQ(dsu.find(1), 1); // ���������, ��� ������� 1 ��������� �� ����
    EXPECT_EQ(dsu.find(2), 2); // ���������, ��� ������� 2 ��������� �� ����
}

TEST_F(TestDSU, TestUnion) {
    dsu.union_sets(1, 2); // ���������� 1 � 2
    EXPECT_EQ(dsu.find(1), dsu.find(2)); // ���������, ��� 1 � 2 ������ � ����� ���������

    dsu.union_sets(3, 4); // ���������� 3 � 4
    EXPECT_EQ(dsu.find(3), dsu.find(4)); // ���������, ��� 3 � 4 ������ � ����� ���������

    dsu.union_sets(2, 3); // ���������� 2 � 3
    EXPECT_EQ(dsu.find(1), dsu.find(3)); // ���������, ��� 1 � 3 ������ � ����� ���������
}

TEST_F(TestDSU, TestUnionDifferentSets) {
    dsu.union_sets(1, 2);
    dsu.union_sets(3, 4);
    EXPECT_NE(dsu.find(1), dsu.find(3)); // ���������, ��� 1 � 3 ��� ��� � ������ ����������
}

TEST_F(TestDSU, TestInvalidFind) {
    EXPECT_THROW(dsu.find(0), std::logic_error); // �������� �� ����� �� �������
    EXPECT_THROW(dsu.find(7), std::logic_error); // �������� �� ����� �� �������
}

TEST_F(TestDSU, TestInvalidUnion) {
    EXPECT_THROW(dsu.union_sets(0, 1), std::logic_error); // �������� �� ����� �� �������
    EXPECT_THROW(dsu.union_sets(1, 7), std::logic_error); // �������� �� ����� �� �������
}

TEST_F(TestDSU, TestMakeSetOutOfBounds) {
    EXPECT_THROW(dsu.make_set(0), std::logic_error); // �������� �� ����� �� �������
    EXPECT_THROW(dsu.make_set(7), std::logic_error); // �������� �� ����� �� �������
}
