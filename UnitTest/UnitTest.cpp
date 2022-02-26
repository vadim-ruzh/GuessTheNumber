
#define BOOST_TEST_MODULE GameTests

#include <boost/test/included/unit_test.hpp>
#include "../Game/game.h"
#include "../Game/game_config_reader.h"
#include "../Game/game_config.h"

BOOST_AUTO_TEST_CASE(TestFillingHappyPath)
{
	const int start = 1,
		end = 10,
		elementsCount = end - start;

	std::vector<int32_t> dst;
	dst.resize(elementsCount);

	auto result = game::FillVectorUniqueValuesFromRangeAtRandom(
		dst.begin(), dst.end(),
		start, end
	);

	BOOST_TEST(result == game::results::sOk);
	BOOST_TEST(dst.size() == elementsCount);

	for (auto& elem : dst)
	{
		BOOST_TEST((elem <= end && elem >= start));
	}
}

BOOST_AUTO_TEST_CASE(EndRangeLargerThenStartError)
{
	std::vector<int32_t> dst;
	dst.resize(10);

	auto result = game::FillVectorUniqueValuesFromRangeAtRandom(
		dst.begin(), dst.end(),
		0, -10
	);

	BOOST_TEST(result);
}

BOOST_AUTO_TEST_CASE(ReadingConfigFromIniSuccess)
{
	auto config = R"(
		[Config]
		numberOfAttempts = 10
		startRangeOfInitialValues = 0
		endRangeOfInitialValues = 9
		numberOfDigits = 4
		needCorrectNumbers = 4
	)";

	std::stringstream configFile(config);

	try
	{

		conf::Configuration cnfg;

		conf::GetConfigIni(configFile, cnfg);
		BOOST_TEST(true);
	}
	catch (const std::exception&)
	{
		BOOST_TEST(false);
	}
}

BOOST_AUTO_TEST_CASE(ReadingConfigFromXmlSuccess)
{
	auto config = R"(
		<Config>
			<numberOfAttempts>10</numberOfAttempts>
			<startRangeOfInitialValues>10</startRangeOfInitialValues>
			<endRangeOfInitialValues>10</endRangeOfInitialValues>
			<numberOfDigits>10</numberOfDigits>
			<needCorrectNumbers>10</needCorrectNumbers>
		</Config>
	)";

	std::stringstream configFile(config);

	try
	{
		conf::Configuration cnfg;
		conf::GetConfigXml(configFile, cnfg);
		BOOST_TEST(true);
	}
	catch (const std::exception&)
	{
		BOOST_TEST(false);
	}
}

BOOST_AUTO_TEST_CASE(ReadingConfigFromXmlWoNumberOfAttempts)
{
	auto config = R"(
		<Config>
			<startRangeOfInitialValues>10</startRangeOfInitialValues>
			<endRangeOfInitialValues>10</endRangeOfInitialValues>
			<numberOfDigits>10</numberOfDigits>
			<needCorrectNumbers>10</needCorrectNumbers>
		</Config>
	)";

	std::stringstream configFile(config);

	try
	{
		conf::Configuration cnfg;

		conf::GetConfigXml(configFile,cnfg);
		BOOST_TEST(false);
	}
	catch (const std::exception&)
	{
		BOOST_TEST(true);
	}
}

BOOST_AUTO_TEST_CASE(ReadingConfigFromTengeSuccess)
{
	auto config = R"(
		$(Config.numberOfAttempts) = 123444
		$(Config.startRangeOfInitialValues) = 23423
		$(Config.endRangeOfInitialValues) = 667655
		$(Config.numberOfDigits) = 123123
		$(Config.needCorrectNumbers) = 123333
	)";

	std::stringstream configFile(config);

	try
	{
		conf::Configuration cnfg;
		conf::GetConfigFromTenge(configFile, cnfg);

		BOOST_TEST(true);
	}
	catch (const std::exception&)
	{
		BOOST_TEST(false);
	}
}

BOOST_AUTO_TEST_CASE(ReadingConfigFromeTengeFalse)
{
	auto testConfig1 = R"(
		$(Config.numberOfAttempts) = 1232.123
		$(Config.startRangeOfInitialValues) = "asd"
		$(Config.endRangeOfInitialValues) = +_01332
		$(Config.numberOfDigits) = ads
		$(Config.needCorrectNumbers) = "123aaw3"
		)";

	auto testConfig2 = "";

	std::stringstream configFile1(testConfig1);
	std::stringstream configFile2(testConfig2);

	try
	{
		conf::Configuration cnfg1;
		conf::Configuration cnfg2;
		if(conf::GetConfigFromTenge(configFile1, cnfg1))
		{
			throw "Error";
		}
		if(conf::GetConfigFromTenge(configFile2, cnfg2))
		{
			throw "Error";
		}

		BOOST_TEST(false);
	}
	catch (const std::exception&)
	{
		BOOST_TEST(true);
	}



}