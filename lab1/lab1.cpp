#include <iostream>
#include <cmath>

int main()
{
    unsigned int x; // unsigned int т.к длина катета не может быть отрицательной и значение целочисленное
    unsigned int y;
    double z; // т.к может быть не целым числом
    double p; // т.к может быть не целым числом
    double size;
    double minsize;
    double maxsize;

    size = pow(2, 32) - 1;
    minsize = -((2 - pow(2, -52)) * pow(2, 1023));
    maxsize = (2 - pow(2, -52)) * pow(2, 1023);
    std::cout << "Первый катет = ";
    std::cin >> x;

    std::cout << "Второй катет = ";

    std::cin >> y;


    z = sqrt(pow(x, 2) + pow(y, 2));
    p = x + y + z;
    std::cout << "Гипотенуза = " << z << std::endl;
    std::cout << "Периметр = " << p << std::endl;
    std::cout << "Тип - unsigned int, размер - 32бит, от 0 до " << size << std::endl;
    std::cout << "Тип - double, размер - 64бит, от " << minsize << " до " << maxsize << std::endl;







}