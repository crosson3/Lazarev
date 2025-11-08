#include <iostream>

void point2() {
    int x, y;
    std::cin >> x >> y;
    double z = sqrt(pow(x, 2) + pow(y, 2));
    double p = x + y + z;

    std::cout << "Гипотенуза = " << z << std::endl;
    std::cout << "Периметр = " << p << std::endl;

}

int calc_expr(int a, int b) {
    std::cout << "исп. функция для 2 чисел: a + 2*b + 3" << std::endl;
    return a + 2 * b + 3;
}

int max_csum(int a, int b, int c) {
    std::cout << "исп. функция для 3 чисел: максимальное из попарных сумм" << std::endl;
    int s1 = a + b;
    int s2 = a + c;
    int s3 = b + c;
    int max_sum = s1;
    if (s2 > max_sum) {
        max_sum = s2;
    }
    if (s3 > max_sum) {
        max_sum = s3;
    }
    return max_sum;
}


int main()
{
    int point;
    std::cout << "введите номер пункта: " << std::endl;
    std::cin >> point;

    if (point == 1) {
        const int NMAX = 3;
        int arr[NMAX];

        std::cout << "введите три целых числа: " << std::endl;
        for (int i = 0; i < NMAX; i++) {
            std::cin >> arr[i];
        }

        
        int count = 0;
        for (int i = 0; i < NMAX; i++) {
            if (arr[i] != 0)
                count++;
        }

        int res = 0;

        if (count == 3) {
            
            res = max_csum(arr[0], arr[1], arr[2]);
        }
        else if (count == 2) {
            
            int nzero[2];
            int index = 0;
            for (int i = 0; i < NMAX; i++) {
                if (arr[i] != 0)
                    nzero[index++] = arr[i];
            }
            res = calc_expr(nzero[0], nzero[1]);
        }
        else if (count == 1) {
          
            int nzero = 0;
            for (int i = 0; i < NMAX; i++) {
                if (arr[i] != 0)
                    nzero = arr[i];
            }
            res = nzero;
        }
        else {
            std::cout << "все числа нули" << std::endl;
            
        }

        std::cout << "вывод: " << res << std::endl;
    }
    else if (point == 2) {
        point2();
    }
    else {
        std::cout << "некорректный выбор." << std::endl;
    }

    
    return 0;
}

