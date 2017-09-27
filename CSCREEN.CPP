// CScreen.cpp

#include <conio.h>
#include "CScreen.h"
#include <dos.h>
#include <iostream.h>
#include <ctype.h>
#include "matodef.h"
#include <iomanip.h>

CScreen::CScreen()
{
	int i;
	char name[5];
	int score,length;

	Scr=(unsigned int far *)MK_FP(0xb800,0);

	hideCursor();
	clrscr();
	gotoxy(WIDTH+20,1);
	cout << "     HISCORES";
	gotoxy(WIDTH+20,2);
	cout << "Name:  Score: Length:";
	gotoxy(WIDTH+20,3);
	cout << "-----  ------ -------";
	gotoxy(WIDTH+8,17);
	cout << "    MATO v 1.00    ";
	gotoxy(WIDTH+8,20);
	cout << " (C) M. Poutiainen ";
	gotoxy(WIDTH+8,21);
	cout << "        1994       ";

	for (i=80-WIDTH;i<80;i++)
		toScreen(i,15,196,BLUE);

	for (i=0;i<HEIGHT;i++)         // Left vertical wall
		toScreen(0,i,WALL,BLUE);
	for (i=0;i<HEIGHT;i++)				 // Right vertical wall
		toScreen(WIDTH-1,i,WALL,BLUE);
	for (i=0;i<WIDTH;i++)					 // Upper horizontal wall
		toScreen(i,0,WALL,BLUE);
	for (i=0;i<WIDTH;i++)					 // Lower horizontal wall
		toScreen(i,HEIGHT-1,WALL,BLUE);

}

CScreen::~CScreen()
{
	showCursor();
}

int CScreen::fromScreen(int x, int y)
{
	int a;
	a=Scr[y*80+x] & 255;
	if (isdigit(a)) return 2;
	switch (a) {
		case WALL : {return 1;}
		case BODY : {return 1;}
		default 	: {return 0;}
		}
	return 0;
}

int CScreen::toScreen(int x, int y, char c,char color)
{
	int Next;
	Next=fromScreen(x,y);
	Scr[y*80+x]=c+color*256;

	switch(Next) {
		case 1 : {return 1;}
		case 2 : {return 2;}
    default: {return 0;}
		}

	return 0;
}

void CScreen::hideCursor()
{
	asm { mov ax,0x0100
				mov cx,0x0700
				int 0x10
			}

}

void CScreen::showCursor()
{
	asm { mov ax,0x100
				mov cx,0x607
				int 0x10
			}
}

void CScreen::printString(int x, int y, char str [5], int score, int length)

{
	gotoxy(x,y);
	cout.width(7);
	cout.setf(ios::left);
	cout << str;
	cout.width(6);
	cout.setf(ios::right);
	cout << score;
	cout.width(7);
	cout << length;
}