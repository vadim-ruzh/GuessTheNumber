#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

/**
 * \brief - заполнение вектора случайными уникальными значениями из заданного диапазона значений
 * \param IN destinationBegin - итератор на начало вектора
 * \param IN destinationEnd - итератор на конец вектора
 * \param IN startRange - начало диапазона исходных значений
 * \param IN endRange  - конец диапазона исходных значений
 */
// REWIEW: destinationBegin/End укоротить на dstBegin/End
// TODO: а теперь то что делают startRange и endRange надо заменить на функтор, по аналогии с тем как работает std::generate_n(я описал пример внутри функции в /HERE1).
/* TODO: а теперь итераторы должны быть на шаблонах, можешь посмотреть как они принимаются в том же std::random_shuffle.
 * Для начала сделай std::vector<Type>::iterator, вместо std::vector<int>::iterator.
 */
void randomlyFillVectorUniqueValuesFromGivenRange(std::vector<int>::iterator destinationBegin, std::vector<int>::iterator destinationEnd,int startRange,int endRange)
{
	/* REWIEW: сходу сложно понять почему именно так.
	 * Нужно описать подобные немаловажные вещи в секции \warning в комментарию к функции вида: Функция не имеет эффекта если...
	 */
	/* REWIEW: /HERE2 стоит заменить на
	 *		if((endRange - startRange) >= (destinationEnd - destinationBegin))
	 *		{
	 *			throw ...;
	 *		}
	 *		std::vector<int> source;
	 *		...
	 *	Тем самым избавиться от вложенности, сделав else неявным
	 */
    if ((endRange - startRange) >= (destinationEnd - destinationBegin))
    {
    	/* REWIEW: /HERE1 стоит заменить на std::generate_n
    	 * с генератором вида [i = startRange] () mutable { return i++; }
    	 */
    	/* REWIEW:
    	 * Мы точно значем, что в векторе будет endRange-startRange элементов
    	 *		поэтому мы можем заранее выделить всю нужную память.
    	 * Потому что иначе, вектор будет ресайзиться почти при каждом push_back-e, а это:
    	 *		1. Запрос у операционки нового(возможно длинного) куска непрерывной памяти.
    	 *				Если память фрагментирована, то его может быть сложно(долго) найти.
    	 *		2. Копирование всех элементов из 'старой' памяти в 'новую'
    	 *		3. Освобождение старой памяти.
    	 *		3.* Если элементы в контейнере сложные(к примеру std::string),
    	 *				то в процессе освобождения для каждого элемента вызовется деструкторю
    	 * Сложность такого алгоритма можешь попробовать посчитать сам.
    	 * И всего этого можно избежать вызвав source.reserve(endRange-startRange);
    	 * Тогда и shrink_to_fit не нужно будет вызывать.
    	 */
		std::vector<int> source;
		for(int i = startRange;i<=endRange; ++i)
		{
            source.push_back(i);
		}

        source.shrink_to_fit();

    	/* REWIEW: смотри на варнинги от решарпера.
    		std::random_shuffle был удалён в c++17, используй std::shuffle
    	*/
    	std::random_shuffle(source.begin(), source.end());

        std::vector<int>::iterator sourseIter = source.begin();
    	// REWIEW: дополнительный итератор не нужен, вместо destinationIter можно использовать destinationBegin.
        std::vector<int>::iterator destinationIter = destinationBegin;

    	/* REWIEW: стоит заменить как минимум на for(;dstBegin != dstEnd; ++sourseIter, ++destinationIter)
    	 * Но ещё лучше будет использовать std::copy, ещё в похожих кейсах используют std::transform
    	 */
        while(destinationIter != destinationEnd)
        {
            *destinationIter = *sourseIter;

        	// REWIEW: заменить на префиксный инкремент
            sourseIter++;
            destinationIter++;
        }

    }
    else
    {
    	// REWIEW: выбрасывать нужно исключения типа std:::runtime_exception, но не сырые строки
    	// REWIEW: все исключения функции нужно описать в секции \throws(или \throw) в комментарии к функции.
        throw "The specified range of values is too small";
    }
}

/**
 * \brief - сравнение векторов одинаковой длин на однозначное соответсвие
 * \param IN controlBegin - итератор на начало контрольного вектора
 * \param IN controlEnd - итератор на конец контрольного вектора
 * \param IN subjectBegin - итератор на начало проверяемого вектора
 * \param IN subjectEnd - итератор на конец проверяемого вектора
 * \param OUT correct - количество значений находящихся в контрольном векторе на правильных местах
 * \param OUT almostCorrect - количество значений находящихся в контрольном векторе,но имеющие неправильное место
 */
/* REWIEW: а нельзя назвать controlBegin-firstBegin, а subjectBegin-secondBegin?
 * Результат фунции поменяется, если мы вместо control-a будем передавать subject(и наоборот)?
 */
// REWIEW: слишком длинная строка, надо её форматировать. Иначе приходится 'крутить' вправо для того чтобы увидеть все аргументы. 
// REWIEW: почему элементы вектора int, а тот же correct-short int?
void compareVectors(std::vector<int>::iterator controlBegin, std::vector<int>::iterator controlEnd, std::vector<int>::iterator subjectBegin, std::vector<int>::iterator subjectEnd, short int& correct ,short int& almostCorrect)
{
	/* REWIEW: сходу сложно понять почему именно так.
	 * Нужно описать подобные немаловажные вещи в секции \warning в комментарию к функции вида: Функция не имеет эффекта если...
	 */
	 /* REWIEW: стоит заменить на
	  *		if((controlEnd - controlBegin) != (subjectEnd - subjectBegin))
	  *		{
	  *			throw ...;
	  *		}
	  *		std::vector<int>::iterator controlIter = controlBegin;
	  *		...
	  *	Тем самым избавиться от вложенности, сделав else неявным
	  */
    if((controlEnd - controlBegin) == (subjectEnd - subjectBegin))
    {
		// REWIEW: итератор controlIter не нужен, его можно заменить на controlBegin
        std::vector<int>::iterator controlIter = controlBegin;

        while(controlIter != controlEnd)
        {
        	// REWIEW: итератор subjectIter не нужен, его можно заменить на subjectBegin
            std::vector<int>::iterator subjectIter = subjectBegin;

            //Если элементы стоящие на одинаковом растоянии от начала равны
            if (*controlIter == *(subjectIter + (controlIter - controlBegin)))
            {
				// REWIEW: заменить на инкремент
                correct += 1;
            }
            else
            {
            	/* REWIEW: заменить на
            	 * almostCorrect += std::any_of(subjectBegin, subjectEnd, *controlIter);
            	 */ 
	            while (subjectIter != subjectEnd)
	            {
                    if (*controlIter == *subjectIter)
                    {
						// REWIEW: заменить на инкремент
                        almostCorrect += 1;
                        break;
                    }
					// REWIEW: заменить на префиксный инкремент
                    subjectIter++;
	            }
            }

			// REWIEW: заменить на префиксный инкремент
            controlIter++;
        }
    }
    else
    {
		// REWIEW: выбрасывать нужно исключения типа std:::runtime_exception, но не сырые строки
		// REWIEW: все исключения функции нужно описать в секции \throws(или \throw) в комментарии к функции.
        throw "vectors for comparison have different lengths";
    }
}


/**
* \brief Посимвольный ввод числа из консоли в вектор
* \param OUT destinationReverseBegin - обратный итератор на начало вектора
* \param OUT destinationReverseEnd - обратный итератор на конец вектора
* \return Если введенное число не равно длине вектора return false
*/
// TODO: вот тут вот хорошо видно почему итераторы должны быть шаблонными. А если ты захочешь заполнить не с конца в начало, а наоборот?
bool enterNumberIntoVector(std::vector<int>::reverse_iterator destinationReverseBegin, std::vector<int>::reverse_iterator destinationReverseEnd)
{
	std::string enteredValues;
	std::cin >> enteredValues;

	// REWIEW: сделать else неявным, и вынести его перед if(см. комментарий /HERE2)
	if (enteredValues.length() == destinationReverseEnd - destinationReverseBegin)
	{
		int number;

		try
		{
			number = std::stoi(enteredValues);
		}
		// REWIEW: catch (const std::invalid_argument& e)
		/* REWIEW: про такие вот 'заглушенные' исключения лучше писать в лог причину ошибки,
		 *		чтобы потом по логам можно было понять в чём дело.
		 * Сейчас же, лучше писать в консоль:
		 *		std::cout << __FILE__ << ":" << __LINE__ << " ERROR: function " << __FUNCTION__ << ": fail to convert entered string " << std::quoted(enteredValues)
		 *				  << " to number. Error description: " << e.what();
		 * Это заклинание выведет примерно следующее:
		 *	e:\projects\guessthenumber\guessthenumber.cpp:198 ERROR: function enterNumberIntoVector: fail to convert entered string "qwer" to number. Internal error description: invalid stoi argument
		 */
		catch (std::invalid_argument e)
		{
			std::cout << __FILE__ << ":" << __LINE__ << " ERROR: function " << __FUNCTION__ << ": fail to convert entered string " << std::quoted(enteredValues)
				<< " to number. Internal error description: " << e.what();

			/* REWIEW: ты пишешь: \return Если введенное число не равно длине вектора return false
			 * Но этот кейс не похож на то, что ты описал.
			 */
			return false;
		}

		// REWIEW: Дополнительные итераторы не нужны, используй destinationReverseBegin и destinationReverseEnd
		for (std::vector<int>::reverse_iterator destinationIter = destinationReverseBegin; destinationIter != destinationReverseEnd; ++destinationIter)
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
 * \param IN sourceBegin - итератор на начало вектора
 * \param IN sourceEnd - итератор на конец вектора
 */
void outputVectorToConsole(std::vector<int>::iterator sourceBegin, std::vector<int>::iterator sourceEnd)
{
	// REWIEW: используй std::transform в паре с std::ostream_iterator
	for(std::vector<int>::iterator sourceIter = sourceBegin; sourceIter != sourceEnd;++sourceIter)
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
