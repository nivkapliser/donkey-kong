#pragma once

/*
* This class is responsible for the game graphics.
* It contains the game menu, game over screen, game won screen, open screen, instructions screen and stop screen.
* The class also contains a boolean variable that determines whether to add colors to the game or not.
*/

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "utils.h"

class MenuGraphics
{
	static constexpr int GRAPHICS_HIGHT = 23;

	const char* menu[GRAPHICS_HIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "+==============================================================================+",//0
		  "|                    /$$      /$$                                              |",//1                              
		  "|                   | $$$    /$$$                                              |",//2
		  "|                   | $$$$  /$$$$  /$$$$$$  /$$$$$$$  /$$   /$$                |",//3
		  "|                   | $$ $$/$$ $$ /$$__  $$| $$__  $$| $$  | $$                |",//4
		  "|                   | $$  $$$| $$| $$$$$$$$| $$  \\ $$| $$  | $$                |",//5
		  "|                   | $$\\  $ | $$| $$_____/| $$  | $$| $$  | $$                |",//6
		  "|                   | $$ \\/  | $$|  $$$$$$$| $$  | $$|  $$$$$$/                |",//7
		  "|                   |__/     |__/ \\_______/|__/  |__/ \\______/                 |",//8
		  "|==============================================================================|",//9
		  "|                     +---------+-------------------------+                    |",//10
		  "|                     |    1    | Choose board and Start  |                    |",//11
		  "|                     +---------+-------------------------+                    |",//12
		  "|                     |    2    | Disable colors          |                    |",//13
		  "|                     +---------+-------------------------+                    |",//14
		  "|                     |    8    | Display instructions    |                    |",//15
		  "|                     +---------+-------------------------+                    |",//16
		  "|                     |    9    | Exit game :(            |                    |",//17
		  "|                     +---------+-------------------------+                    |",//18
		  "|                                                                              |",//19
		  "|                                                                              |",//20
		  "|                                                                              |",//21
		  "+==============================================================================+" //22
	};

	const char* chooseBoardScreen[GRAPHICS_HIGHT] = {};

	const char* instructions[GRAPHICS_HIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "+==============================================================================+",//0
		  "|                              GAME INSTRUCTIONS                               |",//1
		  "|                             ===================                              |",//2
		  "|  Your job is to help Mario rescue Pauline from the clutches of Donkey Kong.  |",//3
		  "|   You must climb the ladders and jump over barrels to reach the top of the   |",//4
		  "|    building where Pauline is being held.Be careful! Avoid hitting barrels    |",//5
		  "|    or falling from five lines hight. You have three attempts to complete     |",//6
		  "|                       your mission, so do your best!                         |",//7
		  "|                                 Good luck!                                   |",//8
		  "|                                                                              |",//9
		  "|                               KEYBOARD LAYOUT                                |",//10
		  "|                             ===================                              |",//11
		  "|                                     +-----+                                  |",//12
		  "|     W : JUMP / CLIMB UP             | ESC |          +---+                   |",//13
		  "|     A : MOVE LEFT                   +-----+          | W |                   |",//14
		  "|     D : MOVE RIGHT                               +---+---+---+               |",//15
		  "|     S : STAY IN PLACE                            | A | S | D |               |",//16
		  "|     X : CLIMB DOWN                               +---+---+---+               |",//17
		  "|     ESC : PAUSE                                      | X |                   |",//18
		  "|                                                      +---+                   |",//19
		  "|     PRESS ANY KEY TO RETURN...                                               |",//20
		  "+==============================================================================+", //21
		  "																				  " //22
	};

	const char* openScreen[GRAPHICS_HIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "    +======================================================================+    ",//0
		  "    |                                                                      |    ",//1
		  "    |     $$$$$$$\\                      $$\\                                |    ",//2
		  "    |     $$  __$$\\                     $$ |                               |    ",//3
		  "    |     $$ |  $$ | $$$$$$\\  $$$$$$$\\  $$ |  $$\\  $$$$$$\\  $$\\   $$\\      |    ",//4
		  "    |     $$ |  $$ |$$  __$$\\ $$  __$$\\ $$ | $$  |$$  __$$\\ $$ |  $$ |     |    ",//5
		  "    |     $$ |  $$ |$$ /  $$ |$$ |  $$ |$$$$$$  / $$$$$$$$ |$$ |  $$ |     |    ",//6
		  "    |     $$ |  $$ |$$ |  $$ |$$ |  $$ |$$  _$$<  $$   ____|$$ |  $$ |     |    ",//7
		  "    |     $$$$$$$  |\\$$$$$$  |$$ |  $$ |$$ | \\$$\\ \\$$$$$$$\\ \\$$$$$$$ |     |    ",//8
		  "    |     \\_______/  \\______/ \\__|  \\__|\\__|  \\__| \\_______| \\____$$ |     |    ",//9
		  "    |     $$\\   $$\\                              $$\\        $$\\   $$ |     |    ",//10
		  "    |     $$ | $$  |                             $$ |       \\$$$$$$  |     |    ",//11
		  "    |     $$ |$$  / $$$$$$\\  $$$$$$$\\   $$$$$$\\  $$ |        \\______/      |    ",//12
		  "    |     $$$$$  / $$  __$$\\ $$  __$$\\ $$  __$$\\ $$ |                      |    ",//13
		  "    |     $$  $$<  $$ /  $$ |$$ |  $$ |$$ /  $$ |\\__|                      |    ",//14
		  "    |     $$ |\\$$\\ $$ |  $$ |$$ |  $$ |$$ |  $$ |                          |    ",//15
		  "    |     $$ | \\$$\\$$$$$$   |$$ |  $$ |\\$$$$$$$ |$$\\                       |    ",//16
		  "    |     \\__|  \\__|\\______/ \\__|  \\__| \\____$$ |\\__|                      |    ",//17
		  "    |                                  $$\\   $$ |                          |    ",//18
		  "    |                                  \\$$$$$$  |                          |    ",//19
		  "    |                                   \\______/                           |    ",//20
		  "    |                                                                      |    ",//21
		  "    +======================================================================+    "     //22                                
	};

	const char* gameOverScreen[GRAPHICS_HIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "          +=========================================================+           ",//0
		  "          |                                                         |           ",//1
		  "          |      $$$$$$\\                                            |           ",//2
		  "          |     $$  __$$\\                                           |           ",//3
		  "          |     $$ /  \\__| $$$$$$\\  $$$$$$\\$$$$\\   $$$$$$\\          |           ",//4
		  "          |     $$ |$$$$\\  \\____$$\\ $$  _$$  _$$\\ $$  __$$\\         |           ",//5
		  "          |     $$ |\\_$$ | $$$$$$$ |$$ / $$ / $$ |$$$$$$$$ |        |           ",//6
		  "          |     $$ |  $$ |$$  __$$ |$$ | $$ | $$ |$$   ____|        |           ",//7
		  "          |     \\$$$$$$  |\\$$$$$$$ |$$ | $$ | $$ |\\$$$$$$$\\         |           ",//8
		  "          |      \\______/  \\_______|\\__| \\__| \\__| \\_______|        |           ",//9
		  "          |      $$$$$$\\                                            |           ",//10
		  "          |     $$  __$$\\                                           |           ",//11
		  "          |     $$ /  $$ |$$\\    $$\\  $$$$$$\\   $$$$$$\\             |           ",//12
		  "          |     $$ |  $$ |\\$$\\  $$  |$$  __$$\\ $$  __$$\\            |           ",//13
		  "          |     $$ |  $$ | \\$$\\$$  / $$$$$$$$ |$$ |  \\__|           |           ",//14
		  "          |     $$ |  $$ |  \\$$$  /  $$   ____|$$ |                 |           ",//15
		  "          |      $$$$$$  |   \\$  /   \\$$$$$$$\\ $$ |$$\\ $$\\ $$\\      |           ",//16
		  "          |      \\______/     \\_/     \\_______|\\__|\\__|\\__|\\__|     |           ",//17
		  "          |                                                         |           ",//18
		  "          +=========================================================+           ",//19
		  "                                                                                ",//20
		  "                                                                                ",//21
		  "                                                                                " //22
	};

	const char* gameWonScreen[GRAPHICS_HIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789	
		  "+=============================================================================+",//0
		  "|                                                                             |",//1
		  "|     $$$$$$\\                                      $$\\                        |",//2
		  "|    $$  __$$\\                                     $$ |                       |",//3
		  "|    $$ /  \\__| $$$$$$\\ $$\\    $$\\  $$$$$$\\   $$$$$$$ |                       |",//4
		  "|    \\$$$$$$\\   \\____$$\\\\$$\\  $$  |$$  __$$\\ $$  __$$ |                       |",//5
		  "|     \\____$$\\  $$$$$$$ |\\$$\\$$  / $$$$$$$$ |$$ /  $$ |                       |",//6
		  "|    $$\\   $$ |$$  __$$ | \\$$$  /  $$   ____|$$ |  $$ |                       |",//7
		  "|    \\$$$$$$  |\\$$$$$$$ |  \\$  /   \\$$$$$$$\\ \\$$$$$$$ |                       |",//8
		  "|     \\______/  \\_______|   \\_/     \\_______| \\_______|                       |",//9
		  "|    $$$$$$$\\                     $$\\ $$\\                     $$\\ $$\\ $$\\     |",//10
		  "|    $$  __$$\\                    $$ |\\__|                    $$ |$$ |$$ |    |",//11
		  "|    $$ |  $$ |$$$$$$\\  $$\\   $$\\ $$ |$$\\ $$$$$$$\\   $$$$$$\\  $$ |$$ |$$ |    |",//12
		  "|    $$$$$$$  |\\____$$\\ $$ |  $$ |$$ |$$ |$$  __$$\\ $$  __$$\\ $$ |$$ |$$ |    |",//13
		  "|    $$  ____/ $$$$$$$ |$$ |  $$ |$$ |$$ |$$ |  $$ |$$$$$$$$ |\\__|\\__|\\__|    |",//14
		  "|    $$ |     $$  __$$ |$$ |  $$ |$$ |$$ |$$ |  $$ |$$   ____|                |",//15
		  "|    $$ |     \\$$$$$$$ |\\$$$$$$  |$$ |$$ |$$ |  $$ |\\$$$$$$$\\ $$\\ $$\\ $$\\     |",//16
		  "|    \\__|      \\_______| \\______/ \\__|\\__|\\__|  \\__| \\_______|\\__|\\__|\\__|    |",//17
		  "|                                                                             |",//18
		  "+=============================================================================+",//19
		  "                                                                               ",//20
		  "                                                                               ",//21
		  "                                                                               " //22
	};

	const char* stopScreen[GRAPHICS_HIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "+==============================================================================+",//0
		  "|                 /$$$$$$                                                      |",//1
		  "|                /$$__  $$                                                     |",//2
		  "|               | $$  \\__/ /$$$$$$  /$$$$$$/$$$$   /$$$$$$                     |",//3
		  "|               | $$ /$$$$|____  $$| $$_  $$_  $$ /$$__  $$                    |",//4
		  "|               | $$|_  $$ /$$$$$$$| $$ \\ $$ \\ $$| $$$$$$$$                    |",//5
		  "|               | $$  \\ $$/$$__  $$| $$ | $$ | $$| $$_____/                    |",//6
		  "|               |  $$$$$$/  $$$$$$$| $$ | $$ | $$|  $$$$$$$                    |",//7
		  "|                /$$$$$$$ \\_______/|__/ |__/ |__/ \\_______/                    |",//8
		  "|               | $$__  $$                                                     |",//9
		  "|               | $$  \\ $$/$$$$$$  /$$   /$$  /$$$$$$$  /$$$$$$                |",//10
		  "|               | $$$$$$$/____  $$| $$  | $$ /$$_____/ /$$__  $$               |",//11
		  "|               | $$____/ /$$$$$$$| $$  | $$|  $$$$$$ | $$$$$$$$               |",//12
		  "|               | $$     /$$__  $$| $$  | $$ \\____  $$| $$_____/               |",//13
		  "|               | $$    |  $$$$$$$|  $$$$$$/ /$$$$$$$/|  $$$$$$$               |",//14
		  "|               |__/     \\_______/ \\______/ |_______/  \\_______/               |",//15
		  "|                                                                              |",//16
		  "|                                                                              |",//17
		  "|                                                                              |",//18
		  "|                                                                              |",//19
		  "|               PRESS 'ESC' TO RESUME OR ANY KEY TO RETURN TO MENU....         |",//20
		  "|                                                                              |",//21
		  "+==============================================================================+" //22
	};

	const char* goodBye[GRAPHICS_HIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "+==============================================================================+",//0
		  "|                                                                              |",//1
		  "|                                                                              |",//2
		  "|    /$$$$$$                            /$$ /$$$$$$$                      /$$  |",//3
		  "|   /$$__  $$                          | $$| $$__  $$                    | $$  |",//4
		  "|  | $$  \\__/  /$$$$$$   /$$$$$$   /$$$$$$$| $$  \\ $$ /$$   /$$  /$$$$$$ | $$  |",//5
		  "|  | $$ /$$$$ /$$__  $$ /$$__  $$ /$$__  $$| $$$$$$$ | $$  | $$ /$$__  $$| $$  |",//6
		  "|  | $$|_  $$| $$  \\ $$| $$  \\ $$| $$  | $$| $$__  $$| $$  | $$| $$$$$$$$|__/  |",//7
		  "|  | $$  \\ $$| $$  | $$| $$  | $$| $$  | $$| $$  \\ $$| $$  | $$| $$_____/      |",//8
		  "|  |  $$$$$$/|  $$$$$$/|  $$$$$$/|  $$$$$$$| $$$$$$$/|  $$$$$$$|  $$$$$$$ /$$  |",//9
		  "|   \\______/  \\______/  \\______/  \\_______/|_______/  \\____  $$ \\_______/|__/  |",//10
		  "|                                                     /$$  | $$                |",//11
		  "|                                                    |  $$$$$$/                |",//12
		  "|                                                     \\______/                 |",//13
		  "|                                                                              |",//14
		  "|                                                                              |",//15
		  "|                                                                              |",//16
		  "|                                                                              |",//17
		  "|                                                                              |",//18
		  "|                                                                              |",//19
		  "|                                                                              |",//20
		  "|                                                                              |",//21
		  "+==============================================================================+" //22

	};

	const char* legend = " Lives:  | Score:  ";

	enum COLORS {
		BLACK = 0,
		BLUE = 1,
		GREEN = 2,
		CYAN = 3,
		RED = 4,
		MAGENTA = 5,
		BROWN = 6,
		LIGHT_GRAY = 7,
		DARK_GRAY = 8,
		LIGHT_BLUE = 9,
		LIGHT_GREEN = 10,
		LIGHT_CYAN = 11,
		LIGHT_RED = 12,
		LIGHT_MAGENTA = 13,
		YELLOW = 14,
		WHITE = 15
	};
    
	bool addColor = true;

public:
	
	void setCurrentColor(int color) const {
		if (addColor) { setColor(color); }
		else { setColor(WHITE); }
	}

	void setColor(int color) const;
	void printGraphics(const char* graphics[]) const;
	void displayMenu();
	void displayGameOver();
	void displayGameWon();
	void displayOpenScreen();
	void displayInstructions();
	void displayStopScreen();
	void displayGoodBye();
	void disableColors();
	bool getAddColor() const {
		return addColor;
	}
	void setAddColor(bool b) {
		addColor = b;
	}

	int getLightRed() const {
		return LIGHT_RED;
	}
	int getCyan() const {
		return CYAN;
	}
	int getLightGreen() const {
		return LIGHT_GREEN;
	}
	int getBrown() const {
		return BROWN;
	}

};

