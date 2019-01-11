// BullCowGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*This is the console executable, that makes use of BullCow class
This acts as the view in a MVC pattern, and is responsible for all user interaction. For game logic, see the FBUllCowGame Class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include "pch.h"

//to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

//function prototypes as outside a class
FText GetValidGuess();
bool AskToPlayAgain();
void PrintIntro();
void PlayGame();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game, which we re-use across plays

//the entry point for our application
int32 main()
{
	do 
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
	return 0;
}

void PrintIntro()
{
	//introduce the game
	FText WordLength = "";
	std::cout << std::endl;
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";

	std::cout << "How many Letters would you like the isogram to be? [3,4,5,6,7] : ";
	do {
		std::getline(std::cin, WordLength);
	} while (!BCGame.SetWordLength(std::atoi(WordLength.c_str())));
	std::cout << "\n\n";

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of ?\n";
	std::cout << std::endl;
	return;
}

//plays a single game to completion
void PlayGame()
{
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();
	//loop for the number of turns asking for guesses while the game is NOT won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) 
	{
		FText Guess = GetValidGuess(); 

		//Submit valid guess to the game, and recieve count
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
		std::cout << "You won the game! Congratulation\n";
	else
	{
		std::cout << "You lost, good luck next time!\n";
	}
	return;
}

FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of "<< BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter lowercases letters only. \n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);

	return Guess;
}


bool AskToPlayAgain() 
{
	std::cout << "Do you want to play again ? [y/n] \n";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file