#pragma once

#include "FBullCowGame.h"
#include <map>

//Unreal Syntax
#define TMap std::map

FBullCowGame::FBullCowGame() //Default Constructor
{
	Reset();
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) // if guess isn't all lower case
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

//receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//increment turn count
	MyCurrentTry++;
	//setup a return variable
	FBullCowCount BullCowCount;
	//loop through all letters in the guess
	int32 WordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		//compare letters against the hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { //if they're in the same place
					//increment bulls
					BullCowCount.Bulls++;
				}
				else {
					//increment cows
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) 
	{
		bIsGameWon = true;
	}
	else 
	{
		bIsGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat zero and one letter words as isograms
	if (Word.length() <= 1)
	{
		return true;
	}

	TMap <char, bool> LetterSeen; //setup our map
	for (auto Letter : Word) //loop through all letters of word
	{
		Letter = tolower(Letter); //Sets Letter to lowercase.
		if (LetterSeen[Letter])
		{
			return false; //we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true; //add the letter to the map
		}
			
	}
	return true; //for examples in cases where /0 is entered
}

int FBullCowGame::GetMaxTries() const
{
	TMap <int32, int32> WordLengthToMaxTries{ {3,4}, {4,5}, {5,6}, {6,7}, {7,8}, {8,9}, {9,10}, {10, 11}};
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bIsGameWon;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) 
	{
		if (!islower(Letter)) 
		{
			return false;
		}
	}

	return true;
}
