#pragma once

// Вывод кода результата работы функции и сообщения об ошибке 
#define ERROR_RETURN(errorCode) \
	if(errorCode)\
		for(int16_t __macro_i = 0;;++__macro_i)\
			if(__macro_i)\
				return errorCode;\
			else\
				std::cout << "\n" << __FILE__ << ":" << __LINE__ << " ERROR: function " << __FUNCTION__

#define USER_ERROR(errorCode)\
	if(errorCode)\
		for(int16_t __macro_i = 0;;++__macro_i)\
			if(__macro_i)\
				return errorCode;\
			else\
				std::cout << "\n" 



#define IF_RETURN(errorCode)\
	if(errorCode)\
		return errorCode\



#define ERROR_RETURN_EX(errorCode, mapper) \
	if(errorCode)\
		ERROR_RETURN(mapper)