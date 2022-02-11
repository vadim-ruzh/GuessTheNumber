#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * \brief - заполнение вектора случайными уникальными значениями из заданного диапазона значений
 * \param IN destinationBegin - итератор начала вектора
 * \param IN destinationEnd - итератор конца вектора
 * \param IN startRange - начало диапазона исходных значений
 * \param IN endRange  - конец диапазона исходных значений 
 */
void randomlyFillVectorUniqueValuesFromGivenRange(std::vector<int>::iterator destinationBegin, std::vector<int>::iterator destinationEnd,int startRange,int endRange)
{
    if ((endRange - startRange) >= (destinationEnd - destinationBegin))
    {
		std::vector<int> source;
		for(int i = startRange;i<=endRange;i++)
		{
            source.push_back(i);
		}

        source.shrink_to_fit();

    	std::random_shuffle(source.begin(), source.end());

        std::vector<int>::iterator sourseIter = source.begin();
        std::vector<int>::iterator destinationIter = destinationBegin;

        while(destinationIter != destinationEnd)
        {
            *destinationIter = *sourseIter;

            sourseIter++;
            destinationIter++;
        }

    }
    else
    {
        throw "The specified range of values is too small";
    }
}

/**
 * \brief - сравнение векторов на однозначное соответсвие
 * \param IN controlBegin - итератор начала контрольного вектора
 * \param IN controlEnd - итератор конца контрольного вектора
 * \param IN subjectBegin - итератор начала проверяемого вектора
 * \param IN subjectEnd - итератор конца проверяемого вектора
 * \param OUT correct - количество значений находящихся в контрольном векторе на правильных местах
 * \param OUT almostCorrect - количество значений находящихся в контрольном векторе,но имеющие неправильное место
 */
void compareVectors(std::vector<int>::iterator controlBegin, std::vector<int>::iterator controlEnd, std::vector<int>::iterator subjectBegin, std::vector<int>::iterator subjectEnd, short int& correct ,short int& almostCorrect)
{
    if((controlEnd - controlBegin) == (subjectEnd - subjectBegin))
    {
        std::vector<int>::iterator controlIter = controlBegin;

        while(controlIter != controlEnd)
        {
            std::vector<int>::iterator subjectIter = subjectBegin;

            //Если элементы стоящие на одинаковом растоянии от начала равны
            if (*controlIter == *(subjectIter + (controlIter - controlBegin)))
            {
                correct += 1;
            }
            else
            {
	            while (subjectIter != subjectEnd)
	            {
                    if (*controlIter == *subjectIter)
                    {
                        almostCorrect += 1;
                        break;
                    }
                    subjectIter++;
	            }
            }

            controlIter++;
        }
    }
    else
    {
        throw "vectors for comparison have different lengths";
    }
}

/**
 * \brief Посимвольный ввод числа из консоли в вектор 
 * \param OUT destinationReverseBegin - обратный итератор начала вектора
 * \param OUT destinationReverseEnd - обратный итератор конца вектора 
 * \return Если введенное число не равно длине вектора return false
 */
bool enterNumberIntoVector(std::vector<int>::reverse_iterator destinationReverseBegin, std::vector<int>::reverse_iterator destinationReverseEnd)
{
    std::string enteredValues;
    std::cin >> enteredValues;

    if (enteredValues.length() == destinationReverseEnd - destinationReverseBegin)
    {
        int number;

        try 
        {
            number = std::stoi(enteredValues);
        }
        catch (std::invalid_argument) 
        {
            return false;
        }

        for (std::vector<int>::reverse_iterator destinationIter = destinationReverseBegin; destinationIter != destinationReverseEnd; destinationIter++)
        {
            *destinationIter = number % 10;
            number = number / 10;
        }

        return true;
    }
    else
    {
        return false;
    }


}

/**
 * \brief Вывод вектора в консоль
 * \param IN sourceBegin - итератор начала вектора
 * \param IN sourceEnd - итератор конца вектора
 */
void outputVectorToConsole(std::vector<int>::iterator sourceBegin, std::vector<int>::iterator sourceEnd)
{
	for(std::vector<int>::iterator sourceIter = sourceBegin; sourceIter < sourceEnd;++sourceIter)
	{
        std::cout << *sourceIter << " ";
	}
}


int main()
{
    short int running = 1;
    std::vector<int> decisions(4);
    std::vector<int> userResponses(4);

    randomlyFillVectorUniqueValuesFromGivenRange(decisions.begin(), decisions.end(), 0, 9);

	std::cout << "You have to guess the number of 4 non - repeating digits\n\n";

    while (running) 
    {
        short int correctNumbers = 0;
        short int numberOfAttempts = 10;

        std::cout << "You have to guess the number of 4 non - repeating digits\n\n";

        while (correctNumbers != 4 && numberOfAttempts > 0)
        {
            short int almostCorrectNumbers = 0;
            correctNumbers = 0;

            std::cout << "Enter 4 digits: ";

            if (enterNumberIntoVector(userResponses.rbegin(), userResponses.rend()))
            {
                compareVectors(decisions.begin(), decisions.end(), userResponses.begin(), userResponses.end(), correctNumbers, almostCorrectNumbers);

                std::cout << "\nCorrect numbers = " << correctNumbers << "; ";
                std::cout << "Almost correct numbers = " << almostCorrectNumbers << ".\n";

                numberOfAttempts--;
                std::cout << "You have " << numberOfAttempts << " attempts left\n\n" ;
            }
            else 
            {
                std::cout << "\nWrong number!!!\n\n";
                continue;
            }
        }

        if (correctNumbers == 4) 
        {
            outputVectorToConsole(decisions.begin(), decisions.end());
            std::cout << "Congratulations you have won !!!\n";
        }
        else
        {
            std::cout << "All attempts ended :(\n";
        }
            


        std::cout << "\nIf you want to exit the game, press 0, if you want to play again, press any other number:";
        std::cin >> running ;
        std::cout << "\n";
    }
}
