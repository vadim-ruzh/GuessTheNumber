#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/regex.hpp>
#include "game_config.h"
#include "error_processing.h"


namespace conf
{
	/**
	 * \brief Извлечение определенных переменных из configPtree и помещение их в dstConfig
	 * \param configPtree ptree содержащий в себе конфигурацию  
	 * \param dstConfig Структура конфигурации 
	 * \return resultCode Код результата работы функции 
	 */
	inline  resultCode  GetConfigFromPtree(boost::property_tree::ptree& configPtree, Configuration& dstConfig)
	{
		Configuration localConfig;

		try
		{
			localConfig.numberOfAttempts = configPtree.get<int>("Config.numberOfAttempts");
			localConfig.startRangeOfInitialValues = configPtree.get<int>("Config.startRangeOfInitialValues");
			localConfig.endRangeOfInitialValues = configPtree.get<int>("Config.endRangeOfInitialValues");
			localConfig.numberOfDigits = configPtree.get<int>("Config.numberOfDigits");
			localConfig.needCorrectNumbers = configPtree.get<int>("Config.needCorrectNumbers");
		}
		catch (boost::exception const& e)
		{
			ERROR_RETURN(eBadConfiguration) << ":" << dynamic_cast<std::exception const&>(e).what();
		}

		dstConfig = localConfig;

		return sOk;
	}

	inline resultCode GetConfigIni(std::istream& configFile,Configuration &configStructure)
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

	inline resultCode GetConfigXml(std::istream& configFile, Configuration& configStructure)
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

	/**
	 * @brief Чтение информации из входного потока в ptree,по заданному формату
	 * @param inputStream Поток ввода 
	 * @param  dstPtree Ptree назначения 
	 * @return resultCode Код результата работы функции 
	 */
	inline resultCode ReadTenge(std::istream& inputStream, boost::property_tree::ptree& dstPtree)
	{
		if (!inputStream)
		{
			ERROR_RETURN(eFileReadingError) << " Error reading from configuration file";
		}

		std::string FileInLine;
		std::ostringstream tmpStr;
		tmpStr << inputStream.rdbuf();
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
		
		dstPtree.swap(localPtree);

		return sOk;
	}

	/**
	 * @brief Чтение  данных из входного потока и помещение в конфигурационную структуру 
	 * @param  inputStream Поток ввода 
	 * @param  dstConfig Cтруктура конфигурации 
	 * @return resultCode Код результата работы функции 
	 */
	inline resultCode GetConfigFromTenge(std::istream& inputStream, Configuration& dstConfig)
	{
		boost::property_tree::ptree configPtree;

		IF_RETURN(ReadTenge(inputStream, configPtree));
		
		IF_RETURN(GetConfigFromPtree(configPtree, dstConfig));

		return sOk;
	}

} //namespace conf
