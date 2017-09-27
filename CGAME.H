// CGame.h

#include <fstream.h>
#include "matodef.h"
#include "CMato.h"

struct Scores
{
	char	name[5];
	int		score;
	int 	length;
};


class CGame {

	public:
		CGame();
		~CGame();
		int Go();					// Starts the game

	protected:
		// Methods:
		void Init();
		int getKey();			// Reads player input
		void Delay() {delay(Time);}			// Delays the game
		void addPoints(int sc);
		void writeScoreLine();
		void increaseSpeed();
		void setHiScore(int,int);
		// Attributes:
		int Score;
		int Time;					// The current delay
		CMato* Mato;
		CScreen* Screen;
		Scores hiScoreList[10];

};

