#include <iostream>
#include <cmath>
#include <algorithm>

int calc(int n) {
    int absN = std::abs(n);
    if (absN == 0) return 1;

    int maxNum = -1;
    int temp = absN;
    
    while (temp > 0) {
        int currentNum = temp % 10;
        if (currentNum > maxNum) maxNum = currentNum;
        temp /= 10;
    }
    
    int countMN = 0;
    temp = absN;
    while (temp > 0) {
        if (temp % 10 == maxNum) countMN++;
        temp /= 10;
    }
    return countMN;
}

int calc(int a, int b, int c) {
    
    if ((a != b) && (b != c) && (a != c)) {
        int arr[3] = { a, b, c };

        if (std::abs(arr[0]) > std::abs(arr[1])) {
            std::swap(arr[0], arr[1]);
        }
        if (std::abs(arr[1]) > std::abs(arr[2])) {
            std::swap(arr[1], arr[2]);
        }
        if (std::abs(arr[0]) > std::abs(arr[1])) {
            std::swap(arr[0], arr[1]);
        }
        return arr[1];
    }
    else {
        return std::min({a, b, c});
    }
}

void calc_radius(int radius) {

    const double pi = 13.1415;

    double oneNumber = (4.0/3.0) * pi * std::pow(radius, 3);
    
    double s = 4 * pi * std::pow(radius, 2);

    std::cout << "объем сферы: " << oneNumber << std::endl;
    std::cout << "площадь поверхности: " << s << std::endl;
}

int main() {

    int point;
    std::cout << "выберите пункт: ";
    std::cin >> point;

    if (point == 1) {
        int arr[3];
        int count = 0;

        std::cout << "введите 3 числа:" << std::endl;
        for (int i = 0; i < 3; i++) {
            std::cin >> arr[i];
            if (arr[i] != 0) {
                count++;
            }
        }

        if (count == 1) {
            for (int oneNumber : arr) {
                if (oneNumber != 0) {
                    std::cout << "результат: " << calc(oneNumber) << std::endl;
                    break;
                }
            }
        }
        else if (count == 3) {
            std::cout << "результат: " << calc(arr[0], arr[1], arr[2]) << std::endl;
        }
        else {
            std::cout << "два ненулевых" << std::endl;
        }

    }
    else if (point == 2) {
        int r;
        std::cout << "введите радиус: " << std::endl;
        std::cin >> r;
        calc_radius(r);
    }
    else {
        std::cout << "неверный выбор пункта" << std::endl;
    }

    return 0;
}
