#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>


//Заполнение массива числами из заданного мн-ва чисел,в случайно порядке
void RandomFilling( int* array,int* alphabet, int array_size, int alphabet_size = 10) {

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
void RandomDigits(int* array, int array_size = 10, int quantity_of_digits = 1) {
    int quantity = (int)(pow(10, (quantity_of_digits)));
    array[0] = rand() % quantity;

    for (int i = 1; i < array_size; i++) {
        array[i] = rand() % quantity;
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
void ComparingArrays(int* array_1,int* array_2,short int &correctly, short int &closely,int  array_size = 4) {
    for (int i = 0; i <= array_size - 1; i++) {
        if (array_1[i] == array_2[i])
            correctly += 1;

        else{
            for (int j = 0; j <= array_size - 1; j++) {
                if (array_1[i] == array_2[j]){
                    closely += 1;
                }

            }
        }
    }
}

//Ввод числа в массив,с указанием желаемого количества символов в числе
//Заполнение по одному знаку,в один элемент массива
//Если количество символов в числе не соответсвует заданному,возвращение 0
int InputDigits(int* array,int quantity_of_digits = 4) {

    std::string str;
    std::cin >> str;
    
    if(str.length() == quantity_of_digits){
        int number;

        try {
            number = std::stoi(str);
        }
        catch (std::invalid_argument) {
            return 0;
        }

        for (int i = quantity_of_digits-1; i>=0; i--) {
            array[i] = number % 10;
            number = number / 10;
        }
        return 1;
    }

    else
        return 0;
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

    short int play = 1;

    srand(time(NULL));
    RandomFilling(decisions,alphabet,lenght, lenght_alphabet);

    while (play) {
        short int correct = 0;
        short int attempts = 10;

        std::cout << "You have to guess the number of 4 non - repeating digits\n" << std::endl;

        while (correct != 4 && attempts > 0) {
            short int close = 0;
            correct = 0;

            std::cout << "Enter 4 digits: ";
            if (InputDigits(anwsers)) {
                ComparingArrays(decisions, anwsers, correct, close);

                std::cout << "\nCorrectly = " << correct << "; ";
                std::cout << "Closely = " << close << "." << std::endl;
                attempts--;
                std::cout << "You have " << attempts << " attempts left\n" << std::endl;

            }


            else {
                std::cout << "\nWrong number!!!\n" << std::endl;
                continue;
            }
        }

        if (correct == 4) {
            OutputArray(decisions, lenght);
            std::cout << "Congratulations you have won !!!" << std::endl;
        }
        else
            std::cout << "All attempts ended :(" << std::endl;

        std::cout << "\nIf you want to exit the game, press 0, if you want to play again, press any other number:";
        std::cin >> play;
        std::cout << std::endl;
    }
    
}

