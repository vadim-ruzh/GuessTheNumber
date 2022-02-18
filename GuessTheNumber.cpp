#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>


//Вывод кода результата работы функции и сообщения об ошибке 
#define ERROR_RETURN(error_code) \
	for(int16_t __macro_i = 0;;++__macro_i)\
		if(__macro_i)\
			return error_code;\
		else\
		std::cout << "\n" << __FILE__ << ":" << __LINE__ << " ERROR: function " << __FUNCTION__  



//Коды результата работы функций 
enum resultCode
{
	sOk = 0,
	eUnexpectedError,
	eInvalidArgument,
	eInvalidUserInput,
	eIncorrectConfigurations
};


/**
 * \brief - Заполнение вектора значениями из заданного диапазона,в случайном порядке
 * \tparam Iterator - Итератор на вектор
 * \param dstBegin - Итератор на начало вектора 
 * \param dstEnd - Итератор на конец вектора
 * \param startRange - Начало диапазона исходных значений 
 * \param endRange - Конец диапазона исходных значений
 * \return resultCode - Код результата работы функции
 * \warning - функция не имеет смысла,если длина диапазона исходных значений <= 0
 * \warning - функция не имеет смысла,если длина диапазона исходных значений < длины вектора
 */
template <typename Iterator>
resultCode fillVectorUniqueValuesFromRangeAtRandom(Iterator dstBegin,Iterator dstEnd, int32_t startRange, int32_t endRange)
{
	//Проверка на корректность границ диапазона исзодных значений 
	if (startRange >= endRange)
	{
		ERROR_RETURN(eInvalidArgument) << ":The length of the range is incorrect ";
	}

	int32_t rangeElementsCount;

	//Вычесление размера диапазона исходных значений,в зависимости от заданных границ
	if (startRange >= 0 && endRange > 0)
	{
		rangeElementsCount = endRange - startRange;
	}
	else
	{
		if (startRange < 0 && endRange < 0)
		{
			rangeElementsCount = startRange * (-1) - endRange * (-1);
		}
		else
		{
			rangeElementsCount = startRange * (-1) + endRange;
		}
	}

	const auto dstElementsCount = std::distance(dstBegin, dstEnd);

	if (rangeElementsCount < dstElementsCount)
	{
		ERROR_RETURN(resultCode::eInvalidArgument) << ": The specified range of values is too small";
	}

	std::vector<int32_t> source;
	source.reserve(rangeElementsCount);


	std::generate_n(std::back_inserter(source), source.capacity(),
							[i = startRange]() mutable { return i++; });
	std::shuffle(source.begin(), source.end(), std::mt19937(std::random_device()()));
	std::copy_n(source.begin(), dstElementsCount, dstBegin);

	return resultCode::sOk;
}


/**
 * \brief Сравнение векторов на однозначное соответсвие 
 * \tparam ControlIterator - Итератор на вектор
 * \tparam SubjectIterator - Итератор на вектор
 * \param controlBegin - Итератор на начало контрольного вектора
 * \param controlEnd - Итератор на конец контрольного вектора
 * \param subjectBegin - Итератор на начало сравниваемого вектора
 * \param subjectEnd - Итератор на конец сравниваемого вектора
 * \param correct - Количество элементов из subject имеющие однозначное соотвествие в control 
 * \param almostCorrect - Количество элементов из subject,находящиеся в control,но имеющие неправильно положение 
 * \return resultCode - Код результата работы функции
 * \warning - Функция не имеет смысла,если векторы имеют разную длину
 */
template <typename Iterator>
resultCode compareVectors(Iterator controlBegin, Iterator controlEnd,
						  Iterator subjectBegin, Iterator subjectEnd,
							int32_t& correct, int32_t& almostCorrect)
{
	if (std::distance(controlBegin, controlEnd) != std::distance(subjectBegin, subjectEnd))
	{
		ERROR_RETURN(resultCode::eInvalidArgument) << "vectors for comparison have different lengths";
	}

	for (auto controlIter = controlBegin; controlIter != controlEnd; ++controlIter)
	{
		auto subjectIter = subjectBegin + std::distance(controlBegin, controlIter);

		if (*controlIter == *subjectIter)
		{
			correct += 1;
		}
		else
		{
			almostCorrect += std::any_of(subjectBegin, subjectEnd,
					[controlIter](int i) { return i == *controlIter; });
		}
	}

	return resultCode::sOk;
}


/**
 * \brief Посимвольный ввод числа из консоли в вектор
 * \tparam - Итератор на вектор
 * \param dstBegin - Итератор на начало вектора
 * \param dstEnd -Итератор на конец вектора
 * \return resultCode - Код результата работы функции
 * \warning - Функция не имеет смысла,если значение пользовательского ввода не является числом
 * \warning - Функция не имеет смысла,если размер значения пользовательского ввода не равен длине вектора  
 */
template <typename Iterator>
resultCode enterNumberIntoVector(Iterator dstBegin, Iterator dstEnd)
{
	int32_t inputVal;
	std::cin >> inputVal;

	if(std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		ERROR_RETURN(resultCode::eInvalidUserInput) << " :The entered value is not a number ";
	}

	std::string enteredValues = std::to_string(inputVal);

	if (enteredValues.length() != std::distance(dstBegin,dstEnd))
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		ERROR_RETURN(resultCode::eInvalidUserInput) << " :The length of the entered value is incorrect ";
	}

	std::transform(enteredValues.begin(), enteredValues.end(), dstBegin, [](char ch) {return ch - '0'; });

	return resultCode::sOk;
}


//Конфигурация игры
struct gameConfiguration
{
	//Количество попыток у пользователя ввести значение 
	int32_t numberOfAttempts = 10;

	//Начало и конец диапазона чисел 
	int32_t startRangeOfInitialValues = 0;
	int32_t endRangeOfInitialValues = 9;

	//Количество цифр в числе 
	int32_t numberOfDigits = 4;
	//Количество верных цифр в числе 
	int32_t needCorrectNumbers = 4;
};


int main()
{
	try
	{
		gameConfiguration config;

		//Проверка корректности параметров конфигурации игры 
		if (config.numberOfDigits < 1 || config.needCorrectNumbers < 1)
		{
			ERROR_RETURN(eIncorrectConfigurations) << " :The configuration of the number of digits is incorrect ";
		}
		if ((config.startRangeOfInitialValues < 0 || config.startRangeOfInitialValues > 9)
			|| (config.endRangeOfInitialValues < 0 || config.endRangeOfInitialValues > 9))
		{
			ERROR_RETURN(eIncorrectConfigurations) << " :The configuration of the range of initial values is set incorrectly ";
		}
		if(config.numberOfAttempts <= 0)
		{
			ERROR_RETURN(eIncorrectConfigurations) << " :The configuration of the number of attempts is not set correctly ";
		}

		while (true)
		{
			std::vector<int32_t> decisions(config.numberOfDigits);
			std::vector<int32_t> userResponses(config.numberOfDigits);

			if (fillVectorUniqueValuesFromRangeAtRandom(
				decisions.begin(),decisions.end(),
				config.startRangeOfInitialValues, config.endRangeOfInitialValues))
			{
				return EXIT_FAILURE;
			}

			std::cout << "You have to guess the number of " << config.numberOfDigits << " non - repeating digits\n";
			std::cout << "to win, you need to enter " << config.numberOfDigits << " correct numbers\n\n";

			int32_t correctNumbers = 0;
			int32_t attempts = config.numberOfAttempts;

			while (correctNumbers != config.needCorrectNumbers && attempts > 0)
			{
				int32_t almostCorrectNumbers = 0;
				correctNumbers = 0;

				std::cout << "Enter " << config.numberOfDigits << " digits: ";

				if (enterNumberIntoVector(userResponses.begin(), userResponses.end()))
				{
					std::cout << "\n\nTry entering the value again\n";
					continue;
				}

				if(compareVectors(decisions.begin(), decisions.end(),
							userResponses.begin(),userResponses.end(),
										correctNumbers, almostCorrectNumbers))
				{
					return EXIT_FAILURE;
				}
				

				std::cout << "\nCorrect numbers = " << correctNumbers << "; ";
				std::cout << "Almost correct numbers = " << almostCorrectNumbers << ".\n";

				attempts--;
				std::cout << "You have " << attempts << " attempts left\n\n";
			}


			if (correctNumbers == config.needCorrectNumbers)
			{
				std::copy(decisions.begin(), decisions.end(), std::ostream_iterator<int32_t>(std::cout, " "));
				std::cout << "Congratulations you have won !!!\n";
			}
			else
			{
				std::cout << "All attempts ended :(\n";
			}

			//Предложение пользователю сыграть еще раз 
			std::cout << "\nIf you want to play again, press 1,if you want to exit the game , press any other button:";
			bool startAgain = true;
			std::cin >> startAgain;
			if (std::cin.fail() || !startAgain)
			{
				return EXIT_FAILURE;
			}

			std::cout << "\n";
		}
	}
	catch (...)
	{
		ERROR_RETURN(eUnexpectedError) << " :An undefined error has occurred";
	}
}
