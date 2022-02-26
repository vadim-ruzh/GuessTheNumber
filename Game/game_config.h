#pragma once

namespace conf
{
	//Конфигурация игры - значения по умолчанию
	struct Configuration
	{
		//Количество попыток у пользователя ввести значение 
		int32_t numberOfAttempts =0;

		//Начало и конец диапазона чисел 
		int32_t startRangeOfInitialValues = 0;
		int32_t endRangeOfInitialValues = 0;

		//Количество цифр в числе 
		int32_t numberOfDigits = 0;
		//Количество верных цифр в числе 
		int32_t needCorrectNumbers = 0;

	};

	
	enum resultCode
	{
		sOk = 0,
		eBadConfiguration,
		eEmptyConfiguration,
		eFileReadingError
	};


}//namespace conf

