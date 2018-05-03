#pragma once
#include <string>
//initial commit

using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 bulls = 0;
	int32 cows = 0;

};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase

};



class FBullCowGame 
{

public:
	FBullCowGame(); //Constructor

	void Reset(); //TODO make a more rich return value
	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString Guess) const;
	
	FBullCowCount SubmitValidGuess(FString);



private:
	//See constructor for initialization
	int32 myCurrentTry;
	int32 myMaxTries;

	FString myHiddenWord;

	bool bGameIsWon;
	
};
