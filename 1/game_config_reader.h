#pragma once
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "game_config.h"

namespace game
{

inline Configuration GetConfigFromPtree(boost::property_tree::ptree& config)
{
	Configuration result;

	result.numberOfAttempts = config.get<int>("Config.numberOfAttempts");
	result.startRangeOfInitialValues = config.get<int>("Config.startRangeOfInitialValues");
	result.endRangeOfInitialValues = config.get<int>("Config.endRangeOfInitialValues");
	result.numberOfDigits = config.get<int>("Config.numberOfDigits");
	result.needCorrectNumbers = config.get<int>("Config.needCorrectNumbers");

	return result;
}

inline Configuration GetConfigIni(std::istream& configFile)
{
	boost::property_tree::ptree config;
	read_ini(configFile, config);

	return GetConfigFromPtree(config);
}

inline Configuration GetConfigXml(std::istream& configFile)
{
	boost::property_tree::ptree config;
	read_xml(configFile, config);

	return GetConfigFromPtree(config);
}

}
