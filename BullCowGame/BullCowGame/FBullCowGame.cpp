#pragma once
#include "FBullCowGame.h"
#include "pch.h"
#include <map>
#define TMap std::map

using int32 = int;
 
FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3 ,4}, {4 ,7}, {5,10}, {6,15} , {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{   //if the guess isn't an isogram, return an error
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) 
	{	//if the guess isn't all lowercase, return error
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) 
	{	//if the guess length is wrong, return error
		return EGuessStatus::Wrong_Length;
	}
	else
	{	//otherwise return ok
		return EGuessStatus::OK;
	}
}

//recieves a VALID guess, increments try, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	// setup a return variable
	FBullCowCount BullCowCount;
	// loop through all letters in the guess
	for (int32 i = 0; i < MyHiddenWord.length(); i++) 
	{	// compare letters against the hidden word
		for (int32 j = 0; j < MyHiddenWord.length(); j++) 
		{
			if (Guess[i] == MyHiddenWord[j]) 
			{
				if (i == j) {
					BullCowCount.Bulls++; //incriment bulls
				}
				else { BullCowCount.Cows++; } //incriment cows 
			}

		}
	}
	if (BullCowCount.Bulls == GetHiddenWordLength()) {
		bGameIsWon = true;
	}
	else { bGameIsWon = false; }

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen; //setup our map
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case;
		if (LetterSeen[Letter])	{ 
			return false; //We do NOT have an isogram
		}else {
			LetterSeen[Letter] = true;
		}
	}
	return true; //for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	if (Word.length() < 1) { return true; }

	for (auto Letter : Word) 
	{		
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

//HIDDENT_WORD MUST be an isogram
bool FBullCowGame::SetWordLength(int32 Number)
{
	if (Number == 3) {
		const FString HIDDEN_WORD = "not";
		MyHiddenWord = HIDDEN_WORD;
		return true;
	}else if (Number == 4) {
		const FString HIDDEN_WORD = "also";
		MyHiddenWord = HIDDEN_WORD;
		return true;
	}else if (Number == 5) {
		const FString HIDDEN_WORD = "slime";
		MyHiddenWord = HIDDEN_WORD;
		return true;
	}else if (Number == 6) {
		const FString HIDDEN_WORD = "planet";
		MyHiddenWord = HIDDEN_WORD;
		return true;
	}else if (Number == 7) {
		const FString HIDDEN_WORD = "authors";
		MyHiddenWord = HIDDEN_WORD;
		return true;
	}
	std::cout << "Please enter a valid number [3,4,5,6,7] : ";
	return false;
}

