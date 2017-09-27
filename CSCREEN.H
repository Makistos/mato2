// CScreen.h

class CScreen {

	public:
		CScreen();
		~CScreen();
		void Init();
		int InitScreen(); 	// Initializes the screen at the beginning
		int fromScreen(int x, int y); //x,y = the coordinates to check
		int toScreen(int x, int y, char c,char color);
		void hideCursor();
		void showCursor();
		void printString(int, int, char[5], int, int);
	protected:
		unsigned int far *Scr; //The screen

};

