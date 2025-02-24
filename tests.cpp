#include "longnumber.hpp"
#include <iostream>
using namespace LongMath;
#define TEST_CASE(name, expr) std::cout << (expr ? "[ OK ] " : "[FAIL] ") << name << std::endl;

int main()
{
    LongNumber num1;
    TEST_CASE("Конструктор по умолчанию", num1.toString() == "0");

    LongNumber num2("1101");
    TEST_CASE("Конструктор из строки", num2.toString() == "1101");

    LongNumber num3(5);
    TEST_CASE("Конструктор из числа", num3.toString() == "101");

    LongNumber num4(5, 4);
    TEST_CASE("Конструктор с точностью", num4.toString(4) == "101.0000");

    LongNumber num5 = num3 + num2;
    TEST_CASE("Оператор сложения", num5.toString() == "10010");

    LongNumber num6 = num2 - num3;
    TEST_CASE("Оператор вычитания", num6.toString() == "1000");

    LongNumber num7 = num3 * num2;
    TEST_CASE("Оператор умножения", num7.toString() == "1000001");

    LongNumber num8 = num2 / num3;
    TEST_CASE("Оператор деления", num8.toString() == "10");

    TEST_CASE("Оператор ==", (num3 == LongNumber(5)));

    TEST_CASE("Оператор !=", (num3 != num2));

    TEST_CASE("Оператор <", (num3 < num2));

    TEST_CASE("Оператор >", (num2 > num3));

    return 0;
}
