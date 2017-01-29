/* This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();
//int32 HCHiddenOrHidden();

FBullCowGame BCGame; // instatiate a new game, which we re-use across plays

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
	std::cout << "\n\nDobrodosli u kupusice i rodice!\n\n";
	std::cout << "                                                                                                    " << std::endl;
	std::cout << "                                                                       .+////+/                     " << std::endl;
	std::cout << "                                                                       y`     +/                    " << std::endl;
	std::cout << "                                                                    `-:so`     :s`                  " << std::endl;
	std::cout << "                                                               `-//+:-``-:   ```./+:`               " << std::endl;
	std::cout << "                                                             `/+.`          `ys:////s+              " << std::endl;
	std::cout << "                  -:  `-::::::.                             -o.              `+/  `.:sy-            " << std::endl;
	std::cout << "                 +/h/+:-`````./+.  `--                     .y`                 y      `::           " << std::endl;
	std::cout << "              :/+/ ss`         `/+.:///                    s-                  y                    " << std::endl;
	std::cout << "            `s-o+   -o:     `.--:so+: y`                  `y                  .s                    " << std::endl;
	std::cout << "            +:  o:`  `://:///:..-ds.  yo`                 `y                ./+`                    " << std::endl;
	std::cout << "           /s//:.-//----+y:`    +/    y+/                  y`            ./+:.                      " << std::endl;
	std::cout << "           /+ `-+/.`..oo-.     -o    :o:+                  s+         .:+/.                         " << std::endl;
	std::cout << "            s-   .//.-s        y`  `:+ s-                  oy      .//+y`                           " << std::endl;
	std::cout << "            `o/    .+y-      -+: `-+- -s                   oy   ..-d+-s`                            " << std::endl;
	std::cout << "              /+`    +:   `/ss///:- `/+`                 .+/.-:/o+ yhy.                             " << std::endl;
	std::cout << "               -///-.++:/o//:-.`.-://-                  :s-:o/. .sso:.o-                            " << std::endl;
	std::cout << "                  `.-o+:-//////::-.                     .--.     `s    /+`                          " << std::endl;
	std::cout << "                                                                 `s`    -o`                         " << std::endl;
	std::cout << "                                                                 `s:+    .y`                        " << std::endl;
	std::cout << "                                                                `.y`y.    /y//.``                   " << std::endl;
	std::cout << "                                                                .:+oyd/` .ohoo/ss-                  " << std::endl;
	std::cout << "                                                                    `+ss/   .-- -:                  " << std::endl;
	std::cout << "                                                                                                    " << std::endl;
	std::cout << "                                                                                                    " << std::endl << std::endl;
	std::cout << "Ovo je igra pogadjanja reci!\n" << std::endl;
	std::cout << "Nakon sto unesete pokusaj, na ekranu ce se ispisati broj kupusa i broj roda.\nBroj kupusa oznacava kolicinu tacnih slova na tacnim pozicijama u reci,\na broj roda oznacava broj tacnih slova, ali na losim pozicijama.\n\n";
	std::cout << "Pravila:\nUneta rec mora biti izmedju 3 i 7 slova dugacka.\nSva slova moraju biti mala.\nRec je isogram, sto znaci da nema ponovljenih slova.\n\n";
	std::cout << "Da li mozete da pogodite rec od " << BCGame.GetHiddenWordLength() << " slova u " << BCGame.GetMaxTries() << " pokusaja?\n" << std::endl;

	return;
}

// play a single game to completion
void PlayGame()
{
	BCGame.Reset();
	/*std::cout << "Da li zelite da neko unese rec koju cete pogadjati? (y/n)\n";
	FText Answer = "";
	std::getline(std::cin, Answer);
	if (Answer == "n" || Answer == "N")
	{
		std::cout << "Da li mozete da pogodite rec od " << BCGame.GetHCHiddenWordLength() << " slova u " << BCGame.GetMaxTries() << " pokusaja?\n" << std::endl;
	}
	else if (Answer == "y" || Answer == "Y")
	{
		std::cout << "Neka neko unese rec izmedju 3 i 7 slova po pravilima napisanim iznad: \n";
		std::cin >> BCGame.MyHiddenWord;
		std::cout << "Da li mozete da pogodite rec od " << BCGame.GetHiddenWordLength() << " slova u " << BCGame.GetMaxTries() << " pokusaja?\n" << std::endl;
	}
	else
	{
		std::cout << "Niste odgovorili na pitanje.";
		BCGame.Reset();
	}*/
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
		std::cout << "Pokusaj " << CurrentTry << " od " << BCGame.GetMaxTries();
		std::cout << ". Ukucajte rec: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Ukucajte rec od " << BCGame.GetHiddenWordLength() << " slova. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Ukucajte rec u kojoj se slova ne ponavljaju. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Ukucajte rec koja ima samo mala slova. \n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

/*int32 HCHiddenOrHidden()
{
	if (BCGame.GetHiddenWordLength() < 3)
	{
		return BCGame.GetHCHiddenWordLength();
	}
	else
	{
		return BCGame.GetHiddenWordLength();
	}
}*/

bool AskToPlayAgain()
{
	std::cout << "Da li zelite da igrate ponovo sa istom recju? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
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
