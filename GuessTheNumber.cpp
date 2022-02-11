#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <algorithm>


bool fillRandomVector(std::vector<int>::iterator vect1Begin, std::vector<int>::iterator vect1End, std::vector<int>::iterator vect2Begin, std::vector<int>::iterator vect2End)
{
    if ((vect1End - vect1Begin) >= (vect2End - vect2Begin))
    {
    	std::random_shuffle(vect1Begin, vect1End);


        std::vector<int>::iterator It1 = vect1Begin;
        std::vector<int>::iterator It2 = vect2Begin;

        while(It2 != vect2End)
        {
            *It2 = *It1;
            It1++;
            It2++;
        }


		return true;
    }
    else
    {
        return false;
    }

}

bool comparingVector(std::vector<int>::iterator vect1Begin, std::vector<int>::iterator vect1End, std::vector<int>::iterator vect2Begin, std::vector<int>::iterator vect2End, short int& correctly, short int& closely)
{
    if((vect1End - vect1Begin) == (vect2End - vect2Begin))
    {
        std::vector<int>::iterator It1 = vect1Begin;

        while(It1 != vect1End)
        {
            std::vector<int>::iterator It2 = vect2Begin;

            if (*It1 == *(It2 + (It1-vect1Begin)))
            {
                correctly += 1;
            }

            else
            {
	            while (It2 != vect2End)
	            {
                    if (*It1 == *It2) {
                        closely += 1;
                        break;
                    }

                    It2++;
	            }
            }

            It1++;
        }

        return true;
    }
    else
    {
        return  false;
    }

   



	
}

bool enteringNumberInVector(std::vector<int>::reverse_iterator begin, std::vector<int>::reverse_iterator end)
{
    std::string str;
    std::cin >> str;

    if (str.length() == end - begin)
    {
        int number;

        try 
        {
            number = std::stoi(str);
        }
        catch (std::invalid_argument) 
        {
            return false;
        }

        for (std::vector<int>::reverse_iterator It = begin; It != end; It++)
        {
            *It = number % 10;
            number = number / 10;
        }

        return true;
    }

    else
    {
        return false;
    }


}

void outputVectorToConsole(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	for(std::vector<int>::iterator It = begin;It < end;++It)
	{
        std::cout << *It << " ";
	}
}

/*
int main()
{  
    const int lenght = 4;
    int decisions[lenght];
    int anwsers[lenght];

    const int lenght_alphabet = 10;
    int alphabet[lenght_alphabet] = { 0,1,2,3,4,5,6,7,8,9 };

    bool play = 1;

    srand(time(NULL));
    RandomFilling(decisions,alphabet,lenght, lenght_alphabet);

    while (play) {
        short int correct = 0;
        short int attempts = 10;

        std::cout << "You have to guess the number of 4 non - repeating digits\n" << std::endl;

        while (correct != 4 && attempts > 0) {
            short int close = 0;
            correct = 0;

            std::cout << "Enter 4 digits: ";
            if (InputDigits(anwsers)) {
                ComparingArrays(decisions, anwsers, correct, close);

                std::cout << "\nCorrectly = " << correct << "; ";
                std::cout << "Closely = " << close << "." << std::endl;
                attempts--;
                std::cout << "You have " << attempts << " attempts left\n" << std::endl;

            }


            else {
                std::cout << "\nWrong number!!!\n" << std::endl;
                continue;
            }
        }

        if (correct == 4) {
            OutputArray(decisions, lenght);
            std::cout << "Congratulations you have won !!!" << std::endl;
        }
        else
            std::cout << "All attempts ended :(" << std::endl;

        std::cout << "\nIf you want to exit the game, press 0, if you want to play again, press any other number:";
        std::cin >> play;
        std::cout << std::endl;
    }
    
}
*/

int main()
{
    std::vector<int> alphabet = { 0,1,2,3,4,5,6,7,8,9 };
    std::vector<int> anwsers(4);
    std::vector<int> playing(4);

    bool play = 1;

    srand(time(NULL));

    fillRandomVector(alphabet.begin(), alphabet.end(), anwsers.begin(), anwsers.end());

    while (play) {

        short int correct = 0;
        short int attempts = 10;

        std::cout << "You have to guess the number of 4 non - repeating digits\n" << std::endl;

        while (correct != 4 && attempts > 0) {
            short int close = 0;
            correct = 0;

            std::cout << "Enter 4 digits: ";
            if (enteringNumberInVector(playing.rbegin(),playing.rend())) 
            {
                comparingVector(anwsers.begin(), anwsers.end(), playing.begin(), playing.end(), correct, close);

                std::cout << "\nCorrectly = " << correct << "; ";
                std::cout << "Closely = " << close << "." << std::endl;
                attempts--;
                std::cout << "You have " << attempts << " attempts left\n" << std::endl;

            }


            else {
                std::cout << "\nWrong number!!!\n" << std::endl;
                continue;
            }
        }

        if (correct == 4) {
            outputVectorToConsole(anwsers.begin(),anwsers.end());
            std::cout << "Congratulations you have won !!!" << std::endl;
        }
        else
            std::cout << "All attempts ended :(" << std::endl;

        std::cout << "\nIf you want to exit the game, press 0, if you want to play again, press any other number:";
        std::cin >> play;
        std::cout << std::endl;
    }



}
