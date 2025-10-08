#include <iostream>
#include <cmath>
#include <limits>

int main()
{
    unsigned int x; /* длина катета не может быть отрицательной             
                    и значение целочисленное => тип unsigned int */
    unsigned int y;
    double z; // т.к. может быть не целым числом
    double p; // т.к. может быть не целым числом
    unsigned int k = sizeof(unsigned int) * 8;
    unsigned int k2 = sizeof(double) * 8;

    std::cout << "Первый катет = ";
    std::cin >> x;
    std::cout << "unsighed int, занимает " << k << " бит от 0 " << "до " << std::numeric_limits<unsigned int>::max() << std::endl;


    std::cout << "Второй катет = ";

    std::cin >> y;
    std::cout << "unsighed int, занимает " << k << " бит от 0 " << "до " << std::numeric_limits<unsigned int>::max() << std::endl;


    z = sqrt(pow(x, 2) + pow(y, 2));
    p = x + y + z;
    std::cout << "Гипотенуза = " << z << " double, занимает " << k2 << " бит от" << std::numeric_limits<double>::min() << "до " << std::numeric_limits<double>::max() << std::endl;
    std::cout << "Периметр = " << p << " double, занимает " << k2 << " бит от" << std::numeric_limits<double>::min() << "до " << std::numeric_limits<double>::max() << std::endl;







}