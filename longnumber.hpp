#ifndef LONGNUMBER_HPP
#define LONGNUMBER_HPP
#include <string>
#include <iostream>
#include <vector>

namespace LongMath{
    class LongNumber{
    private:
        std::vector<bool> bits; //храним число в двоичной системе
        unsigned precision; //точность вычислений
	unsigned point; //число битов после запятой
        bool sign; //знак числа
	void removezeros(); //убираем ведущие нули
        bool iszero() const; //проверка, является число нулем или нет
        int magnitude() const; //определение количества значащих битов

    public:
        LongNumber();
	explicit LongNumber(std::string binary); //конструктор из строки
        explicit LongNumber(int number); //конструктор из целого числа
        LongNumber(int number, int precision); //конструктор с заданной точностью
        std::string toString() const; //возврат строкового представления числа
        std::string toString(int) const; //представление с заданной точностью

        friend std::ostream &operator<<(std::ostream &, const LongNumber &);
        LongNumber operator-() const;
        friend LongNumber operator+(const LongNumber &, const LongNumber &);
        friend LongNumber operator-(const LongNumber &, const LongNumber &);
        friend LongNumber operator*(const LongNumber &, const LongNumber &);
        friend LongNumber operator/(const LongNumber &, const LongNumber &);
        friend bool operator==(const LongNumber &, const LongNumber &);
        friend bool operator!=(const LongNumber &, const LongNumber &);
        friend bool operator<(const LongNumber &, const LongNumber &);
        friend bool operator>(const LongNumber &, const LongNumber &);

        friend LongNumber operator""_longnum(long double number);
    };
}

#endif //LONGNUMBER_HPP