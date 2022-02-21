#ifndef BL_GAME_CONFIG_H__
#define BL_GAME_CONFIG_H__

#include <cstdint>

namespace game
{

//Конфигурация игры
struct Configuration
{
	//Количество попыток у пользователя ввести значение 
	int32_t numberOfAttempts;

	//Начало и конец диапазона чисел 
	int32_t startRangeOfInitialValues;
	int32_t endRangeOfInitialValues;

	//Количество цифр в числе 
	int32_t numberOfDigits;
	//Количество верных цифр в числе 
	int32_t needCorrectNumbers;
};

}

#endif
