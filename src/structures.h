#include <string>
#include <vector>

struct Tile{
	int w,h;
	std::string content;

	Tile(int w, int h, std::string description = ""): w(w), h(h){
		if(description == "") description = std::string(w*h,' ');
		content = description;
	}

	std::string At(int x, int y){
		std::string o="";
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
	std::vector<point> points;
	point center = {-1,-1};
	bool Tblock = 0;
	int rotationPoint = -1;
	int reverse = 1;

};


struct Block{
	int reverse = 1;
	int rotation=2;
	std::vector<point> points;
	bool Tblock = false;

	int clampX,clampY;
	int** arr;
	point center;

	bool find(point a, std::vector<point>& b){
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


		std::vector<point> copy = points;
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


