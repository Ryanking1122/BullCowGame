#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame;


int main() 
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;
}



void PrintIntro() 
{ 
	//Introduce the game
	std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
	std::cout << "|||                                                               |||" << std::endl;
	std::cout << "|||                                                               |||" << std::endl;
	std::cout << "|||                                                               |||" << std::endl;
	std::cout << "|||                                                               |||" << std::endl;
	std::cout << "|||        Welcome to the Bulls and Cows. A fun word game.        |||" << std::endl;
	std::cout << "|||      Can you guess the " << BCGame.GetHiddenWordLength(); std::cout << " letter isogram I am thinking of?     |||" << std::endl;
	std::cout << "|||                                                               |||" << std::endl;
	std::cout << "|||      A Bull is how many letters you have in the correct space |||" << std::endl;
	std::cout << "|||      A Cow is a correct letter but in the wrong position      |||" << std::endl;
	std::cout << "|||                                                               |||" << std::endl;
	std::cout << "|||                                                               |||" << std::endl;
	std::cout << "|||                                                               |||" << std::endl;
	std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//For Loop for ammount of guesses
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() < MaxTries)
	{
		FText Guess = GetValidGuess();
		// submit valid guess to the game, and receives counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// Print number of Bulls and Cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
	}
	PrintGameSummary();
}

FText GetValidGuess() 
{ 
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
		do {
			int32 CurrentTry = BCGame.GetCurrentTry();
			std::cout << std::endl;
			//Gets the player's guess
			std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
			std::cout <<". Enter your guess?: ";
			getline(std::cin, Guess);
			Status = BCGame.CheckGuessValidity(Guess);
			switch (Status)
			{
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter isogram.\n";
				break;
			case EGuessStatus::Not_Isogram:
				std::cout << "Please enter a word without repeating letters.\n";
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "Please enter in all lower case letters.\n";
				break;
			default:
				break;
			}
		} while (Status != EGuessStatus::OK); //Keep looping until valid guess
		return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations, You have won!!!!\n\n";
	}
	else
	{
		std::cout << "You Lose. Better luck next time\n\n";
	}
}

bool AskToPlayAgain() 
{
	std::cout << "\nDo You want to play again with the same hidden word? (y/n): ";
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
	std::cout << std::endl;
}