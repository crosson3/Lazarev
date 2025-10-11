
#include <iostream>
#include <bitset>

int main()
{
	
	int p;
	std::cout << "Выберите подпункт(1,2)" << std::endl;
	std::cin >> p;
	bool check = ((p == 1) ? true : false); // тернарный оператор для установления флага
	if (check) {	
		unsigned short i;
		std::cout << "Введите i" << std::endl;
		std::cin >> i;
		if (i < 0 || i > 7) { // проверка на правильность ввода i
			std::cout << "i должен быть в пределе 0...7" << std::endl;	
		}
		else {
			short z;
			unsigned char A;			
			std::cout << "Введите А" << std::endl;
			std::cin >> z;
			A = static_cast<unsigned char>(z);			
			bool val = (A >> i) & 1; // получаем i-ое значение бита
			if (val) { // если i-ый бит == 1
				int x, y;
				std::cout << "i-ый бит А == 1, введите x, y " << std::endl;
				std::cin >> x >> y;
				std::cout << "Максимальное значение = " << (x > y ? x : y) << std::endl; // вывод максимального значения

				A = A & ~(1 << i); // i-ый бит А устанавливаем в 0
				std::cout << "Устанавливаем i-ый бит А в 0 - " << std::bitset<8>(A) << std::endl;
			}
			else {
				A = ~A; // инвертируем все биты
				std::cout << "i-ый бит != 1, инвертируем А " << std::bitset<8>(A) << std::endl;
			}
		}
	}
	else {
		int n;//unsigned int не рекомендуется т.к. при вводе отрицательных из-за переполнения они интерпритируются как большие положительные 
		std::cout << "Введите номер месяца" << std::endl;
		std::cin >> n;

		switch (n) {
		case 1:  std::cout << "Январь"; break;
		case 2:  std::cout << "Февраль"; break;
		case 3:  std::cout << "Март"; break;
		case 4:  std::cout << "Апрель"; break;
		case 5:  std::cout << "Май"; break;
		case 6:  std::cout << "Июнь"; break;
		case 7:  std::cout << "Июль"; break;
		case 8:  std::cout << "Август"; break;
		case 9:  std::cout << "Сентябрь"; break;
		case 10: std::cout << "Октябрь"; break;
		case 11: std::cout << "Ноябрь"; break;
		case 12: std::cout << "Декабрь"; break;
		default: std::cout << "Ошибка номера месяца";
		}
	}	
}


