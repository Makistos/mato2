// CMato.h

#include "matodef.h"
#include "CScreen.h"

class CMato {

	public:
		CMato(CScreen*);
		~CMato();
		int Move();
		int Turn(char dir);
		int getLength();
		int checkFood(int x,int y);  // We check that the food isn't on the
																 // worm.
	private:
		char Body[(WIDTH-2)*(HEIGHT-2)][2]; // [0][0] tells the coordinates of the head
		char Dir;						//direction: 0=up, 1= right, 2= down, 3= left
		int Length;
		int Growing;
		int rotateList(char newheadx, char newheady);
		CScreen* Screen;  // Pointer to the screen object
};

