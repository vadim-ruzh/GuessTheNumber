#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <boost/filesystem.hpp>

#include "error_processing.h"
#include "game.h"
#include "game_config_reader.h"

int main()
{
	try
	{
		const auto pathToConfig = boost::filesystem::current_path() / "config.ini";
		std::ifstream configFile(pathToConfig.c_str());
		if(!configFile)
		{
			ERROR_RETURN(EXIT_FAILURE) << " : There is no config file along path " << pathToConfig;
		}

		auto config = game::GetConfig(configFile);

		//Проверка корректности параметров конфигурации игры 
		if (config.numberOfDigits < 1 || config.needCorrectNumbers < 1)
		{
			ERROR_RETURN(EXIT_FAILURE) << " :The configuration of the number of digits is incorrect ";
		}
		if ((config.startRangeOfInitialValues < 0 || config.startRangeOfInitialValues > 9)
			|| (config.endRangeOfInitialValues < 0 || config.endRangeOfInitialValues > 9))
		{
			ERROR_RETURN(EXIT_FAILURE) << " :The configuration of the range of initial values is set incorrectly ";
		}
		if (config.numberOfAttempts <= 0)
		{
			ERROR_RETURN(EXIT_FAILURE) << " :The configuration of the number of attempts is not set correctly ";
		}

		ERROR_RETURN_EX(game::StartEventLoop(config), EXIT_FAILURE)
			<< "Can't start game event loop";
	}
	catch (...)
	{
		ERROR_RETURN(EXIT_FAILURE) << " :An undefined error has occurred";
	}
}
