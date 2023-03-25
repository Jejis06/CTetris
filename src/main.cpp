#include <iostream>
#include <map>
#include <vector>
#include "CORE.h"
#include <stdlib.h>
#include <string>
#include <chrono>
#include <random>

using namespace std;

// :)

/* 
 * CORE.h function list:
 *
 * kbhit() : bool
 * raw_mode_on() : void
 * raw_mode_off() : void 
 * getch() : char
 *
*/

struct Tile{
	int w,h;
	string content;

	Tile(int w, int h, string description = ""): w(w), h(h){
		if(description == "") description = string(w*h,' ');
		content = description;
	}

	string At(int x, int y){
		string o="";
		if(x >= w || y >= h) return o + "$";
		return o + (content[x + y*w]);
	}
};

struct point{
	int x,y;

	point operator+(const point& in){
		return {x + in.x, y + in.y};
	}
	bool operator==(const point& in){
		return (x == in.x && y == in.y);
	}

};
struct Tetromino{
	int color=-1;
	vector<point> points;
	point center = {-1,-1};
	bool Tblock = 0;
	int rotationPoint = -1;
	int reverse = 1;

};


struct Block{
	int reverse = 1;
	int rotation=2;
	vector<point> points;
	bool Tblock = false;

	int clampX,clampY;
	int** arr;
	point center;

	bool find(point a, vector<point>& b){
		for(auto& c : b)
			if(c == a) return true;
		return false;
	}

	void load(point origin, Tetromino Description, int** table, int maxX, int maxY){

		arr = table;
		clampX = maxX;
		clampY = maxY;
		reverse = Description.reverse;
		rotation = Description.rotationPoint;
		Tblock = Description.Tblock;
		center = Description.center + origin;

		for(auto& element : Description.points){
			element.x += origin.x - Description.center.x;
			element.y += origin.y;
			

		}
		points = Description.points;
	}

	bool PossibleX(int direction){
		for(auto& element : points)
			if((element.x + direction < 0 || element.x + direction >= clampX) || 
					(arr[element.y][element.x + direction] >= 1))
				return false;
		return true;
	}
	bool PossibleY(){
		for(auto& element : points)
			if((element.y + 1 >= clampY) ||
					(arr[element.y + 1][element.x] >= 1))
				return false;
		return true;	
	}

	bool Playable(){
		return PossibleX(-1) || PossibleX(1) || PossibleY();
	}


	void Rotate(int Deg){
		Deg = Deg*reverse/90;
		
		int y,x;
		bool possible = true;

		if(rotation < 0) return;


		vector<point> copy = points;
		for(auto& element : copy){
			x = element.x;
			y = element.y;

			element.x = Deg * (y - points[rotation].y ) + points[rotation].x;
			element.y = Deg * (points[rotation].x - x ) + points[rotation].y;

			if(element.x < 0 || element.y < 0 || element.x >= clampX || element.y >= clampY){
				possible = false;
				break;
			}else if(arr[element.y][element.x] >= 1){
				possible = false;
				break;
			}

		}
		if(!possible) return;
		points = copy;

		if(!Tblock) return;
		if(rotation>1) rotation--;
		else rotation++;
		

	}
	void move(int direction){

		if(!PossibleX(direction)) return;	

		center.x += direction;
		for(auto& element : points){
			element.x += direction;
		}
	}
	bool down(){
		bool possible = PossibleY();
		if(!possible) return !possible;
		
		center.y++;
		for(auto& element : points)
			element.y += 1;
		return !possible;

	}

};

						/* TILES */
/*
			light
	+------+
	|  @@  |
	|  @@  |
	+______+
*/
Tile light(8,4,"+------+|  @@  ||  @@  |+______+");

/*
			clunky

	#####
	# @ #
	#####
*/
Tile clunky(5,3,"###### @ ######");

/*
			clear	
*/
Tile clear(5,3,"               ");

/*
  			high 
	 o-----o
	( .---. )
	| |###| |
	( '---' )
	 o-----o
*/
Tile high(9,4," o-----o ( .---. )| |###| |( '---' ) o-----o ");




class Game{
	public:


		/* constructor/destructor */
		Game(int width=10, int height=25, float inputDelay=20, Tile deafultTile=clear):
			w(width), h(height), inputDelay(inputDelay), deafultTile(deafultTile)
		{
			board = new int*[height];
			for(size_t i=0; i<height; i++)
				board[i] = new int[width];

			videoBoard = new string*[height * deafultTile.h];
			for(size_t i=0; i<height * deafultTile.h; i++)
				videoBoard[i] = new string[width * deafultTile.w];

			fill<string>(videoBoard,BACKGROUND,width * deafultTile.w, height * deafultTile.h);
			fill<int>(board,0,width,height);

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

		template<typename T> void fill(T** arr, T val, int W, int H);
		void SetTile(int x, int y, bool remove);

		/* game functions */	

		void loop();

		void refreshFrame();
		void processInput(char in);
		void nextFrame();
		void drawFrame();

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
		bool game_loop = true;
		float inputDelay;
		bool change = false;

		Block currentBlock;
		int** board = nullptr;
		string** videoBoard = nullptr;

		int frameDelay = 30;
		Tile deafultTile;

		/* codes */
		short LEFT=1,
		      RIGHT=2,
		      DOWN=3,
		      ROTATE_LEFT=4,
		      ROTATE_RIGHT=5;

		string BACKGROUND = ".";

		// \033[XXXm
		string CLEAR = 		"\033c";
		string END = 		"\e[0m";

		string RED = 		"\e[41m";
		string GREEN = 		"\e[42m";
		string YELLOW = 	"\e[43m";
		string CYAN = 		"\e[46m";
		string MAGENTA = 	"\e[45m";
		string WHITE = 		"\e[47m";
		string BLUE=		"\e[44m";


		/* graphics */
		string colorTable[7] = {CYAN, BLUE, WHITE, MAGENTA, GREEN, RED, YELLOW};

		/* tetrominos */
		Tetromino I_block = 		{1, {{0,1},{1,1},{2,1},{3,1}}, {2,1}, 1, 2};
		Tetromino L_block = 		{2, {{0,0},{0,1},{1,1},{2,1}}, {1,1}, 0, 2, -1};
		Tetromino REV_L_block = 	{3, {{2,0},{0,1},{1,1},{2,1}}, {1,1}, 0, 2, -1};
		Tetromino T_block = 		{4, {{0,1},{1,1},{2,1},{1,0}}, {1,1}, 0, 1, -1};
		Tetromino SQUIG_block = 	{5, {{0,0},{1,0},{1,1},{2,1}}, {1,1}, 0, 2, -1};
		Tetromino REV_SQUIG_block = 	{6, {{1,0},{2,0},{1,1},{0,1}}, {1,1}, 0, 2, -1};
		Tetromino CUBE_block = 		{7, {{1,1},{2,1},{1,2},{2,2}}, {1,1}};

		vector<Tetromino> pieces = {I_block, L_block, REV_L_block, T_block, SQUIG_block, REV_SQUIG_block, CUBE_block};
		vector<Tetromino> piecesPool = pieces;



		/* controls */
		const map<char, short> INPUT_MAP = {
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

template<typename T>
void Game::fill(T** arr, T val, int W, int H){
	for(int x=0; x<W; x++)
		for(int y=0; y<H; y++)
			arr[y][x] = val;
}

void Game::SetTile(int x, int y, bool remove = false){
	for(int x1=x * deafultTile.w; x1 <= x * deafultTile.w + deafultTile.w-1; x1++){
		for(int y1=y * deafultTile.h; y1 <= y * deafultTile.h + deafultTile.h-1; y1++){
			if (remove) videoBoard[y1][x1] = BACKGROUND;
			else videoBoard[y1][x1] = colorTable[board[y][x] - 1] + deafultTile.At(x1-x*deafultTile.w,y1-y*deafultTile.h) + END;

		}
	}
}





void Game::loop(){

	bool frameWait=false;
	int frameCount=0;
	auto startTime = chrono::high_resolution_clock::now();

	raw_mode_on();
	while(game_loop){
		if(kbhit()){
			/* get input */
			char in = getch();
			
			/* check if key can be captured */
			if(!frameWait){
				/* register key press */
				processInput(in);
				frameWait = 1;
			}

			/* clear unused char`s in buffer */
			raw_mode_off();
			tcflush(0, TCIFLUSH);
			raw_mode_on();
		} 

		auto endTime = chrono::high_resolution_clock::now();	
		float deltaTime = chrono::duration<float, chrono::milliseconds::period>(endTime - startTime).count();

		if(deltaTime >= inputDelay){
			startTime = endTime;
			frameWait = 0;

			if(++frameCount >= frameDelay){
				frameCount = 0;
				/* process frame */
				nextFrame();
				drawFrame();
			}
			/* keep last frame if not changed */
		}
	}
	/* clear */
	raw_mode_off();
	tcflush(0, TCIFLUSH);

	/* gameover screen */
	gameOver();

}

void Game::refreshFrame(){
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			if(board[y][x] >= 1) SetTile(x,y);
			else SetTile(x,y,1);
		}
	}

}

void Game::processInput(char in){
	if(INPUT_MAP.count(in) == 0) return;
	int code = INPUT_MAP.at(in);

	for(auto& element : currentBlock.points){
		board[element.y][element.x] = 0;
		SetTile(element.x,element.y, 1);
	}

	
	if(code == LEFT){
		currentBlock.move(-1);
	}
	else if(code == RIGHT){
		currentBlock.move(1);

	}
	else if(code == DOWN){
		change = currentBlock.down();
		points++;
	}
	else if(code == ROTATE_LEFT){
		currentBlock.Rotate(-90);

	}
	else if(code == ROTATE_RIGHT){
		currentBlock.Rotate(90);
	}

	else if(code == 11){
		frameDelay -= 1;
	}

	else if(code == 12){ 
		frameDelay += 1;
	}
	/* update frame */
	for(auto& element : currentBlock.points){
		board[element.y][element.x] = currentColor;
		SetTile(element.x,element.y);
	}

	
	drawFrame();

}

void Game::nextFrame(){
	for(auto& element : currentBlock.points){
		board[element.y][element.x] = 0;
		SetTile(element.x, element.y, 1);
	}

	change = currentBlock.down();

	for(auto& element : currentBlock.points){
		board[element.y][element.x] = currentColor;
		SetTile(element.x, element.y);
	}
}

void Game::drawFrame(){
	cout << CLEAR;
	if(change){
		if(checkLines()) levelIncrease();
		randomBlock();
		change = false;
	}
	cout << "LEVEL : " << level << " FRAMES : " << frameDelay << " POINTS : " << points << " NEXT : " << nextBlockIND<<  '\n';


	for(int y=0; y<h * deafultTile.h; y++){
		for(int x=0; x<w * deafultTile.w; x++){
			cout << videoBoard[y][x];
		}
		cout << '\n';
	}
	/*
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			if(board[y][x] >= 1) cout << board[y][x];
			else cout << ' ';
		}
		cout << '\n';
	}
	*/


}





void Game::randomBlock(){

	currentColor = piecesPool[nextBlockIND].color;
	currentBlock.load({w/2,0},piecesPool[nextBlockIND], board, w , h);
	if(!currentBlock.Playable()) game_loop = false;

	piecesPool.erase(piecesPool.begin() + nextBlockIND);
	if(piecesPool.empty())
	       	piecesPool = pieces;

	nextBlockIND =  rand() % piecesPool.size();

	refreshFrame();
}





bool Game::checkLines(){
	int iterations = 0;
	for(int y=0; y<h; y++){
		int whole=0;
		for(int x=0; x<w; x++)
			if(board[y][x] >= 1) whole++;

		if(whole != w) continue;
		iterations++;

		bool empty = false;
		int upper=1;
		while(!empty){
			empty = true;
			for(int x=0; x<w; x++){
				board[y-upper+1][x] = board[y-upper][x];
				if(board[y-upper+1][x] >= 1) empty = false;
			}
			upper++;
		}
		
	}
	if(iterations > 0){
		points += (level+1) * scores[iterations-1];
		refreshFrame();
	}

	linesCleared += iterations;
	totalLinesCleared += iterations;

	return (iterations > 0);
	
}

void Game::levelIncrease(){

	/*

	  lvl.	pts.
	 0 - 3 (level+1) * 10 / 2
	 4 - 5 50
	 6 - 9 50 + (level - 6) * 10
	 10 - 11 100

	 */

	/* 0-3 */
	if(level <= 3 && linesCleared >= (level+1)*2){
		linesCleared -= (level+1) * 2;
		level++;
	}

	/* 4-5 */
	else if(level >= 4 && level <= 5 && linesCleared >= 10){
		linesCleared -= 10;
		level++;
	}

	/* 6-9 */
	else if(level >= 6 && level <= 9 && linesCleared >= 10 + (level - 6) * 1){
		linesCleared -= 10 + (level - 15) * 1;
		level++;
	}

	/* 10-11 */
	else if(level >= 10 && level <= 11 && linesCleared >= 20){
		linesCleared -= 20;
		level++;
	}

	frameDelay = speeds[level];

	
}


	

void Game::gameOver(){
	cout << CLEAR << "KONIEC TYEGFO\n";
}


int main(){
	Game tetris;
	return 0;
}

