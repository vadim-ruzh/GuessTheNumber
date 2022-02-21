#include "game.h"

namespace game
{

results::ResultCode StartEventLoop(game::Configuration& config)
{
	while (true)
	{
		std::vector<int32_t> decisions(config.numberOfDigits);
		std::vector<int32_t> userResponses(config.numberOfDigits);

		ERROR_RETURN(game::FillVectorUniqueValuesFromRangeAtRandom(
			decisions.begin(), decisions.end(),
			config.startRangeOfInitialValues, config.endRangeOfInitialValues));

		std::cout << "You have to guess the number of " << config.numberOfDigits << " non - repeating digits\n";
		std::cout << "to win, you need to enter " << config.numberOfDigits << " correct numbers\n\n";

		int32_t correctNumbers = 0;
		int32_t attempts = config.numberOfAttempts;

		while (correctNumbers != config.needCorrectNumbers && attempts > 0)
		{
			int32_t almostCorrectNumbers = 0;
			correctNumbers = 0;

			std::cout << "Enter " << config.numberOfDigits << " digits: ";

			if (game::enterNumberIntoVector(userResponses.begin(), userResponses.end()))
			{
				std::cout << "\n\nTry entering the value again\n";
				continue;
			}

			ERROR_RETURN(game::compareVectors(decisions.begin(), decisions.end(),
				userResponses.begin(), userResponses.end(),
				correctNumbers, almostCorrectNumbers));

			std::cout << "\nCorrect numbers = " << correctNumbers << "; ";
			std::cout << "Almost correct numbers = " << almostCorrectNumbers << ".\n";

			attempts--;
			std::cout << "You have " << attempts << " attempts left\n\n";
		}


		if (correctNumbers == config.needCorrectNumbers)
		{
			std::copy(decisions.begin(), decisions.end(), std::ostream_iterator<int32_t>(std::cout, " "));
			std::cout << "Congratulations you have won !!!\n";
		}
		else
		{
			std::cout << "All attempts ended :(\n";
		}

		//Предложение пользователю сыграть еще раз 
		std::cout << "\nIf you want to play again, press 1,if you want to exit the game , press any other button:";
		bool startAgain = true;
		std::cin >> startAgain;
		ERROR_RETURN_EX(std::cin || !startAgain, results::eInvalidUserInput);

		std::cout << "\n";
	}
}

}
