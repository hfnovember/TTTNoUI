/**************************************************

					TIC TAC TOE
	Author: Nicos Kasenides (Year 2/3 BSc Computing)
	Email: nkasenides@uclan.ac.uk
	Summer Hacker Challenge 2016

/**************************************************/
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <stdio.h>
#include "Player.h";
#include "Color.h";
using namespace std;
/**************************************************/
// --- Globals ---
const int gameSize = 3;
char gameArray[gameSize][gameSize];
GameState gameState;
/**************************************************/
// --- Function Declarations ---
void PrintIntro();
void InitializeGameBoard();
void PrintGameBoard();
void PrintInstructions();
void ClearScreen();
void Exit();
void SelectCharacter(Player &player, Player &npc);
void SelectDifficulty(Difficulty &gameDifficulty);
void PlayGame(Difficulty &gameDifficulty, Player &player, Player &npc);
void RandomPlayerStart();
bool PlayerHasWon(Player &player);
bool BoardIsFilled();
bool PositionIsEmpty(int i, int j);
void MakeEasyMove(Player &npc);
void PrintEndingBoard(Player player);
void GameEndHandler(Player &player, Player &npc);
void DisplayStats(Player player, Player npc);
void PostGameHandler(Difficulty &gameDifficulty, Player player, Player npc);
void ResetGame(Difficulty gameDifficulty, Player player, Player npc);
void MakeHardMove(Player player, Player npc);
int WinnerPick(const int convertedGameBoard[9], int cSize);
int Minimax(int convertedGameBoard[9], int player, int cSize);
string GetRandomTaunt();
template <typename Number> 
inline Number GetRandomNumber(Number min, Number max) {
	return (rand() % (int)(max + 1 - min) + min);
}//end getRandomNumber()
/**************************************************/
void main() {
	//-Game Objects Init-
	Player player;
	Player npc;
	Difficulty gameDifficulty;
	//-Game Start-
	srand(time(NULL));
	ClearScreen();
	SetColor(white);
	InitializeGameBoard();
	PrintInstructions();
	SelectCharacter(player, npc);
	SelectDifficulty(gameDifficulty);
	RandomPlayerStart();
	while (gameState != ended) PlayGame(gameDifficulty, player, npc);
	if (gameState == ended) {
		GameEndHandler(player, npc); 
		PostGameHandler(gameDifficulty, player, npc);
	}//end if game ended
}//end main()
/**************************************************/
void PrintIntro() {
	PrintColored(yellow, "**************************************************\n");
	PrintColored(yellow, "               TIC TAC TOE BY NICOS               \n");
	PrintColored(yellow, "        ---------------------------------         \n");
	PrintColored(yellow, " Created by: "); PrintColored(blue, " Nicos Kasenides (Year 2)\n");
	PrintColored(yellow, " Email: "); PrintColored(blue,"nkasenides@uclan.ac.uk\n");
	PrintColored(yellow, " --- UCLan Cyprus Summer Hacker Challenge 2016 ---\n");
	PrintColored(yellow, "**************************************************\n");
	cout << endl;
}//end printIntro()
/**************************************************/
void InitializeGameBoard() {
	for (int i = 0; i < gameSize; i++) 
		for (int j = 0; j < gameSize; j++)	gameArray[i][j] = ' ';
}//end InitializeGameBoard()
/**************************************************/
void PrintGameBoard() {
	SetColor(green);
	cout << "                -----------------" << endl;
	for (int i = 0; i < gameSize; i++) {
		cout << "                ";
		for (int j = 0; j < gameSize; j++) {
			cout << "|| " << gameArray[i][j] << " ";
		}//end for
		cout << "||" << endl;
	}//end for
	cout << "                -----------------" << endl;
	cout << endl;
	SetColor(white);
}//end printGameArray()
/**************************************************/
void PrintInstructions() {
	cout << "== Instructions ==" << endl;
	cout << " Two players, X and O, take turns marking each \n";
	cout << " of their characters in the spaces in a 3x3 grid.\n";
	cout << " The player who succeeds in placing three of their\n";
	cout << " characters in a horizontal, vertical, or diagonal\n";
	cout << " row wins the game." << endl;
	cout << "--------------------------------------------------" << endl;
	system("pause");
}//end printInstructions()
/**************************************************/
void ClearScreen() {
	system("cls");
	PrintIntro();
}//end clearScreen()
/**************************************************/
void Exit() {
	system("exit");
}//end exit()
/**************************************************/
void SelectCharacter(Player &player, Player &npc) {
	ClearScreen();
	string inputString;
	PrintColored(red, "Please select a character, X or O: ");
	cin >> inputString;
	char inputChar = inputString[0];
	while (inputChar != 'x' && inputChar != 'X' && inputChar != 'o' && inputChar != 'O') {
		ClearScreen();
		PrintColored(red, "-- You done goofed! X or O only--\n");
		PrintColored(red, "Please select a character, X or O: ");
		cin >> inputString;
		inputChar = inputString[0];
	}//end while

	char playerCharacter;
	char npcCharacter;

	if (inputChar == 'x' || inputChar == 'X') {
		playerCharacter = 'X';
		npcCharacter = 'O';
	}//end if

	if (inputChar == 'o' || inputChar == 'O') {
		playerCharacter = 'O';
		npcCharacter = 'X';
	}//end if

	
	player.SetCharacter(playerCharacter);
	npc.SetCharacter(npcCharacter);

	ClearScreen();

	SetColor(blue);
	cout << "Your character: " << player.GetCharacter() << endl;
	cout << "PC character: " << npc.GetCharacter() << endl;
	cout << endl;
	SetColor(white);

	system("pause");
}//end SelectCharacter()
/**************************************************/
void SelectDifficulty(Difficulty &gameDifficulty) {
	ClearScreen();
	string inputString;
	PrintColored(red, "Please select difficulty:\n E - Easy\n H - Hard (You will never win >:] )\n\n");
	cin >> inputString;
	char difficultyInput = inputString[0];

	while (difficultyInput != 'E' && difficultyInput != 'e' && difficultyInput != 'H' && difficultyInput != 'h') {
		ClearScreen();
		PrintColored(red, "-- Are you noob? E or H only--\n");
		PrintColored(red, "Please select difficulty:\n E - Easy\n H - Hard\n\n");
		cin >> inputString;
		difficultyInput = inputString[0];
	}//end while

	string txtDifficulty;
	if (difficultyInput == 'E' || difficultyInput == 'e') {
		gameDifficulty = easy;
		txtDifficulty = "Easy";
	}//end if

	if (difficultyInput == 'H' || difficultyInput == 'h') {
		gameDifficulty = hard;
		txtDifficulty = "Hard";
	}//end if

	ClearScreen();
	SetColor(blue);
	cout << "Difficulty: " << txtDifficulty << endl;
	cout << endl;
	SetColor(white);
	system("pause");
}//end SelectDifficulty()
/**************************************************/
void RandomPlayerStart() {
	int randomTurn = rand() % 100;
	if (randomTurn % 2 == 0) gameState = npcTurn;
	else gameState = playerTurn;
}//end randomPlayerStart()
/**************************************************/
void PlayGame(Difficulty &gameDifficulty, Player &player, Player &npc) {
	ClearScreen();
	PrintColored(yellow, "  Difficulty: ");
	if (gameDifficulty == easy) PrintColored(blue, "Easy\n");
	else if (gameDifficulty == hard) PrintColored(red, "Hard\n");

	if (gameState == npcTurn) {
		if (gameDifficulty == easy) {
			MakeEasyMove(npc);
			gameState = playerTurn;
		}//end if easy mode
		else if (gameDifficulty == hard) {
			MakeHardMove(player, npc);
			gameState = playerTurn;
		}//end if hard mode
	}//end if NPC Turn
	else if (gameState == playerTurn) {
		PrintGameBoard();
		PrintColored(blue, "-- 1 is bottom left, 9  is top right -- "); PrintColored(red, "TIP: Use the numpad!"); 
		PrintColored(blue," \n Enter position to place character (or Q to exit): ");
		string inputString;
		cin >> inputString;
		char position = inputString[0];
			
		switch (position) {
		case '1':
			if (gameArray[2][0] == ' ') { gameArray[2][0] = player.GetCharacter(); gameState = npcTurn; } break;
		case '2':
			if (gameArray[2][1] == ' ') { gameArray[2][1] = player.GetCharacter(); gameState = npcTurn; } break;
		case '3':
			if (gameArray[2][2] == ' ') { gameArray[2][2] = player.GetCharacter(); gameState = npcTurn; } break;
		case '4':
			if (gameArray[1][0] == ' ') { gameArray[1][0] = player.GetCharacter(); gameState = npcTurn; } break;
		case '5':
			if (gameArray[1][1] == ' ') { gameArray[1][1] = player.GetCharacter(); gameState = npcTurn; } break;
		case '6':
			if (gameArray[1][2] == ' ') { gameArray[1][2] = player.GetCharacter(); gameState = npcTurn; } break;
		case '7':
			if (gameArray[0][0] == ' ') { gameArray[0][0] = player.GetCharacter(); gameState = npcTurn; } break;
		case '8':
			if (gameArray[0][1] == ' ') { gameArray[0][1] = player.GetCharacter(); gameState = npcTurn; } break;
		case '9':
			if (gameArray[0][2] == ' ') { gameArray[0][2] = player.GetCharacter(); gameState = npcTurn; } break;
		case 'q':
		case 'Q':
			PrintColored(red, " ==== THE RAGE!!! ===\n"); system("pause");
			gameState = ended;
			break;
		default:
			PrintColored(red, " ERROR: The position you entered is invalid. Please enter a position 1-9.");
			break;
		}//end switch
	}//end if Player's Turn
	if (PlayerHasWon(player) || PlayerHasWon(npc) || BoardIsFilled()) gameState = ended;
}//end PlayGame()
/**************************************************/
bool PlayerHasWon(Player &player) {
	//Horizontals
	if (gameArray[0][0] == player.GetCharacter() && gameArray[0][1] == player.GetCharacter() && gameArray[0][2] == player.GetCharacter()) return true;
	else if (gameArray[1][0] == player.GetCharacter() && gameArray[1][1] == player.GetCharacter() && gameArray[1][2] == player.GetCharacter()) return true;
	else if (gameArray[2][0] == player.GetCharacter() && gameArray[2][1] == player.GetCharacter() && gameArray[2][2] == player.GetCharacter()) return true;
	//Verticals
	else if (gameArray[0][0] == player.GetCharacter() && gameArray[1][0] == player.GetCharacter() && gameArray[2][0] == player.GetCharacter()) return true;
	else if (gameArray[0][1] == player.GetCharacter() && gameArray[1][1] == player.GetCharacter() && gameArray[2][1] == player.GetCharacter()) return true;
	else if (gameArray[0][2] == player.GetCharacter() && gameArray[1][2] == player.GetCharacter() && gameArray[2][2] == player.GetCharacter()) return true;
	//Diagonals
	else if (gameArray[0][0] == player.GetCharacter() && gameArray[1][1] == player.GetCharacter() && gameArray[2][2] == player.GetCharacter()) return true;
	else if (gameArray[2][0] == player.GetCharacter() && gameArray[1][1] == player.GetCharacter() && gameArray[0][2] == player.GetCharacter()) return true;
	//No Win
	else return false;
}//end playerHasWon()
/**************************************************/
bool BoardIsFilled() {
	bool boardFilled = true;
	for (int i = 0; i < gameSize; i++) {
		for (int j = 0; j < gameSize; j++) {
			if (gameArray[i][j] == ' ') {
				boardFilled = false;
				break;
			}//end if
		}//end for
	}//end for
	return boardFilled;
}//end boardisFilled()
/**************************************************/
bool PositionIsEmpty(int i, int j) {
	if (gameArray[i][j] == ' ') return true;
	else return false;
}//end positionIsEmpty()
/**************************************************/
void MakeEasyMove(Player &npc) {
	int randomRow = GetRandomNumber(0, 2); int randomColumn = GetRandomNumber(0, 2);
	if (PositionIsEmpty(randomRow, randomColumn)) gameArray[randomRow][randomColumn] = npc.GetCharacter();
	else MakeEasyMove(npc);
}//end makeEasyMove()
/**************************************************/
void PrintEndingBoard(Player player) {
	SetColor(green);
	cout << "                -----------------" << endl;
	for (int i = 0; i < gameSize; i++) {
		cout << "                ";
		for (int j = 0; j < gameSize; j++) {
			cout << "|| "; 
			if (gameArray[i][j] == player.GetCharacter()) PrintColored(blue, gameArray[i][j]);
			else PrintColored(red, gameArray[i][j]);
			cout << " ";
		}//end for
		cout << "||" << endl;
	}//end for
	cout << "                -----------------" << endl;
	cout << endl;
	SetColor(white);
}//end printEndingBoard()
/**************************************************/
void GameEndHandler(Player &player, Player &npc) {
	cout << "\a";
	ClearScreen();
	PrintEndingBoard(player);
	if (PlayerHasWon(player)) {
		PrintColored(green, " Congratulations, you have won! :D \n");
		player.IncreaseWins();
		npc.IncreaseLosses();
	}//end if player has won
	else if (PlayerHasWon(npc)) {
		PrintColored(red, " Sorry, you lost :( \n");
		player.IncreaseLosses();
		npc.IncreaseWins();
	}//end if npc has won
	else {
		PrintColored(pink, " It's a draw. Stand down. \n");
		player.IncreaseDraws();
		npc.IncreaseDraws();
	}//end if draw
	system("pause");
}//end gameEndHandler()
/**************************************************/
void DisplayStats(Player player, Player npc) {
	cout << endl;
	cout << "  ---------- SCORE ---------- " << endl;
	cout << "      YOU [" << player.GetWins() << "] - [" << npc.GetWins() << "] PC" << endl;
	cout << "      DRAWS: " << player.GetDraws() << endl;
	cout << endl;
}//end displayStats()
/**************************************************/
void PostGameHandler(Difficulty &gameDifficulty, Player player, Player npc) {
	ClearScreen();
	DisplayStats(player, npc);
	bool lastChoice = false;
	string choiceInput;
	char choice;
	while (!lastChoice) {
		cout << "-- Enter P to play again." << endl;
		if (gameDifficulty == easy) cout << "-- Enter D to Change Difficulty to HARD." << endl;
		if (gameDifficulty == hard) cout << "-- Enter D to Change Difficulty to EASY." << endl;
		cout << "-- Enter R to reset stats." << endl;
		cout << "-- Enter X to exit." << endl;
		cin >> choiceInput;
		choice = choiceInput[0];

		string message;

		switch (choice) {
		case 'p':
		case 'P':
			lastChoice = true;
			ResetGame(gameDifficulty, player, npc);
			break;
		case 'r':
		case 'R':
			lastChoice = false;
			player.ResetStats();
			npc.ResetStats();
			ClearScreen();
			PrintColored(blue, " Stats Reset! \n");
			DisplayStats(player, npc);
			break;
		case 'd':
		case 'D':
			lastChoice = false;
			ClearScreen();
			DisplayStats(player, npc);
			if (gameDifficulty == easy) {
				gameDifficulty = hard;
				PrintColored(red, "Game Difficulty was changed to hard.\n");
			}//end if
			else if (gameDifficulty == hard) {
				gameDifficulty = easy;
				PrintColored(blue, "Game Difficulty was changed to easy.\n");
			}//end else
			break;
		case 'x':
		case 'X':
			lastChoice = true;
			ClearScreen();
			message = GetRandomTaunt();
			PrintColored(pink, "  " + message + "\n");
			system("pause");
			break;
		default:
			lastChoice = false;
			ClearScreen();
			DisplayStats(player, npc);
			PrintColored(red, "- Wrong Choice! -\n");
			break;
		}//end switch

	}//end while
}//end postGameHandler()
/**************************************************/
void ResetGame(Difficulty gameDifficulty, Player player, Player npc) {
	srand(time(NULL));
	ClearScreen();
	SetColor(white);
	InitializeGameBoard();
	RandomPlayerStart();
	while (gameState != ended) PlayGame(gameDifficulty, player, npc);
	if (gameState == ended) {
		GameEndHandler(player, npc); PostGameHandler(gameDifficulty, player, npc);
	}//end if game ended
}//end resetGame()
/**************************************************/
void MakeHardMove(Player player, Player npc) {
	const int cSize = 9;
	int convertedBoard[cSize];
	int boardCount = 0;
	for (int i = 0; i < gameSize; i++) {
		for (int j = 0; j < gameSize; j++) {
			if (gameArray[i][j] == player.GetCharacter()) convertedBoard[boardCount] = -1;
			else if (gameArray[i][j] == npc.GetCharacter()) convertedBoard[boardCount] = 1;
			else convertedBoard[boardCount] = 0;
			boardCount++;
		}//end for
	}//end for

	int move = -1;
	int score = -2;
	for (int i = 0; i < cSize; ++i) {
		if (convertedBoard[i] == 0) {
			convertedBoard[i] = 1;
			int tempScore = -Minimax(convertedBoard, -1, cSize);
			convertedBoard[i] = 0;
			if (tempScore > score) {
				score = tempScore;
				move = i;
			}//end if
		}//end for
	}//end for

	convertedBoard[move] = 1;

	gameArray[0][0] = convertedBoard[0]; gameArray[0][1] = convertedBoard[1]; gameArray[0][2] = convertedBoard[2];
	gameArray[1][0] = convertedBoard[3]; gameArray[1][1] = convertedBoard[4]; gameArray[1][2] = convertedBoard[5];
	gameArray[2][0] = convertedBoard[6]; gameArray[2][1] = convertedBoard[7]; gameArray[2][2] = convertedBoard[8];

	for (int i = 0; i < gameSize; i++) {
		for (int j = 0; j < gameSize; j++) {
			if (gameArray[i][j] == 1) gameArray[i][j] = npc.GetCharacter();
			else if (gameArray[i][j] == -1) gameArray[i][j] = player.GetCharacter();
			else gameArray[i][j] = ' ';
		}//end for
	}//end for

}//end makeHardMove()
/**************************************************/
int WinnerPick(const int convertedGameBoard[9], int cSize) {
	unsigned int winCases[8][3] = { 
		{ 0, 1, 2 },
		{ 3, 4, 5 },
		{ 6, 7, 8 },
		{ 0, 3, 6 },
		{ 1, 4, 7 }, 
		{ 2, 5, 8 },
		{ 0, 4, 8 },
		{ 2, 4, 6 }
	};

	for (int i = 0; i < cSize-1; ++i) {
		if (convertedGameBoard[winCases[i][0]] != 0 &&
			convertedGameBoard[winCases[i][0]] == convertedGameBoard[winCases[i][1]] &&
			convertedGameBoard[winCases[i][0]] == convertedGameBoard[winCases[i][2]])
			return convertedGameBoard[winCases[i][2]];
	}//end for

	return 0;
}//end winnerPick()
/**************************************************/
int Minimax(int convertedGameBoard[9], int player, int cSize) {

	int winPick = WinnerPick(convertedGameBoard, cSize);
	if (winPick != 0) return winPick*player;

	else {

		int move = -1;
		int score = -2;
		int i;
		for (i = 0; i < cSize; ++i) {
			if (convertedGameBoard[i] == 0) {
				convertedGameBoard[i] = player;
				int thisScore = -Minimax(convertedGameBoard, player*-1, cSize);
				if (thisScore > score) {
					score = thisScore;
					move = i;
				}//end if new score > old score
				convertedGameBoard[i] = 0;
			}//end if legal
		}//end for

		if (move == -1) return 0;
		else return score;

	}//end if no winner
}//end minimax()
/**************************************************/
string GetRandomTaunt() {
	const int size = 10;
	string taunts [size];
	taunts[0] = "TOO SCARED TO GO ON...";
	taunts[1] = "RUNNING HOME TO MOMMA?";
	taunts[2] = "ARE YOU SURE? I WILL REALLY MISS YOU :'( ";
	taunts[3] = "ARE YOU REALLY A QUITTER?";
	taunts[4] = "I WOULDN'T LEAVE IF I WERE YOU... DOS IS MUCH WORSE!";
	taunts[5] = "RETIRING TOO SOON?";
	taunts[6] = "GO AHEAD AND LEAVE. SEE IF I CARE!";
	taunts[7] = "GET OUT OF HERE AND GO BACK TO YOUR BORING PROGRAMS...";
	taunts[8] = "WHEN YOU COME BACK, I WILL BE WAITING WITH A BAT!";
	taunts[9] = "PUSS PUSS!";

	int random = GetRandomNumber(0, size-1);
	return taunts[random];

}//end getRandomTaunt()
/**************************************************/