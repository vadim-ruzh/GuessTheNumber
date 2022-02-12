#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <deque>
#include <iomanip>
#include <iterator>
#include <array>
#include <list>
#include <stdlib.h>

#define ERROR_RETURN(error_code, msg) \
	std::cout << __FILE__ << ":" << __LINE__ << " ERROR: function " << __FUNCTION__ \
		<< msg; \
	return error_code;

enum results
{
	sOk = 0,
	eFail,
	eInvalidArgument,
	eInvalidUserInput
};

/**
 * \brief - заполнение вектора случайными уникальными значениями из заданного диапазона значений
 * \param IN destinationBegin - итератор на начало вектора
 * \param IN destinationEnd - итератор на конец вектора
 * \param IN startRange - начало диапазона исходных значений
 * \param IN endRange  - конец диапазона исходных значений
 * \warning has no effect if ...
 * \throw std::runtime_error if ...
 */
// REWIEW: destinationBegin/End укоротить на dstBegin/End
// TODO: а теперь то что делают startRange и endRange надо заменить на функтор, по аналогии с тем как работает std::generate_n(я описал пример внутри функции в /HERE1).
/* TODO: а теперь итераторы должны быть на шаблонах, можешь посмотреть как они принимаются в том же std::random_shuffle.
 * Для начала сделай std::vector<Type>::iterator, вместо std::vector<int>::iterator.
 */
template <typename Iterator>
results randomlyFillVectorUniqueValuesFromGivenRange(
	Iterator destinationBegin, Iterator destinationEnd,
	int32_t startRange, int32_t endRange)
{
	const auto rangeElementsCount = endRange - startRange;
	const auto destinationElementsCount = std::distance(destinationBegin, destinationEnd);

	if (rangeElementsCount < destinationElementsCount)
	{
		ERROR_RETURN(results::eInvalidArgument, ": The specified range of values is too small");
	}

	std::vector<int> source;
	source.reserve(rangeElementsCount);
	std::generate_n(
		std::back_inserter(source), source.size(),
		[i = startRange]() mutable { return i++; });

	std::shuffle(source.begin(), source.end(), std::mt19937(std::random_device()()));

	std::copy_n(source.begin(), destinationElementsCount, destinationBegin);

	return results::sOk;
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
template <typename ControlIterator, typename SubjectIterator>
results compareVectors(
	ControlIterator controlBegin, ControlIterator controlEnd,
	SubjectIterator subjectBegin, SubjectIterator subjectEnd,
	int& correct, int& almostCorrect)
{
	if (std::distance(controlBegin, controlEnd) != std::distance(subjectBegin, subjectEnd))
	{
		ERROR_RETURN(results::eInvalidArgument, "vectors for comparison have different lengths");
	}

	auto controlIter = controlBegin;

	for (; controlIter != controlEnd; ++controlIter)
	{
		auto subjCopy = subjectBegin;
		std::advance(subjCopy, std::distance(controlBegin, controlIter));
		if (*controlIter == *subjCopy)
		{
			correct += 1;
		}
		else
		{
			almostCorrect += std::any_of(
				subjectBegin, subjectEnd, 
				[controlIter](int i) { return i == *controlIter; });
		}
	}

	return results::sOk;
}

/**
* \brief Посимвольный ввод числа из консоли в вектор
* \param destinationReverseBegin [OUT] - обратный итератор на начало вектора
* \param destinationReverseEnd [OUT] - обратный итератор на конец вектора
* \return Если введенное число не равно длине вектора return false
*/
// TODO: вот тут вот хорошо видно почему итераторы должны быть шаблонными. А если ты захочешь заполнить не с конца в начало, а наоборот?
template <typename Iterator>
results enterNumberIntoVector(Iterator destinationReverseBegin, Iterator destinationReverseEnd)
{
	std::string enteredValues;
	std::cin >> enteredValues;

	// REWIEW: сделать else неявным, и вынести его перед if(см. комментарий /HERE2)
	if (enteredValues.length() != std::distance(destinationReverseBegin, destinationReverseEnd))
	{
		ERROR_RETURN(results::eInvalidUserInput, " to number. Internal error description");
	}

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
	catch (const std::invalid_argument& e)
	{
		ERROR_RETURN(results::eInvalidUserInput, " to number. Internal error description: " << e.what());
	}

	// REWIEW: Дополнительные итераторы не нужны, используй destinationReverseBegin и destinationReverseEnd
	for (; destinationReverseBegin != destinationReverseEnd; ++destinationReverseBegin)
	{
		*destinationReverseBegin = number % 10;
		number = number / 10;
	}

	return results::sOk;
}

int main()
{
	try
	{
		short int running = 1;
		std::list<int> decisions{};
		std::list<int> userResponses{};
		
		if (randomlyFillVectorUniqueValuesFromGivenRange(decisions.begin(), decisions.end(), 0, 9))
		{
		}

		std::cout << "You have to guess the number of 4 non - repeating digits\n\n";

		while (running)
		{
			int correctNumbers = 0;
			int numberOfAttempts = 10;

			while (correctNumbers != 4 && numberOfAttempts > 0)
			{
				int almostCorrectNumbers = 0;
				correctNumbers = 0;

				std::cout << "Enter 4 digits: ";

				if (enterNumberIntoVector(userResponses.rbegin(), userResponses.rend()))
				{
					continue;
				}

				auto result = compareVectors(decisions.begin(), decisions.end(), userResponses.begin(),
				                             userResponses.end(), correctNumbers, almostCorrectNumbers);
				switch (result)
				{
				case results::sOk: break;
				case results::eInvalidArgument:
					std::cout << "\nPROGRAM IS BROKEN, PLEASE STAND BY!!!\n\n";
					return EXIT_FAILURE;
				default:
					continue;
				}

				std::cout << "\nCorrect numbers = " << correctNumbers << "; ";
				std::cout << "Almost correct numbers = " << almostCorrectNumbers << ".\n";

				numberOfAttempts--;
				std::cout << "You have " << numberOfAttempts << " attempts left\n\n";
			}

			if (correctNumbers == 4)
			{
				std::copy(decisions.begin(), decisions.end(), std::ostream_iterator<int>(std::cout, " "));
				std::cout << "Congratulations you have won !!!\n";
			}
			else
			{
				std::cout << "All attempts ended :(\n";
			}

			std::cout <<
				"\nIf you want to exit the game, press 0, if you want to play again, press any other number:";
			std::cin >> running;

			std::cout << "\n";
		}

		return EXIT_SUCCESS;
	}
	catch (...)
	{
		std::cout << __FILE__ << ":" << __LINE__ << " ERROR: function " << __FUNCTION__
			<< ": unexpected error";

		return EXIT_FAILURE;
	}
}
