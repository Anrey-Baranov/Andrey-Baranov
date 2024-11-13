#include <gtest.h>
#include "../lib_pair/TPair.h"
#include "iostream"

class TestPairLib : public ::testing::Test {
protected:
	TPair<int, int> pair1 = TPair<int, int>(3, 10);
	TPair<int, int> pair2 = TPair<int, int>(2, 5);
};

TEST(TestTPairLib, check_func_make_pair) {
	TPair<int, double> pair;
	pair.make_pair(3, 5.2);
	EXPECT_EQ(pair.first(), 3);
	EXPECT_EQ(pair.second(), 5.2);
}

TEST_F(TestPairLib, check_func_assign) {
	pair1 = pair2;
	EXPECT_EQ(pair1.first(), 2);
	EXPECT_EQ(pair1.second(), 5);
}

TEST_F(TestPairLib, check_func_assign_sub) {
	pair1 -= pair2;
	EXPECT_EQ(pair1.first(), 1);
	EXPECT_EQ(pair1.second(), 5);
}

TEST_F(TestPairLib, check_func_add) {
	TPair<int, int> pair3;
	pair3 = pair1 + pair2;
	EXPECT_EQ(pair3.first(), 5);
	EXPECT_EQ(pair3.second(), 15);
}

TEST_F(TestPairLib, check_not_eq) {
	EXPECT_EQ(pair1!=pair2, true);
}

TEST_F(TestPairLib, check_not_eq_not) {
	TPair<int, int> pair2 = TPair<int, int>(3, 10);
	EXPECT_EQ(pair1 != pair2, false);
}

TEST_F(TestPairLib, check_eq) {
	TPair<int, int> pair2 = TPair<int, int>(3, 10);
	EXPECT_EQ(pair1 == pair2, true);
}

TEST_F(TestPairLib, check_eq_not) {
	EXPECT_EQ(pair1 == pair2, false);
}

TEST_F(TestPairLib, check_gt) {
	EXPECT_EQ(pair1 >= pair2, true);
}

TEST_F(TestPairLib, check_gt_eq) {
	TPair<int, int> pair2 = TPair<int, int>(3, 10);
	EXPECT_EQ(pair1 >= pair2, true);
}

TEST_F(TestPairLib, check_not_gt) {
	TPair<int, int> pair3 = TPair<int, int>(5, 10);
	EXPECT_EQ(pair1 >= pair3, false);
	TPair<int, int> pair4 = TPair<int, int>(3, 11);
	EXPECT_EQ(pair1 >= pair4, false);
}

TEST_F(TestPairLib, check_ls) {
	TPair<int, int> pair3 = TPair<int, int>(3, 10);
	EXPECT_EQ(pair1 <= pair3, true);
}

TEST_F(TestPairLib, check_swap) {
	pair1.swap(pair2);
	EXPECT_EQ(pair1.first(), 2); EXPECT_EQ(pair1.second(), 5);
	EXPECT_EQ(pair2.first(), 3); EXPECT_EQ(pair2.second(), 10);
}

TEST_F(TestPairLib, check_func_sub) {
	TPair<int, int> pair3;
	pair3 = pair1 - pair2;
	EXPECT_EQ(pair3.first(), 1);
	EXPECT_EQ(pair3.second(), 5);
}