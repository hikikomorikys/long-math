#include <iostream>
#include"longnumber.hpp"
#include "pi.hpp"

int main()
{
    int n;
    std::cout << "Задайте точность: ";
    std::cin >> n;
    auto _pi = PI::pi(n);
    std::cout << "pi = " << _pi.toString(n) << std::endl;
    return 0;
}