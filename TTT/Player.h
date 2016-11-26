#ifndef __PLAYER__
#define __PLAYER__ 
#include <string>
/**************************************************/
enum Difficulty { easy, hard };
enum GameState { npcTurn, playerTurn, ended };
class Player {
private:
	char character;
	int wins = 0;
	int draws = 0;
	int losses = 0;
public:
	void SetCharacter(char c) { character = c; }
	char GetCharacter() { return character; }
	void IncreaseWins() { wins++; }
	void IncreaseDraws() { draws++; }
	void IncreaseLosses() { losses++; }
	void ResetStats() {
		wins = 0;
		losses = 0;
		draws = 0;
	}//end ResetStats()
	int GetWins() { return wins; }
	int GetDraws() { return draws; }
};
/**************************************************/
#endif 