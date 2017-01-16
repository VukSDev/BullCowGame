#include <iostream>
#include <string>
#include "FBullCowGame.h"

void PrintIntro();
void PlayGame();
std::string GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instatiate a new game

// entry point for the application
int main()
{
	std::cout << BCGame.GetCurrentTry();
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0; // exit the application
}

// introduce the game
void PrintIntro()
{
	constexpr int WORD_LENGTH = 9;
	std::cout << "Welcome to Bulls and Cows!\n\n" << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?\n" << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int MaxTries = BCGame.GetMaxTries();
	
	// loop for the number of turns asking for guesses
	// TODO change from FOR to WHILE loop once we are validating tries
	for (int i = 1; i <= MaxTries; i++)
	{
		std::string Guess = GetGuess(); //TODO make loop checking valid

		// pubmit valid guess the game
		// print number of bulls and cows

		std::cout << "Your guess is: " << Guess << std::endl;
		std::cout << std::endl;
	}
	// TODO summarize game
}

// get a guess from the player and print the guess back to them
std::string GetGuess()
{
	int CurrentTry = BCGame.GetCurrentTry();
	// get a guess from the player
	std::cout << "Try " << CurrentTry << ". Enter your guess: ";
	std::string Guess = "";
	std::getline(std::cin, Guess);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n)";
	std::string Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');;
	std::cout << std::endl;
}