#include <iostream>
#include <stdlib.h>
#include <time.h>


//Заполнение массива случайными неповторяющимися числами
void GenerateKey( int array[], const int size) {

    int mass[10] = { 0,1,2,3,4,5,6,7,8,9 };

    for (int i = 9; i >= 1; i--) {
        int j = rand() % (i + 1);
        int tmp = mass[j];
        mass[j] = mass[i];
        mass[i] = tmp;
    }
    
    for (int i = 0; i <= size - 1; i++) {
         array[i] = mass[i];
    }
}

//Сравнение массивов одинаковой длины
//Проверка на однозначное соответствие массива array_2 массиву array_1
//Подсчет количества сооствествующих элементов и элементов для которых нашлось соответсвие,но он имеет неправильную позицию
void ComparingArrays(int* array_1,int* array_2,int &correctly, int &closely, int size = 4) {
    for (int i = 0; i <= size-1; i++) {
        if (array_1[i] == array_2[i])
            correctly += 1;

        else{
            for (int j = 0; j <= size - 1; j++) {
                if (array_1[i] == array_2[j])
                    closely += 1;
            }
        }
    }
}

//Ввод числа в массив,с указанием желаемого количества символов в числе
//По одному знаку,в каждый элемент массива
int InputDigits(int* array,int quantity_of_digits = 4) {
    int quantity = pow(10, (quantity_of_digits - 1));

    int number;
    std::cin >> number;

    if (number <= (quantity-1) || number >= quantity*10)
        return 0;

    else {
        for (int i = 3; i>=0; i--) {
            array[i] = number % 10;
            number = number / 10;
        }
    }

    return 1;
}

//Вывод массива в консоль
void OutputArray(int* array, const int size) {
    std::cout << "Array: ";
    for (int i = 0; i < size; i++)
        std::cout << array[i] << ' ';

    std::cout << std::endl;
}

int main()
{   
    const int lenght = 4;
    int decisions[lenght];
    int anwsers[lenght];
    int correct = 0;

    srand(time(NULL));
    GenerateKey(decisions, lenght);

    while (correct != 4) {
        int close = 0; 
        correct = 0;

        std::cout << "Enter 4 digits: ";
        if (InputDigits(anwsers)) {
            ComparingArrays(decisions, anwsers,correct,close);

            std::cout << "correctly = " << correct << "; ";
            std::cout << "closely = " << close << "." << std::endl;
        }
            

        else{
            std::cout << "Wrong number!!!" << std::endl;
                continue;
        }
    }

    OutputArray(decisions, lenght);

    
    std::cout << "UrA!";
}

