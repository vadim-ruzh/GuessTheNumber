#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/regex.hpp>
#include "game_config.h"
#include "error_processing.h"


namespace conf
{
	inline  ResultCode  GetConfigFromPtree(boost::property_tree::ptree& configPtree, Configuration& config)
	{
		Configuration localResult;

		try
		{
			localResult.numberOfAttempts = configPtree.get<int>("Config.numberOfAttempts");
			localResult.startRangeOfInitialValues = configPtree.get<int>("Config.startRangeOfInitialValues");
			localResult.endRangeOfInitialValues = configPtree.get<int>("Config.endRangeOfInitialValues");
			localResult.numberOfDigits = configPtree.get<int>("Config.numberOfDigits");
			localResult.needCorrectNumbers = configPtree.get<int>("Config.needCorrectNumbers");
		}
		catch (boost::exception const& e)
		{
			ERROR_RETURN(eBadConfiguration) << ":" << dynamic_cast<std::exception const&>(e).what();
		}

		config = localResult;

		return sOk;
	}

	inline ResultCode GetConfigIni(std::istream& configFile,Configuration &configStructure)
	{
		boost::property_tree::ptree config;

		try
		{
			boost::property_tree::read_ini(configFile, config);
		}
		catch (boost::exception const& e)
		{
			ERROR_RETURN(eBadConfiguration) << ":" << dynamic_cast<std::exception const&>(e).what();
		}

		IF_RETURN(GetConfigFromPtree(config, configStructure));

		return sOk;
	}

	inline ResultCode GetConfigXml(std::istream& configFile, Configuration& configStructure)
	{
		boost::property_tree::ptree config;

		try
		{
			boost::property_tree::read_xml(configFile, config);
		}
		catch(boost::exception const& e)
		{
			ERROR_RETURN(eBadConfiguration) << ":" << dynamic_cast<std::exception const&>(e).what();
		}

		IF_RETURN(GetConfigFromPtree(config, configStructure));

		return sOk;
	}


	 
	inline ResultCode ReadTenge(std::istream& StreamConfig, boost::property_tree::ptree& configPtree)
	{
		if (!StreamConfig)
		{
			ERROR_RETURN(eFileReadingError) << " Error reading from configuration file";
		}

		std::string FileInLine;
		std::ostringstream tmpStr;
		tmpStr << StreamConfig.rdbuf();
		FileInLine = tmpStr.str();

		boost::property_tree::ptree localPtree;

		boost::regex xRegex(R"((\$\((?<KEY>[^$]+)\)\s*?=\s*?((?<DOUBLE>\d+\.\d+)|(?<INTEGER>\d+)|\"(?<STRING>[\w\s\D]*?)\")))");
		boost::sregex_iterator xIter(FileInLine.begin(), FileInLine.end(), xRegex);
		for (boost::sregex_iterator invdIt; xIter != invdIt; ++xIter)
		{
			auto matchIt = *xIter;
			std::string varName = matchIt["KEY"];

			if (matchIt["INTEGER"].matched)
			{
				localPtree.add(varName, stoi(matchIt["INTEGER"]));
				continue;
			}
			if (matchIt["DOUBLE"].matched)
			{
				localPtree.add(varName, stod(matchIt["DOUBLE"]));
				continue;
			}
			localPtree.add(varName, matchIt["STRING"]);
		}
		
		if (localPtree.empty())
		{
			ERROR_RETURN(eEmptyConfiguration) << " The file does not contain a configuration";
		}
		
		configPtree.swap(localPtree);

		return sOk;
	}

	inline ResultCode GetConfigFromTenge(std::istream& configFile, Configuration& configStructure)
	{
		boost::property_tree::ptree config;

		IF_RETURN(ReadTenge(configFile, config));
		
		IF_RETURN(GetConfigFromPtree(config, configStructure));

		return sOk;
	}

} //namespace conf
