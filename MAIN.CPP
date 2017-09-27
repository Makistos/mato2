// main.cpp

#include "matodef.h"
#include "CGame.h"

int main() {
	CGame Game;
	while (Game.Go() != 0) ;
	clrscr();
	return 0;
}