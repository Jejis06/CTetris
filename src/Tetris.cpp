#include "Tetris.h"

template<typename T>
void Game::fill(T** arr, T val, int W, int H, int startX, int startY){
	for(int x=startX; x<W; x++)
		for(int y=startY; y<H; y++)
			arr[y][x] = val;
}

void Game::SetTile(int x, int y, bool remove = false){

	int startX = x * deafultTile.w,
	    startY = y * deafultTile.h;

	int endX = startX + deafultTile.w-1,
	    endY = startY + deafultTile.h-1;

	if(remove){
		fill<std::string>(videoBoard,BACKGROUND,endX+1,endY+1,startX,startY);
		return;
	}

	for(int y1=startY; y1 <= endY; y1++){
		for(int x1=startX; x1 <= endX; x1++)
			videoBoard[y1][x1] =colorTable[board[y][x] - 1] +  deafultTile.At(x1-x*deafultTile.w,y1-y*deafultTile.h) + END;

	}
}




void Game::loop(){

	bool frameWait=false;
	int frameCount=0;
	auto startTime = std::chrono::high_resolution_clock::now();

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

		auto endTime = std::chrono::high_resolution_clock::now();
		float deltaTime = std::chrono::duration<float, std::chrono::milliseconds::period>(endTime - startTime).count();

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
		points += 100000;
	}

	else if(code == 12){
		points -= 100000;
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
	std::cout << CLEAR;
	if(change){
		if(checkLines()) levelIncrease();
		randomBlock();
		change = false;
	}

	for(int y=0; y<h * deafultTile.h; y++){

		if(y == 0) drawStats();

		drawBorder(1);
		for(int x=0; x<w * deafultTile.w; x++){
			std::cout << videoBoard[y][x];
		}
		drawBorder(1);
		std::cout << '\n';

		if(y == h * deafultTile.h - 1) drawBorder(0);
	}
}

void Game::drawBorder(bool Horizontal_Vertical){/*
		  Horizontal	- false
		  Vertical	- true
	 */

	if(Horizontal_Vertical){
		for(int i=0; i<borderWidth; i++)
			std::cout << BORDER_V;
		return;
	}

	for(int i=0; i< borderHeight; i++){
		for(int j=0; j<w * deafultTile.w + 2 * borderWidth ; j++)
			std::cout << BORDER_H;
		std::cout << '\n';
	}


}

void Game::drawStats(){

	std::string information = INFORMATION_C + " LEVEL : " + std::to_string(level) + " " + END +
		BORDER_C + " | " + END +
		INFORMATION_C + " POINTS : " + std::to_string(points) + " " + END;

	int len = information.size() - (INFORMATION_C + INFORMATION_C + END + END + END + BORDER_C).size();

	int endI = abs((2 * borderWidth + w * deafultTile.w)/2 - len/2);
	int correction = (2 * endI + len) - (2 * borderWidth + w * deafultTile.w);

	for(int i=0; i<endI-correction; i++) std::cout << BORDER_V;
		std::cout << information;
	for(int i=0; i<endI; i++) std::cout << BORDER_V;
		std::cout << '\n';

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




void Game::gameOver() {
	std::cout << CLEAR << "GAME OVER\n";
	std::cout << "SCORE : " << points;
}



