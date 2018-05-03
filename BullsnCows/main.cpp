/*
This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user interaction
For game logic see the FBullCowGame class
Initial Commit
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;



void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; //Instantiate (create an instance of) a new game






int main()
{
	bool wantsToPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		wantsToPlayAgain = AskToPlayAgain();
	} while (wantsToPlayAgain);
	//TODO make a game summary
	std::cout << std::endl;

	return 0;

}
	
	



void PrintIntro()
{
	//Introduce the game
	int32 WORD_LENGTH = BCGame.GetHiddenWordLength();

	std::cout << "\n\nWelcome to Bulls and Cows, a fun word guessing game!\n";
	std::cout << "Can you guess the " << WORD_LENGTH;
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

//loop continually until user gives a valid guess
FText GetValidGuess() 
{
	EGuessStatus status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {
		// get a guess from the player
		int32 currentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << currentTry << ". Enter your guess: ";
		
		std::getline(std::cin, Guess);

		status = BCGame.CheckGuessValidity(Guess);
		switch (status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use only lowercase.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Your guess is not an isogram (a word with no repeating letters).\n";
			break;
		default:
			// assume the guess is valid
			return Guess;

		} 
		std::cout << std::endl;

	} while (status != EGuessStatus::OK);

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y / n)";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PlayGame()
{
	BCGame.Reset();
	
	int32 maxTries = BCGame.GetMaxTries();
	
	//Loop asking for guesses while the game is NOT won and there are still tries remaining
	//TODO change from for to while loop
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= maxTries)
	{
		FText Guess = GetValidGuess(); //TODO make loop checking valid guess

		//Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		//Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.bulls;
		std::cout << ". Cows = " << BullCowCount.cows << "\n\n";

		std::cout << "Your guess is: " << Guess << std::endl;
		std::cout << std::endl;
	}
}

