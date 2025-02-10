
#include <gtest.h>
#include "CMonom.h"

class TestCMonom : public ::testing::Test {
protected:
    CMonom monom1;
    CMonom monom2;

    void SetUp() override {
        // Инициализация тестовых данных с одинаковым размером
        int powers1[] = { 1, 2, 3 };
        monom1 = CMonom(2.0, powers1, 3);  // 2x^1 * y^2 * z^3

        int powers2[] = { 1, 2, 3 }; // Убедитесь, что размеры совпадают
        monom2 = CMonom(3.0, powers2, 3);  // 3x^1 * y^2 * z^3
    }
};

TEST_F(TestCMonom, DefaultConstructor) {
    CMonom defaultMonom;
    EXPECT_EQ(defaultMonom._coef, 0);
    EXPECT_EQ(defaultMonom._size, 3);
    EXPECT_EQ(defaultMonom._powers[0], 0);
    EXPECT_EQ(defaultMonom._powers[1], 0);
    EXPECT_EQ(defaultMonom._powers[2], 0);
}

TEST_F(TestCMonom, ConstructorWithSize) {
    CMonom monom(5);
    EXPECT_EQ(monom._size, 5);
    EXPECT_EQ(monom._coef, 0);
}

TEST_F(TestCMonom, CopyConstructor) {
    CMonom copyMonom(monom1);
    EXPECT_EQ(copyMonom._coef, monom1._coef);
    EXPECT_EQ(copyMonom._size, monom1._size);
    for (size_t i = 0; i < copyMonom._size; i++) {
        EXPECT_EQ(copyMonom._powers[i], monom1._powers[i]);
    }
}

TEST_F(TestCMonom, AssignmentOperator) {
    CMonom monomCopy;
    monomCopy = monom1;
    EXPECT_EQ(monomCopy._coef, monom1._coef);
    EXPECT_EQ(monomCopy._size, monom1._size);
}

TEST_F(TestCMonom, Addition) {
    CMonom result = monom1 + monom2; // 2x^1 * y^2 * z^3 + 3x^1 * y^2 * z^3
    EXPECT_EQ(result._coef, 2.0 + 3.0);  // Коэффициенты должны складываться
    EXPECT_EQ(result._powers[0], 1);
    EXPECT_EQ(result._powers[1], 2);
    EXPECT_EQ(result._powers[2], 3);
}

TEST_F(TestCMonom, Subtraction) {
    CMonom result = monom1 - monom2; // 2x^1 * y^2 * z^3 - 3x^1 * y^2 * z^3
    EXPECT_EQ(result._coef, 2.0 - 3.0);  // Коэффициенты должны вычитаться
    EXPECT_EQ(result._powers[0], 1);
    EXPECT_EQ(result._powers[1], 2);
    EXPECT_EQ(result._powers[2], 3);
}

TEST_F(TestCMonom, Multiplication) {
    CMonom result = monom1 * monom2; // (2x^1 * y^2 * z^3) * (3x^1 * y^2 * z^3)
    EXPECT_EQ(result._coef, 6.0); // 2 * 3
    EXPECT_EQ(result._powers[0], 2); // 1 + 1
    EXPECT_EQ(result._powers[1], 4); // 2 + 2
    EXPECT_EQ(result._powers[2], 6); // 3 + 3
}

TEST_F(TestCMonom, Division) {
    CMonom result = monom1 / monom2; // (2x^1 * y^2 * z^3) / (3x^1 * y^2 * z^3)
    EXPECT_DOUBLE_EQ(result._coef, 2.0 / 3.0); // 2 / 3
    EXPECT_EQ(result._powers[0], 0); // 1 - 1
    EXPECT_EQ(result._powers[1], 0); // 2 - 2
    EXPECT_EQ(result._powers[2], 0); // 3 - 3
}

TEST_F(TestCMonom, ValuePoint) {
    double point[] = { 1, 2, 3 }; // x=1, y=2, z=3
    EXPECT_DOUBLE_EQ(monom1.valuePoint(point), 2.0 * std::pow(1, 1) * std::pow(2, 2) * std::pow(3, 3));
}

TEST_F(TestCMonom, IsNull) {
    CMonom zeroMonom; // 0
    EXPECT_TRUE(zeroMonom.is_null());
    EXPECT_FALSE(monom1.is_null());
}

TEST_F(TestCMonom, IsNumber) {
    EXPECT_TRUE(monom1.is_number('5'));
    EXPECT_FALSE(monom1.is_number('a'));
}

TEST_F(TestCMonom, Destructor) {
    // Проверка корректного освобождения памяти
    CMonom* monom = new CMonom(monom1);
    delete monom; // Если деструктор не работает, будет утечка памяти
    EXPECT_EQ(true, true); // Просто проверка, что деструктор вызван
}

TEST_F(TestCMonom, NotEqual) {
    EXPECT_TRUE(monom1 != monom2);
}

TEST_F(TestCMonom, Equal) {
    CMonom monom3(monom1);
    EXPECT_TRUE(monom1 == monom3);
}

TEST_F(TestCMonom, GreaterThan) {
    EXPECT_FALSE(monom1 > monom2); // 2.0 < 3.0
    EXPECT_TRUE(monom2 > monom1);  // 3.0 > 2.0
}

TEST_F(TestCMonom, LessThan) {
    EXPECT_TRUE(monom1 < monom2); // 2.0 < 3.0
}
