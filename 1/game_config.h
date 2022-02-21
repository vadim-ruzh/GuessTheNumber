#ifndef BL_GAME_CONFIG_H__
#define BL_GAME_CONFIG_H__

#include <cstdint>

namespace game
{

//������������ ����
struct Configuration
{
	//���������� ������� � ������������ ������ �������� 
	int32_t numberOfAttempts;

	//������ � ����� ��������� ����� 
	int32_t startRangeOfInitialValues;
	int32_t endRangeOfInitialValues;

	//���������� ���� � ����� 
	int32_t numberOfDigits;
	//���������� ������ ���� � ����� 
	int32_t needCorrectNumbers;
};

}

#endif
