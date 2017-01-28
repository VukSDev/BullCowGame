/* This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instatiate a new game

// entry point for the application
int main()
{
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
	std::cout << "\n\nDobrodosli u kupusice i rodice!\n\n" << "Nakon sto unesete rec na ekranu ce se ispisati broj kupusa i broj roda.\nBroj kupusa oznacava kolicinu tacnih slova na tacnim pozicijama u reci,\na broj roda oznacava broj tacnih slova, ali na losim pozicijama.\n\n" << "Da li mozete da pogodite rec od " << BCGame.GetHiddenWordLength() << " slova koju sam zamislio u " << BCGame.GetMaxTries() << " pokusaja?\n" << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop for the number of turns asking for guesses while the game
	// is NOT won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Kupusi = " << BullCowCount.Bulls;
		std::cout << ". Rode = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Pokusaj " << CurrentTry << ". Ukucajte rec: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Ukucajte rec od " << BCGame.GetHiddenWordLength() << " slova. \n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Ukucajte rec u kojoj se slova ne ponavljaju. \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Ukucajte rec koja ima samo mala slova. \n";
			break;
		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');;
	std::cout << std::endl;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon() == true)
	{
		std::cout << "POBEDA!\n\n";
	}
	else 
	{
		std::cout << "Izgubili ste, vise srece sledeci put!\n\n";
	}
}