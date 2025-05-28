/*#include <gtest.h>
#include "CPolinom.h"
#include "CMonom.h" // Убедитесь, что CMonom определен и доступен

class TestCPolinom : public ::testing::Test {
protected:
    CPolinom polinom1 = CPolinom("3x^2 + 2x + 1", 3);
    CPolinom polinom2 = CPolinom("x^2 + 4", 3);
    CPolinom emptyPolinom = CPolinom(); // Пустой полином
};

TEST_F(TestCPolinom, ConstructorFromString) {
    CPolinom polinom("2x^2 + 3x + 4", 3);
    EXPECT_EQ(polinom._monoms.size(), 3); // Проверяем, что 3 монома
}

TEST_F(TestCPolinom, DefaultConstructor) {
    EXPECT_EQ(emptyPolinom._monoms.size(), 0); // Проверяем, что пустой полином имеет 0 мономов
}

TEST_F(TestCPolinom, CheckAssign) {
    CPolinom polinom3;
    polinom3 = polinom1;
    EXPECT_EQ(polinom3._monoms.size(), polinom1._monoms.size());
    EXPECT_TRUE(polinom3 == polinom1);
}

TEST_F(TestCPolinom, CheckAddPolinom) {
    CPolinom result = polinom1 + polinom2;
    EXPECT_EQ(result._monoms.size(), 4); // Проверяем, что размер результирующего полинома
}

TEST_F(TestCPolinom, CheckSubtractPolinom) {
    CPolinom result = polinom1 - polinom2;
    EXPECT_EQ(result._monoms.size(), 3); // Проверяем, что размер результирующего полинома
}

TEST_F(TestCPolinom, CheckMultiplyPolinom) {
    CPolinom result = polinom1 * polinom2;
    EXPECT_EQ(result._monoms.size(), 5); // Проверяем, что размер результирующего полинома
}

TEST_F(TestCPolinom, CheckValuePoint) {
    double points[] = { 2 }; // Пример точки
    double result = polinom1.valuePoint(points);
    EXPECT_DOUBLE_EQ(result, 3 * pow(2, 2) + 2 * 2 + 1); // Проверяем значение в точке
}

TEST_F(TestCPolinom, CheckEquality) {
    CPolinom polinom3 = CPolinom("3x^2 + 2x + 1", 3);
    EXPECT_TRUE(polinom1 == polinom3);
}

TEST_F(TestCPolinom, CheckInequality) {
    EXPECT_FALSE(polinom1 == polinom2);
}

TEST_F(TestCPolinom, CheckNegation) {
    CPolinom negated = -polinom1;
    EXPECT_EQ(negated._monoms.size(), polinom1._monoms.size());
    // Дополнительные проверки для мономов
}

TEST_F(TestCPolinom, CheckToString) {
    std::ostringstream out;
    out << polinom1;
    EXPECT_STREQ(out.str().c_str(), "3x^2 + 2x + 1"); // Проверяем строковое представление
}

// Проверка на выброс исключений
TEST_F(TestCPolinom, CheckAddPolinomException) {
    CPolinom polinom3("x^2", 2);
    EXPECT_THROW(polinom1 + polinom3, std::logic_error);
}

TEST_F(TestCPolinom, CheckSubtractPolinomException) {
    CPolinom polinom3("x^2", 2);
    EXPECT_THROW(polinom1 - polinom3, std::logic_error);
}

TEST_F(TestCPolinom, CheckMultiplyPolinomException) {
    CPolinom polinom3("x^2", 2);
    EXPECT_THROW(polinom1 * polinom3, std::logic_error);
}

TEST_F(TestCPolinom, CheckDividePolinomException) {
    CPolinom polinom3("x^2", 2);
    EXPECT_THROW(polinom1 / polinom3, std::logic_error);
}

TEST_F(TestCPolinom, CheckEmptyPolinomAddition) {
    CPolinom result = emptyPolinom + polinom1;
    EXPECT_TRUE(result == polinom1); // Сложение с пустым полиномом
}

TEST_F(TestCPolinom, CheckEmptyPolinomSubtraction) {
    CPolinom result = polinom1 - emptyPolinom;
    EXPECT_TRUE(result == polinom1); // Вычитание пустого полинома
}

TEST_F(TestCPolinom, CheckEmptyPolinomMultiplication) {
    CPolinom result = emptyPolinom * polinom1;
    EXPECT_EQ(result._monoms.size(), 0); // Умножение на пустой полином
}

TEST_F(TestCPolinom, CheckEmptyPolinomDivision) {
    EXPECT_THROW(emptyPolinom / polinom1, std::logic_error); // Деление на пустой полином
}
*/