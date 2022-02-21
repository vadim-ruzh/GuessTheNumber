#define BOOST_TEST_MODULE GameTests
#include <boost/test/included/unit_test.hpp>

#include "../1/game.h"
#include "../1/game_config_reader.h"

// https://regex101.com/r/hL8tJ7/1
// boost::regex \$\(.\)\ \= ()
// ONLY INTS
/*
 $(Config.numberOfAttempts) = 4
 $(Config.startRangeOfInitialValues) = 10
*/

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

	for(auto& elem : dst)
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
		auto cfg = game::GetConfigIni(configFile);
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
		auto cfg = game::GetConfigXml(configFile);
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
		auto cfg = game::GetConfigXml(configFile);
		BOOST_TEST(false);
	}
	catch (const std::exception&)
	{
		BOOST_TEST(true);
	}
}