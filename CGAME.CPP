// CGame.cpp

#include "CGame.h"
#include <ctype.h>
#include <string.h>
#include <iomanip.h>
#include <iostream.h>

int num=0;


CGame::CGame()
{
	int i;
	fstream hiScore;
	hiScore.open("hiscore.lst",ios::in);
	if (!hiScore) cout << "Cannot open file" << endl;
	for(i=0;i<10;i++)
	{
		hiScore >> hiScoreList[i].name
						>> hiScoreList[i].score
						>> hiScoreList[i].length;
	}
	hiScore.close();

	Init();
}

CGame::~CGame()

{
	int i;
	fstream hiScore;
	hiScore.open("hiscore.lst",ios::out);
	if (!hiScore) cout << "Cannot open file" << endl;
	for(i=0;i<10;i++)
	{
		hiScore << hiScoreList[i].name << " "
						<< hiScoreList[i].score << " "
						<< hiScoreList[i].length
						<< endl;
	}
	hiScore.close();
}

void CGame::Init()

{
	int i,j,x,y;
	Score=0;
	Time=150;

	Screen = new CScreen;
	Mato = new CMato(Screen);

	randomize();
	num=random(9)+'1';
	writeScoreLine();
	do {
	x=random(WIDTH-2)+1;
	y=random(HEIGHT-2)+1;
	}
	while(Mato->checkFood(x,y)!=0);
	Screen->toScreen(x,y,num,FOODCOLOR);

	// Hiscorelist:

	for(i=0;i<10;i++)

		Screen->printString(WIDTH+20,i+4,
											 hiScoreList[i].name,
											 hiScoreList[i].score,
											 hiScoreList[i].length);

	Time=150;       // The delay between moving at the beginning
}

int CGame::Go()

{
	int Key;
	char End=0;
	int x,y;

	while (!End) {
	while (kbhit())
	{
	Key=getKey();
		switch (Key) {
			case UARROW : Mato->Turn(UP);break;
			case DARROW : Mato->Turn(DOWN);break;
			case LARROW : Mato->Turn(LEFT);break;
			case RARROW : Mato->Turn(RIGHT);break;

			case QUIT :   { End=1;break;}
		}
	}
		Delay();
	switch(Mato->Move())
	{
		case 1 : {End=1;break;}
		case 2 : {
							addPoints((num-'0')*10);
							num=random(9)+'1';
							do {
								x=random(WIDTH-2)+1;
								y=random(HEIGHT-2)+1;
							}
							while(Mato->checkFood(x,y)!=0);
								Screen->toScreen(x,y,num,FOODCOLOR);
								increaseSpeed();
								writeScoreLine();
							break;
						 }
	}

	if (End)
	{
		char again;
		delete(Mato);
		delete(Screen);
		gotoxy(3,11);
		cout << "You died!";
		gotoxy(3,12);
		cout << "Score: " << Score;
		setHiScore(Score,Mato->getLength());
		gotoxy(3,15);
		cin.clear();
		cout << "Another game (y/n)? ";
		cin >> again;
		if(toupper(again) == 'Y') {Init();End=0;}
	}
	} // End loop, end game
	return 0;
}

int CGame::getKey()

{
	int c;
	c = getch();
	if (!c) c=getch()+1000;  	// It was a special key
	return c;
}

void CGame::increaseSpeed()

{ if (Time>1)
	{
		Time=99*Time/100;
	}
}

void CGame::addPoints(int sc)

{
	Score+=sc;
}

void CGame::writeScoreLine()

{
	gotoxy(WIDTH+3,1);
	cout << "Score:" << Score << "      ";
	gotoxy(WIDTH+3,2);
	cout << "Length:" << Mato->getLength() << "    ";
}

void CGame::setHiScore(int score,int length)

{
	int i,j;
	Scores tmpScore,tmpScore2;
	char name[5];

	for(i=0;i<10;i++)
	{
		if (score>hiScoreList[i].score)
		{
			tmpScore=hiScoreList[i];
			for(j=i;j<9;j++)
			{
				tmpScore2=hiScoreList[j+1];
				hiScoreList[j+1]=tmpScore;
				tmpScore=tmpScore2;
			}
		gotoxy(3,13);
		cout << "You scored a highscore!";
		gotoxy(3,14);
		cout << "Name: ";
		cin >> name;
		flush(cout);
		strcpy(hiScoreList[i].name,name);
		hiScoreList[i].score=score;
		hiScoreList[i].length=length;
		break;
		}
	}
}