#include "Tetris.cpp"


						/* POSSIBLE TILES */
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

int main(int argc, char** argv){
	if(argc >= 3){
		Game tetris(clear,std::stoi(argv[1]),std::stoi(argv[2]));
		return 0;
	}

	std::cout << "Going through deafult settings to customize (w/h) do : \n" << argv[0] << " <width> <height>\n";
	Game tetris(clear);
		
}

