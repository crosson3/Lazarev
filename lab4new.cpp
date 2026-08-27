#include <iostream>
#include <algorithm>

int main()
{

    const int msize = 7;
    int arr[msize];
    std::cout << "введите 7 элементов массива:" << std::endl;
    for (int i = 0; i < msize; ++i) {
        std::cin >> arr[i];
    }

    bool div = true;
    for (int i = 0; i < msize; ++i) {
        if (arr[i] % 5 != 0) {
            div = false;
            break;
        }
    }

    if (div) {

        for (int i = 0; i < msize - 1; ++i) {
            for (int j = i + 1; j < msize; ++j) {
                if (arr[i] > arr[j]) {
                    std::swap(arr[i], arr[j]);
                }
            }
        }
        std::cout << "упорядоченный массив по возрастанию:" << std::endl;
        for (int i = 0; i < msize; ++i) {
            std::cout << arr[i] << ' ';
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "условие не выполнено " << std::endl;
    }

    const int rows = 3;
    const int cols = 4;
    int matrix[rows][cols];
    std::cout << "введите 12 элементов матрицы: " << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    int maxNegative = 0;
    int numCol = -1;
    for (int j = 0; j < cols; ++j) {
        int countNegative = 0;
        for (int i = 0; i < rows; ++i) {
            if (matrix[i][j] < 0) {
                countNegative++;
            }
        }
        if (countNegative > maxNegative) {
            maxNegative = countNegative;
            numCol = j;
        }
    }
    if (numCol != -1) {
         
        for (int i = 0; i < rows; ++i) {
            matrix[i][numCol] = -1;
        }
        std::cout << "матрица после замены столбца " << numCol + 1 << " на -1:" << std::endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    else {
        std::cout << "отрицательных нет" << std::endl;
    }

    return 0;
}
