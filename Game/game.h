#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

#include "error_processing.h"
#include "game_config.h"

namespace game
{

	// ���� ���������� ������ ������� 
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
	 * @brief ���������� ������� ���������� �� ��������� ���������,� ��������� �������
	 * @tparam Iterator ��� ��������� �� ������
	 * @param dstBegin �������� �� ������ �������
	 * @param dstEnd �������� �� ����� �������
	 * @param startRange  ������ ��������� �������� ��������
	 * @param endRange - ����� ��������� �������� ��������
	 * @return resultCode - ��� ���������� ������ �������
	 * @remarks - ������� �� ����� ������,���� ����� ��������� �������� �������� <= 0
	 * @remarks - ������� �� ����� ������,���� ����� ��������� �������� �������� < ����� �������
	 */
	template <typename Iterator>
	results::ResultCode FillVectorUniqueValuesFromRangeAtRandom(
		Iterator dstBegin, Iterator dstEnd,
		int32_t startRange, int32_t endRange)
	{
		//�������� �� ������������ ������ ��������� �������� �������� 
		if (startRange >= endRange)
		{
			ERROR_RETURN(results::eInvalidArgument) << ":The length of the range is incorrect ";
		}

		int32_t rangeElementsCount;
		//���������� ������� ��������� �������� ��������,� ����������� �� �������� ������
		if (startRange < 0 && endRange < 0)
		{
			rangeElementsCount = -(endRange - startRange);
		}
		else
		{
			rangeElementsCount = endRange - startRange;
		}
		

		const auto dstElementsCount = std::distance(dstBegin, dstEnd);
		if (rangeElementsCount < dstElementsCount)
		{
			ERROR_RETURN(results::eInvalidArgument) << ": The specified range of values is too small";
		}

		std::vector<int32_t> source;
		source.reserve(rangeElementsCount);
		std::generate_n(std::back_inserter(source), source.capacity(),
					[i = startRange]() mutable { return i++; });

		std::shuffle(source.begin(), source.end(), std::mt19937(std::random_device()()));
		std::copy_n(source.begin(), dstElementsCount, dstBegin);

		return results::sOk;
	}

	/**
	 * @brief ��������� �������� �� ����������� �����������
	 * @tparam Iterator �������� �� ������
	 * @param controlBegin �������� �� ������ ������������ �������
	 * @param controlEnd �������� �� ����� ������������ �������
	 * @param subjectBegin �������� �� ������ ������������� �������
	 * @param subjectEnd �������� �� ����� ������������� �������
	 * @param correct ���������� ��������� �� subject ������� ����������� ����������� � control
	 * @param almostCorrect ���������� ��������� �� subject,����������� � control,�� ������� ����������� ���������
	 * @return resultCode ��� ���������� ������ �������
	 * @remarks ������� �� ����� ������,���� ������� ����� ������ �����
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
	 * \brief ������������ ���� ����� �� ������� � ������
	 * \tparam - �������� �� ������
	 * \param dstBegin - �������� �� ������ �������
	 * \param dstEnd -�������� �� ����� �������
	 * \return resultCode - ��� ���������� ������ �������
	 * \warning - ������� �� ����� ������,���� �������� ����������������� ����� �� �������� ������
	 * \warning - ������� �� ����� ������,���� ������ �������� ����������������� ����� �� ����� ����� �������
	 */
	template <typename Iterator>
	results::ResultCode enterNumberIntoVector(Iterator dstBegin, Iterator dstEnd)
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());

		std::string enteredValues;

		std::cin >> enteredValues;
		if(std::cin.fail())
		{
			USER_ERROR(results::eInvalidUserInput) << "An error occurred while trying to enter this value : " << enteredValues;
		}

		try
		{
			stoi(enteredValues);
		}
		catch (std::invalid_argument)
		{
			USER_ERROR(results::eInvalidUserInput) << " The entered value :" << enteredValues << " is not a number ";
		}
		catch(std::exception)
		{
			USER_ERROR(results::eInvalidUserInput) << " Unexpected input error";
		}


		auto dstRange = std::distance(dstBegin, dstEnd);
		if (enteredValues.length() != dstRange)
		{
			USER_ERROR(results::eInvalidUserInput) << " The length of the entered value is incorrect: "
				<< "Lenght entered value = " << enteredValues.length() << " Range destination vector = " << dstRange;
		}

		std::transform(enteredValues.begin(), enteredValues.end(), dstBegin, [](char ch) { return ch - '0'; });

		return results::sOk;
	}

	results::ResultCode StartEventLoop(conf::Configuration& config);

} // namespace game