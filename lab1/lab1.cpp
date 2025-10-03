#include <iostream>
#include <cmath>

int main()
{
    unsigned int x; /* длина катета не может быть отрицательной             
                    и значение целочисленное => тип unsigned int */
    unsigned int y;
    double z; // т.к. может быть не целым числом
    double p; // т.к. может быть не целым числом

    

    std::cout << "Первый катет = ";
    std::cin >> x;
    std::cout << "тип - unsighed int от 0 " << "до " << UINT_MAX << std::endl;


    std::cout << "Второй катет = ";

    std::cin >> y;
    std::cout << "тип - unsighed int от 0 " << "до " << UINT_MAX << std::endl;


    z = sqrt(pow(x, 2) + pow(y, 2));
    p = x + y + z;
    std::cout << "Гипотенуза = " << z << " тип - double от " << DBL_MIN << "до " << DBL_MAX << std::endl;
    std::cout << "Периметр = " << p << " тип - double от " << DBL_MIN << "до " << DBL_MAX << std::endl;







}