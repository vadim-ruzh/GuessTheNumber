#ifndef BL_GAME_H__
#define BL_GAME_H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>

#include "error_processing.h"
#include "game_config.h"

namespace game
{

// Коды результата работы функций 
namespace results
{
	enum ResultCode
	{
		sOk = 0,
		eUnexpectedError,
		eInvalidArgument,
		eInvalidUserInput
	};
}

/**
 * @brief Заполнение вектора значениями из заданного диапазона,в случайном порядке
 * @tparam Iterator тип итератора на вектор
 * @param dstBegin Итератор на начало вектора
 * @param dstEnd Итератор на конец вектора
 * @param startRange  Начало диапазона исходных значений
 * @param endRange - Конец диапазона исходных значений
 * @return resultCode - Код результата работы функции
 * @remarks - функция не имеет смысла,если длина диапазона исходных значений <= 0
 * @remarks - функция не имеет смысла,если длина диапазона исходных значений < длины вектора
 */
template <typename Iterator>
results::ResultCode FillVectorUniqueValuesFromRangeAtRandom(
	Iterator dstBegin, Iterator dstEnd,
	int32_t startRange, int32_t endRange)
{
	//Проверка на корректность границ диапазона исзодных значений 
	if (startRange >= endRange)
	{
		ERROR_RETURN(results::eInvalidArgument) << ":The length of the range is incorrect ";
	}

	int32_t rangeElementsCount;
	//Вычесление размера диапазона исходных значений,в зависимости от заданных границ
	if (startRange >= 0 && endRange > 0)
	{
		rangeElementsCount = endRange - startRange;
	}
	else if (startRange < 0 && endRange < 0)
	{
		rangeElementsCount = startRange * (-1) - endRange * (-1);
	}
	else
	{
		rangeElementsCount = startRange * (-1) + endRange;
	}

	const auto dstElementsCount = std::distance(dstBegin, dstEnd);
	if (rangeElementsCount < dstElementsCount)
	{
		ERROR_RETURN(results::eInvalidArgument) << ": The specified range of values is too small";
	}

	std::vector<int32_t> source;
	source.reserve(rangeElementsCount);
	std::generate_n(
		std::back_inserter(source), source.capacity(),
		[i = startRange]() mutable { return i++; });

	std::shuffle(source.begin(), source.end(), std::mt19937(std::random_device()()));
	std::copy_n(source.begin(), dstElementsCount, dstBegin);

	return results::sOk;
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
results::ResultCode compareVectors(Iterator controlBegin, Iterator controlEnd,
	Iterator subjectBegin, Iterator subjectEnd,
	int32_t& correct, int32_t& almostCorrect)
{
	if (std::distance(controlBegin, controlEnd) != std::distance(subjectBegin, subjectEnd))
	{
		ERROR_RETURN(results::eInvalidArgument) << " vectors for comparison have different lengths";
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

	return results::sOk;
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
results::ResultCode enterNumberIntoVector(Iterator dstBegin, Iterator dstEnd)
{
	int32_t inputVal;
	std::cin >> inputVal;
	if (std::cin.fail())
	{
		// TODO: DRY
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		ERROR_RETURN(results::eInvalidUserInput) << " :The entered value is not a number ";
	}

	std::string enteredValues = std::to_string(inputVal);
	if (enteredValues.length() != std::distance(dstBegin, dstEnd))
	{
		// TODO: DRY
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		ERROR_RETURN(results::eInvalidUserInput) << " :The length of the entered value is incorrect ";
	}

	std::transform(enteredValues.begin(), enteredValues.end(), dstBegin, [](char ch) { return ch - '0'; });

	return results::sOk;
}

results::ResultCode StartEventLoop(game::Configuration& config);

} // namespace game

#endif