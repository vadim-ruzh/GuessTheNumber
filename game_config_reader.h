#pragma once
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "game_config.h"

namespace game
{

inline Configuration GetConfig(std::ifstream& configFile)
{
	Configuration result;

	boost::property_tree::ptree config;
	read_ini(configFile, config);

	result.numberOfAttempts = config.get<int>("Config.numberOfAttempts");
	result.startRangeOfInitialValues = config.get<int>("Config.startRangeOfInitialValues");
	result.endRangeOfInitialValues = config.get<int>("Config.endRangeOfInitialValues");
	result.numberOfDigits = config.get<int>("Config.numberOfDigits");
	result.needCorrectNumbers = config.get<int>("Config.needCorrectNumbers");

	return result;
}

}
