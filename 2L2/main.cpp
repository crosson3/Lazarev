#include <iostream>
#include "watch.h"
#include <ctime>

int main() {
    srand(static_cast<unsigned>(time(0)));

    std::vector<std::string> tasks1 = { "а", "б", "в" };
    std::vector<std::string> tasks2 = { "б", "р", "г" };

    watch w1(27, 12, 2005, 12, 0, tasks1);
    watch w2(5, 6, 2003, 10, 0, tasks2);

    std::cout << " часы 1 " << std::endl;
    w1.print_info();
    std::cout << "\n часы 2 " << std::endl;
    w2.print_info();

    std::cout << "\n проверка оператора + " << std::endl;
    watch w3 = w1 + w2;
    w3.print_info();

    std::cout << "\n проверка оператора / " << std::endl;
    watch w4 = w1 / w2;
    w4.print_info();

    std::cout << "\n завершение работы " << std::endl;
    return 0;
}