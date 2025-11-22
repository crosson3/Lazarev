#include <iostream>
#include <cstdlib> 

int* find_zero(int** matrix, int rows, int cols, int& count) {
    int* res = (int*)malloc(cols * sizeof(int));
    count = 0;    
    for (int j = 0; j < cols; j++) {
        bool zero = false;
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] == 0) {
                zero = true;
                break;
            }
        }
        if (zero == true) {
            res[count] = j;
            count++;
        }
    }    
    if (count == 0) {
        free(res);
        return 0;
    }   
    return (int*)realloc(res, count * sizeof(int));
}

void display_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

int main() {
    int rows = 2;
    int cols = 2;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    
    while (true) {
        std::cout << "введите матрицу 2x2" << std::endl;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                std::cin >> matrix[i][j];
            }
        }

        if (matrix[0][0] < 0 || matrix[0][1] < 0) {
            std::cout << "A и B не могут быть отрицательными" << std::endl;
        }
        else {
            break;
        }
    }

    int A = matrix[0][0]; 
    int B = matrix[0][1]; 
    int C = matrix[1][0];
    int D = matrix[1][1];    
    int new_rows = 2 + A;
    int new_cols = 2 + B;
    
    matrix = (int**)realloc(matrix, new_rows * sizeof(int*));

    for (int i = 0; i < 2; i++) {
        matrix[i] = (int*)realloc(matrix[i], new_cols * sizeof(int));
    }

    for (int i = 2; i < new_rows; i++) {
        matrix[i] = (int*)malloc(new_cols * sizeof(int));
    }

    for (int i = 0; i < new_rows; i++) {
        for (int j = 0; j < new_cols; j++) {
            if (i < 2 && j < 2) continue;
            matrix[i][j] = (i - 1) * C + (j - 1) * D;
        }
    }

    std::cout << "результат: " << std::endl;
    display_matrix(matrix, new_rows, new_cols);
    int zero_count = 0;
    int* indx_zero = find_zero(matrix, new_rows, new_cols, zero_count);

    if (indx_zero != 0) {
        std::cout << "столбцов с 0: " << zero_count << std::endl;

        for (int k = zero_count - 1; k >= 0; k--) {
            int del_cols = indx_zero[k];

            for (int i = 0; i < new_rows; i++) {
                for (int j = del_cols; j < new_cols - 1; j++) {
                    matrix[i][j] = matrix[i][j + 1];
                }
                matrix[i] = (int*)realloc(matrix[i], (new_cols - 1) * sizeof(int));
            }
            new_cols--;
        }
        free(indx_zero);
    }
    else {
        std::cout << "нулей нет" << std::endl;
    }

    std::cout << "итоговая матрица:" << std::endl;
    display_matrix(matrix, new_rows, new_cols);
    for (int i = 0; i < new_rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    float* pA = new float;
    float* pB = new float;
    std::cout << "введите A: ";
    std::cin >> *pA;
    std::cout << "введите B: ";
    std::cin >> *pB;
    *pA = (*pA) * 3.0f;
    float temp = *pA;
    *pA = *pB;
    *pB = temp;
    std::cout << "результат: A = " << *pA << ", B = " << *pB << std::endl;
    delete pA;
    delete pB;

    return 0;
}