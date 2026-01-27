#include <iostream>
#include <vector>
#include <array>
#include <cmath>


void showVector(const std::vector<int>& vec) {
    std::cout << "[";
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << (i == vec.size() - 1 ? "" : " ");
    }
    std::cout << "]" << std::endl;
}

void pushFront(std::vector<int>& vec, int value) {
    vec.insert(vec.begin(), value);
}

void pushBack(std::vector<int>& vec, int value) {
    if (vec.size() == vec.capacity()) {
        int newCap = (vec.capacity() == 0) ? 1 : vec.capacity() * 2;
        vec.reserve(newCap);
    }
    vec.push_back(value);
}

void clearVector(std::vector<int>& vec) {
    vec.clear();
}

void findInd(const std::vector<int>& vec, int target) {
    std::cout << "[";
    bool first = true;
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == target) {
            if (!first) std::cout << ",";
            std::cout << i;
            first = false;
        }
    }
    std::cout << "]" << std::endl;
}

void addZero(std::vector<int>& vec) {
    if (vec.empty()) return;

    int minAbs = -1;
    for (int x : vec) {
        if (x != 0) {
            if (minAbs == -1 || std::abs(x) < minAbs) {
                minAbs = std::abs(x);
            }
        }
    }

    if (minAbs != -1) {
        for (int i = 0; i < minAbs; ++i) {
            vec.push_back(0);
        }
    }
}
/*создается полная копия массива в памяти
  оригинальный массив остается нетронутым
  самый медленный способ, так как компьютер тратит время и память на дублирование всех данных
*/
void sortByVal(std::array<int, 10> arr) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 9; j++)
            if (arr[j] > arr[j + 1]) std::swap(arr[j], arr[j + 1]);
}

/*функция получает прямой доступ к оригиналу под другим именем
  все изменения внутри функции сразу отражаются на оригинальном массиве
  очень быстро, так как данные не копируются
*/
void sortByRef(std::array<int, 10>& arr) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 9; j++)
            if (arr[j] > arr[j + 1]) std::swap(arr[j], arr[j + 1]);
}

/*функция получает адрес ячейки памяти, где лежит начало массива
  указатель может быть пустым
*/
void sortByPoint(std::array<int, 10>* arr) {
    if (arr) {
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 9; j++)
                if ((*arr)[j] > (*arr)[j + 1]) std::swap((*arr)[j], (*arr)[j + 1]);
    }
}

void showArr(const std::array<int, 10>& arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << (i == arr.size() - 1 ? "" : " ");
    }
    std::cout << "]" << std::endl;
}

int main() {
    std::vector<int> vec = { 5, -2, 10, 0, 3 };
    int choice;

    while (true) {
        std::cout << "\nменю:\n0. выход\n1. просмотр массива\n2. добавить в начало\n"
            << "3. добавить в конец\n4. очистка массива\n5. поиск элемента\n"
            << "6. задание варианта 4\n7. пункт 2 array\nвыбор: ";
        std::cin >> choice;

        if (choice == 0) break;

        switch (choice) {
        case 1: showVector(vec); break;
        case 2: {
            int val; std::cout << "введите число: "; std::cin >> val;
            std::cout << "до: "; showVector(vec);
            pushFront(vec, val);
            std::cout << "после: "; showVector(vec);
            break;
        }
        case 3: {
            int val; std::cout << "введите число: "; std::cin >> val;
            std::cout << "до: "; showVector(vec);
            pushBack(vec, val);
            std::cout << "после: "; showVector(vec);
            break;
        }
        case 4:
            std::cout << "до: "; showVector(vec);
            clearVector(vec);
            std::cout << "после: "; showVector(vec);
            break;
        case 5: {
            int val; std::cout << "элемент для поиска: "; std::cin >> val;
            findInd(vec, val);
            break;
        }
        case 6:
            std::cout << "до: "; showVector(vec);
            addZero(vec);
            std::cout << "после: "; showVector(vec);
            break;
        case 7: {
            std::array<int, 10> arr = { 3, -1, 5, 0, -2, 9, 7, -3, 4, 1 };
            std::array<int, 10> by_value = arr, by_referance = arr, by_pointer = arr;

            sortByVal(by_value);
            std::cout << "после сортировки по значению : "; showArr(arr);

            sortByRef(by_referance);
            std::cout << "после сортировки по ссылке: "; showArr(by_referance);

            sortByPoint(&by_pointer);
            std::cout << "после сортировки по указателю: "; showArr(by_pointer);
            break;
        }
        }
    }
    /*пункт 3
     
      для первого пункта vector, потому что он умеет менять размер, 
      чтобы добавлять числа в начало и конец или очищать список. для второго пункта array, 
      так как размер всегда равен 10 и меняться не должен. если количество элементов 
      заранее неизвестно, используем vector, если оно всегда одно и то же array. 
      работают они одинаково, когда нужно достать число по индексу 
    */
    return 0;
}
