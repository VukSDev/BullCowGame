#pragma once

#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map 
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
//int32 FBullCowGame::GetHCHiddenWordLength() const { return HCHiddenWord.length(); } 
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 10}, {4, 15}, {5, 20}, {6, 25}, {7, 30} };
//	if (MyHiddenWord.length() <= 3)
//	{
//		return WordLengthToMaxTries[HCHiddenWord.length()];
//	}
//	else
//	{
		return WordLengthToMaxTries[MyHiddenWord.length()];
//	}
}

/*bool FBullCowGame::IsEnteredOrNot() const
{
	bool bIsEnteredOrNot;
	if (MyHiddenWord.length() < 3)
	{
		bIsEnteredOrNot = false;
	}
	else
	{
		bIsEnteredOrNot = true;
	}
	return bIsEnteredOrNot; 
}*/ // TODO

void FBullCowGame::Reset()
{
	//constexpr int32 MAX_TRIES = 25;
	const FString HIDDEN_WORD = "plugovi"; // this is useful if we don't want to allow another player to set the word // this MUST be an isogram
	//FString HiddenWord;
	//MyMaxTries = MAX_TRIES; // no need for this anymore since it is mapped above in the getter for max tries function
	MyHiddenWord = HIDDEN_WORD;
	//HCHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase; //TODO write function
	}
	else if (/*IsEnteredOrNot() == true && */Guess.length() != GetHiddenWordLength()) // if the guess length is wrong // here I must put a function that returns true or false depending on wether the player entered the word or not
	{
		return EGuessStatus::Wrong_Length;
	}
	/*else if (IsEnteredOrNot() == false && Guess.length() != GetHCHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}*/
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar) // if they are in the same place
				{
					BullCowCount.Bulls++; // increment bulls
				}
				else
				{
					BullCowCount.Cows++; // must be a cow
				}
					
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else 
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const 
{ 
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	// setup our map
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) { return false; }// we do not have an isogram
		else { 
			LetterSeen[Letter] = true;
		}
			// if the letters is in the map
				// we do NOT have an isogram
			// otherwise
				// add the letter to the map as seen
	}

	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
		else 
		{
			return true;
		}
	}

	return true;
}
