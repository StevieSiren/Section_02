#include "FBullCowGame.h"
#include <map>
#define TMap std::map


FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	myCurrentTry = 1;
	myMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "donkey";
	myHiddenWord = HIDDEN_WORD;

	bGameIsWon = false;
	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	return myMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const
{
	return myCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{

	return myHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{

	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if the guess isn't an isogram
	if (!IsIsogram(Guess)) 
	{
		return EGuessStatus::Not_Isogram;
	}
	// if the guess isn't all lowercase
	else if (!IsLowercase(Guess)) 
	{
		return EGuessStatus::Not_Lowercase;
	}
	// if the guess length is wrong
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else 
	{
		return EGuessStatus::OK;
	}

}

// Receives a valid guess; increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	// increment the turn number
	myCurrentTry++;

		// setup a return value
		FBullCowCount BullCowCount;

	// loop through all letters in the guess
		int32 hiddenWordLength = myHiddenWord.length();
		for (int32 MHWChar = 0; MHWChar < hiddenWordLength; MHWChar++)
		{
			// compare letters against the hidden word

			for (int32 GChar = 0; GChar < hiddenWordLength; GChar++)
			{
				// if they match
				if (Guess[GChar] == myHiddenWord[MHWChar]) 
				{
					// if they're in the same place
					if (MHWChar == GChar) 
					{
						//increment bulls
						BullCowCount.bulls++;
					}
					else 
					{
						//increment cows
						BullCowCount.cows++;
					}

				}

			}
		}
	
		if (BullCowCount.bulls == hiddenWordLength)
		{
			bGameIsWon = true;
		}
		else 
		{
			bGameIsWon = false;
		}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString word) const
{
	// treat 0 and 1 letter words as isograms
	if (word.length() <= 1) 
	{
		return true;
	}

	TMap<char, bool> letterSeen;
	for (auto letter : word) 
	{
		letter = tolower(letter); // handle mixed case
		if (letterSeen[letter]) 
		{
			return false; // we do NOT have an isogram
		}
		else 
		{
			letterSeen[letter] = true;
		}
	}
	
	return true;
}

bool FBullCowGame::IsLowercase(FString word) const
{
	for (auto letter : word) 
	{
		
		if (!islower(letter)) 
		{
			return false;
		}
		
	}
	
	return true;
}


