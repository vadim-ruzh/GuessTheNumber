#include <iostream>
#include <stdlib.h>
#include <time.h>


//Заполнение массива числами из заданного мн-ва чисел,в случайно порядке
void RandomFilling( int* array,int* alphabet,int alphabet_size, int array_size = 10) {

    for (int i = alphabet_size - 1; i >= 1; i--) {
        int j = rand() % (i + 1);
        int tmp = alphabet[j];
        alphabet[j] = alphabet[i];
        alphabet[i] = tmp;
    }
    
    for (int i = 0; i <= array_size - 1; i++) {
         array[i] = alphabet[i];
    }
}

//Заполнение массива случайными числами
void RandomDigits(int* array, int array_size = 10) {
    array[0] = rand() % 10;
    for (int i = 1; i < array_size; i++) {
        array[i] = rand() % 10;
        for (int j = 0; j < i; j++) {
            if (array[j] == array[i]) {
                i--;
                break;
            }
        }

    }
}

//Сравнение массивов одинаковой длины
//Проверка на однозначное соответствие массива array_2 массиву array_1
//Подсчет количества сооствествующих элементов и элементов для которых нашлось соответсвие,но он имеет неправильную позицию
void ComparingArrays(int* array_1,int* array_2,int &correctly, int &closely,int  array_size = 4) {
    for (int i = 0; i <= array_size - 1; i++) {
        if (array_1[i] == array_2[i])
            correctly += 1;

        else{
            for (int j = 0; j <= array_size - 1; j++) {
                if (array_1[i] == array_2[j])
                    closely += 1;
            }
        }
    }
}

//Ввод числа в массив,с указанием желаемого количества символов в числе
//Заполнение по одному знаку,в один элемент массива
//Если количество символов в числе не соответсвует заданному,возвращение 0
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
void OutputArray(int* array,int array_size) {
    std::cout << "Array: ";
    for (int i = 0; i < array_size; i++)
        std::cout << array[i] << ' ';

    std::cout << std::endl;
}

int main()
{   
    const int lenght = 4;
    int decisions[lenght];
    int anwsers[lenght];

    const int lenght_alphabet = 10;
    int alphabet[lenght_alphabet] = { 0,1,2,3,4,5,6,7,8,9 };

    int correct = 0;


    srand(time(NULL));
    RandomFilling(decisions,alphabet,lenght_alphabet,lenght);

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

