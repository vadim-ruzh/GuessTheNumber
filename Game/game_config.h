#pragma once

namespace conf
{
	//������������ ���� - �������� �� ���������
	struct Configuration
	{
		//���������� ������� � ������������ ������ �������� 
		int32_t numberOfAttempts =0;

		//������ � ����� ��������� ����� 
		int32_t startRangeOfInitialValues = 0;
		int32_t endRangeOfInitialValues = 0;

		//���������� ���� � ����� 
		int32_t numberOfDigits = 0;
		//���������� ������ ���� � ����� 
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

