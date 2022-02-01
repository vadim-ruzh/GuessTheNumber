#include <iostream>
#include <stdlib.h>
#include <time.h>

//Создание случайного массива
void GenerateKey(int key[], const int size) {

    srand(time(NULL));

    int mass[10] = { 0,1,2,3,4,5,6,7,8,9 };

    for (int i = 9; i >= 1; i--) {
        int j = rand() % (i + 1);
        int tmp = mass[j];
        mass[j] = mass[i];
        mass[i] = tmp;
    }
    
    for (int i = 0; i <= size - 1; i++) {
         key[i] = mass[i];
    }
}
//Проверка ответа
int Guess(int* key,int* anwser) {
    int correctly = 0;
    int closely = 0;
    
    for (int i = 0; i <= 3; i++) {
        if (key[i] == anwser[i])
            correctly += 1;
        else{
            for (int j = 0; j <= 3; j++) {
                if (key[i] == anwser[j])
                    closely += 1;
            }
        }
    }
    std::cout << "correctly = " << correctly << "; ";
    std::cout << "closely = " << closely << "." << std::endl;

    return correctly;
}
//Ввод ответа
void InputDigits(int* array) {
    int number;

    std::cout << "Enter 4 digits: ";
    std::cin >> number;

    if (number < 999 || number > 10000)
        std::cout << "Wrong number!!! " << std::endl;
    else {
        for (int i = 3; i>=0; i--) {
            array[i] = number % 10;
            number = number / 10;
        }
    }


}
//Вывод массива на экран
void OutputArray(int* array, const int size) {
    std::cout << "Array: ";
    for (int i = 0; i < size; i++)
        std::cout << array[i] << ' ';
}

int main()
{   
    const int lenght = 4;
    int key[lenght];
    int anwser[lenght];
    int correctly = 0;

    GenerateKey(key, lenght);

    while (correctly != 4) {
        InputDigits(anwser);
        Guess(key, anwser);
    }

    std::cout << "UrA!";
}

