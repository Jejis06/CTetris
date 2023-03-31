#include <random>
#include <map>
#include <chrono>
#include <stdlib.h>
#include <iostream>

#include "CORE.h"
#include "structures.h"


/*
		  CORE.h function list:

	  kbhit() : bool
	  raw_mode_on() : void
	  raw_mode_off() : void
	  getch() : char

*/


class Game{
	public:


		/* constructor/destructor */
		Game(Tile deafultTile,int width=10, int height=24, float inputDelay=20, int borderWidth=2, int borderHeight=2):
			w(width), h(height), inputDelay(inputDelay), deafultTile(deafultTile), borderWidth(borderWidth), borderHeight(borderHeight)
		{

			BACKGROUND = BACKGROUND_C + BACKGROUND + END;
			BORDER_H = BORDER_C + BORDER_H + END;
			BORDER_V = BORDER_C + BORDER_H + END;

			board = new int*[h];
			for(size_t i=0; i<h; i++)
				board[i] = new int[w];

			videoBoard = new std::string*[h * deafultTile.h];
			for(size_t i=0; i<h * deafultTile.h; i++)
				videoBoard[i] = new std::string[w * deafultTile.w];

			fill<std::string>(videoBoard,BACKGROUND,w * deafultTile.w, h * deafultTile.h);
			fill<int>(board,0,w,h);

			frameDelay = speeds[level];

			srand(time(NULL));
			

			nextBlockIND = rand() % pieces.size();

			randomBlock();
			loop();

		}

		~Game(){
			delete[] board;
			delete[] videoBoard;

		}

		/* helper functions */

		template<typename T> void fill(T** arr, T val, int W, int H, int startX=0, int startY=0);
		void SetTile(int x, int y, bool remove);

		/* game functions */	

		void menu();
		void loop();

		void refreshFrame();
		void processInput(char in);
		void nextFrame();
		void drawFrame();
		void drawBorder(bool Horizontal_Vertical);
		void drawStats();

		void randomBlock();

		bool checkLines();
		void levelIncrease();

		void gameOver();


	private:
		/* game */

		int points=0;
		int level=0;
		int linesCleared=0;
		int totalLinesCleared=0;

		int nextBlockIND;
		int currentColor;
		int speeds[12] = {46,41,36,31,26,21,18,16,13,8,6,4};
		int scores[4] = {40, 100, 300, 1200};

		/* sys */
		int w,h;
		int borderWidth, borderHeight;
		bool game_loop = true;
		float inputDelay;
		bool change = false;

		Block currentBlock;
		int** board = nullptr;
		std::string** videoBoard = nullptr;

		int frameDelay = 30;
		Tile deafultTile;

		/* codes */
		short LEFT=1,
		      RIGHT=2,
		      DOWN=3,
		      ROTATE_LEFT=4,
		      ROTATE_RIGHT=5;

		std::string BACKGROUND = ".";

		std::string BORDER_V = "|";
		std::string BORDER_H = "-";

		// \033[XXXm
		std::string CLEAR = 		"\033c";
		std::string END = 		"\e[0m";

		std::string RED = 		"\e[97;41m";
		std::string GREEN = 		"\e[97;42m";
		std::string YELLOW = 		"\e[97;43m";
		std::string CYAN = 		"\e[97;46m";
		std::string MAGENTA = 		"\e[97;45m";
		std::string WHITE = 		"\e[97;47m";
		std::string BLUE =		"\e[97;44m";

		std::string BACKGROUND_C = 	"\e[40m";
		std::string BORDER_C = 		"\e[30;100m";
		std::string INFORMATION_C =	"\e[31;40m";


		/* graphics */
		std::string colorTable[7] = {CYAN, BLUE, WHITE, MAGENTA, GREEN, RED, YELLOW};

		/* tetrominos */
		Tetromino I_block = 		{1, {{0,1},{1,1},{2,1},{3,1}}, {2,1}, 1, 2};
		Tetromino L_block = 		{2, {{0,0},{0,1},{1,1},{2,1}}, {1,1}, 0, 2, -1};
		Tetromino REV_L_block = 	{3, {{2,0},{0,1},{1,1},{2,1}}, {1,1}, 0, 2, -1};
		Tetromino T_block = 		{4, {{0,1},{1,1},{2,1},{1,0}}, {1,1}, 0, 1, -1};
		Tetromino SQUIG_block = 	{5, {{0,0},{1,0},{1,1},{2,1}}, {1,1}, 0, 2, -1};
		Tetromino REV_SQUIG_block = 	{6, {{1,0},{2,0},{1,1},{0,1}}, {1,1}, 0, 2, -1};
		Tetromino CUBE_block = 		{7, {{1,1},{2,1},{1,2},{2,2}}, {1,1}};

		std::vector<Tetromino> pieces = {I_block, L_block, REV_L_block, T_block, SQUIG_block, REV_SQUIG_block, CUBE_block};
		std::vector<Tetromino> piecesPool = pieces;



		/* controls */
		const std::map<char, short> INPUT_MAP = {
			{'a', LEFT},
			{'d', RIGHT},
			{'s', DOWN},
			{'k', ROTATE_LEFT},
			{'l', ROTATE_RIGHT},

			/* debug */
			{']', 11},
			{'[', 12}	

		};

};


