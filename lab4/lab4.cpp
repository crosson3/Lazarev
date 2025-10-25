#include <iostream>

int main()
{
	const int msize = 4;
	int arr[msize];
	std::cout << "введите 4 элемента массива" << std::endl;
	for (int i = 0; i < msize; ++i) {
		int num;
		std::cin >> num;
		arr[i] = num;
	}
	char minfirst = 9;
	char minsecond = 9;
	int num1 = abs(arr[0]);
	int num2 = abs(arr[3]);
	while (num1 > 0) {		//минимальное первое
		if (num1 % 10 < minfirst) {
			minfirst = num1 % 10;
		}
		num1 /= 10;
	}
	while (num2 > 0) {		//минимальное последнее
		if (num2 % 10 < minsecond) {
			minsecond = num2 % 10;
		}
		num2 /= 10;
	}
	if (minfirst == minsecond) { //массив в порядке возрастания
		for (int i = 0; i < msize; ++i) {
			for (int j = i + 1; j < msize; ++j) {
				if (arr[i] > arr[j]) {
					std::swap(arr[i], arr[j]);
				}
			}
		}
		std::cout << "Упорядоченный массив по возрастанию" << std::endl;
		for (int i = 0; i < msize; ++i) {
			
			std::cout << arr[i] << ' ';
		}
	}
	else {
		std::cout << "Условие не выполнено" << std::endl;

	}
	std::cout << std::endl;
	const int l = 3;
	const int w = 4;
	int nl = 0;
	int minsum = INT_MAX;
	int matrix[l][w];
	std::cout << "введите 12 элементов матрицы" << std::endl;
	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < w; ++j) {
			std::cin >> matrix[i][j];
		}
	}
	for (int i = 0; i < l; ++i) { //поиск строки близкой суммой к 0
		int sum = 0;
		for (int j = 0; j < w; ++j) {
			sum += matrix[i][j];
		}
		if (abs(sum) < minsum) {
			minsum = abs(sum);
			nl = i;
		}
	}
	std::cout << "Номер строки подходящей по условию " << nl + 1 << std::endl;
		
	
	for (int j = 0; j < w; ++j) { //замена эл-ов нужной строки на 0
		matrix[nl][j] = 0;
	}
	std::cout << "Матрица после замены " << nl << " строки на 0" << std::endl;
	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < w; ++j) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}