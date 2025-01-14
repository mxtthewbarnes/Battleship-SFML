#include "Ship.hpp"
#include <vector> 
 
using sf::Color; 
using std::vector; 

//initializing transparent red color
Color transparentRed(255, 0, 0, 128);


enum cellSatus 
{
	EMPTY, SHIP, HIT, MISS
};


class Board {
private: 
	int col; 
	int row; 
	float cellSize; 

	vector<vector<cellSatus>> grid; //cell status grid
	vector<Ship> ships; //vector of ships 

public: 
//						Constructor
//----------------------------------------------------------
	Board(int col, int row, float cellSize); 





//					Render background & grid
//----------------------------------------------------------
	void renderGrid(sf::RenderWindow& window); 




	 






};