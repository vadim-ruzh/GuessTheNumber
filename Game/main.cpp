#include <boost/filesystem.hpp>
#include "error_processing.h"
#include "game.h"
#include "game_config_reader.h"

int main()
{
	try
	{
		const auto pathToConfig = boost::filesystem::current_path() / "config.txt";
		std::ifstream configFile(pathToConfig.c_str());
		conf::Configuration config;

		ERROR_RETURN_EX(conf::GetConfigFromTenge(configFile, config), EXIT_FAILURE)
			<< " Configuration extraction error";

		//Проверка корректности параметров конфигурации игры 
		ERROR_RETURN_EX(config.numberOfDigits < 1 || config.needCorrectNumbers < 1,EXIT_FAILURE)
			<< " :The configuration of the number of digits is incorrect ";

		bool res = (config.startRangeOfInitialValues < 0 || config.startRangeOfInitialValues > 9)
			|| (config.endRangeOfInitialValues < 0 || config.endRangeOfInitialValues > 9);

		ERROR_RETURN_EX(res,EXIT_FAILURE)
			<< " :The configuration of the range of initial values is set incorrectly ";
		
		ERROR_RETURN_EX(config.numberOfAttempts <= 0,EXIT_FAILURE)
			<< " :The configuration of the number of attempts is not set correctly ";

		ERROR_RETURN_EX(game::StartEventLoop(config), EXIT_FAILURE)
			<< "Can't start game event loop";
	}
	catch (...)
	{
		ERROR_RETURN(EXIT_FAILURE) << " :An undefined error has occurred";
	}
	
}
