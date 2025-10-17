
#include <iostream>

int main()
{
    int n;
    short number;
    int sum_even = 0;
    short max_even = 0;
    short min_number = 9;
    int num_seq = 0;
    bool check = false;
    std::cout << "Введите число элементов последовательности - ";
    std::cin >> n;
    std::cout << "Введите " << n << " чисел последовательности - ";
    for (int i = 1; i <= n; ++i) {

        std::cin >> number;
        if (number % 2 == 0) {
            check = true;
            sum_even += number;
            if (number > max_even) {
                num_seq = i;
                max_even = number;
            }
            continue;
        }
    }
    if (check == false) {
        std::cout << "Нет чисел, удовлетворяющих условию" << std::endl;

    }
    else {
        std::cout << "Сумма чётных " << sum_even << std::endl;
        std::cout << "Максимальное чётных " << max_even << std::endl;
        std::cout << "Номер максимального в последовательности " << num_seq << std::endl;
    }

    int x;
    std::cout << "Введите |X| < 1000 " << std::endl;
    std::cin >> x;
    x = abs(x);
    int min_x = 9;
    if (x > 1000) {
        std::cout << "X больше 1000" << std::endl;
    }
    do {
        min_x = std::min(min_x, x % 10);
        x /= 10;
    } while (x > 0);
    std::cout << "Минимальная цифра " << min_x << std::endl;
}
