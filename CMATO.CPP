// cmato.cpp

#include <string.h>
#include <conio.h>
#include "CMato.h"

CMato::CMato(CScreen* Scr)
{
	Body[0][0]=(int)(WIDTH/2);
	Body[0][1]=13;
	Body[1][0]=Body[0][0];
	Body[1][1]=Body[0][1]-1;
	Dir=0;
	Length=1;
	Growing=0;
	Screen=Scr;
}

CMato::~CMato()

{
	
}

//int Move()

// Returns  0 if successfull
//          1 if hit something nasty

int CMato::Move()

{
	char newx,newy;
	int res;

	switch (Dir) {

		case UP 		: {
							newx=Body[0][0];
							newy=Body[0][1]-1;break;
						}
		case LEFT  : {
							newx=Body[0][0]-1;
							newy=Body[0][1];break;
						}
		case DOWN  : {
							newx=Body[0][0];
							newy=Body[0][1]+1;break;
						}
		case RIGHT : {
							newx=Body[0][0]+1;
							newy=Body[0][1];break;
						}
	}
	if (Growing==0) {
			Screen->toScreen(Body[Length][0],Body[Length][1],' ',BKCOLOR);
			}
	Screen->toScreen(Body[0][0],Body[0][1],BODY,BODYCOLOR);
	rotateList(newx,newy);
	res=Screen->toScreen(Body[0][0],Body[0][1],HEAD,HEADCOLOR);
	if (Growing!=0) {Length++;Growing=0;}
	if (res==0) return 0;
	if (res==1) return 1;  // Died!
	if (res==2) {Growing=1;return 2;}
	return 0;
}

int CMato::Turn(char dir)

{
	Dir=dir;
  return 0;
}

int CMato::rotateList(char newheadx,char newheady)

{
	int i;

	if (Growing!=0) Length++;
	for(i=Length-1;i>=0;i--) {
		Body[i+1][0]=Body[i][0];
		Body[i+1][1]=Body[i][1];
		}

	Body[0][0]=newheadx;Body[0][1]=newheady;
	if (Growing!=0) Length--;
	return 0;
}

int CMato::getLength()

{
	return Length+1;
}

int CMato::checkFood(int x,int y)

{
	int i;
	for(i=0;i<Length;i++)
	{
		if (Screen->fromScreen(x,y) != 0)
		return 1;
	}
	return 0;
}