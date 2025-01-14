/***********************************************************************
* Programmer: Alba Raya Sanchez
* Class : CptS 122, Fall 2024; Lab Section 3
* Programming Assignment 9 - Battle Ship Game
* Date : December 4, 2024
* Description :
***********************************************************************/

#include "PlayerBaseClass.hpp"

// returns true if all ships are sunk
bool Player::checkIfWinner()
{
	return otherPlayer->board.checkIfAllSunk();
}

// place ship
void Player::placeShip(Ship* ship)
{
	int dir = 0;

	do {

		dir = gen_dir();

		// generate random direction
		ship->setDirection(dir);

		// generate random start position
		gen_start_pt(dir, ship->getSize(), ship);

	} while (!board.placeShip(ship));
}

// place ships on the board randomly
void Player::placeAllShips()
{
	Ship* newShip = nullptr;

	newShip = new Ship("Carrier", 5, 'c', Vector2i(0, 0), 0);
	placeShip(newShip);

	newShip = new Ship("Battleship", 4, 'b', Vector2i(0, 0), 0);
	placeShip(newShip);

	newShip = new Ship("Cruiser", 3, 'r', Vector2i(0, 0), 0);
	placeShip(newShip);

	newShip = new Ship("Submarine", 3, 's', Vector2i(0, 0), 0);
	placeShip(newShip);

	newShip = new Ship("Destroyer", 2, 'd', Vector2i(0, 0), 0);
	placeShip(newShip);
}


// randomly creates direction for placing ships for player 2
// 1: left, 2: right , 3: up - 4: down
char Player::gen_dir()
{
	return 1 + (rand() % 4); // 1: left, 2: right , 3: up - 4: down
}

// randomly creates row and column for placing ships for player 2
void Player::gen_start_pt(char dir, int ship_length, Ship* ship)
{
	Vector2i startPos(0, 0);

	if (dir == 1) // left
	{
		startPos.x = rand() % board.get_num_rows();
		startPos.y = ship_length + (rand() % (board.get_num_cols() - ship_length + 1));
	}
	if (dir == 2) // right
	{
		startPos.x = rand() % board.get_num_rows();
		startPos.y = rand() % (board.get_num_cols() - ship_length + 1);
	}
	if (dir == 3) // up
	{
		startPos.x = ship_length + (rand() % (board.get_num_rows() - ship_length + 1));
		startPos.y = rand() % board.get_num_cols();
	}
	if (dir == 4) // down
	{
		startPos.x = rand() % (board.get_num_rows() - ship_length + 1);
		startPos.y = rand() % board.get_num_cols();
	}
	ship->setStartPos(startPos);
}

// returns number of shots tried by this player
int Player::get_numOfShots()
{
	if (otherPlayer == nullptr) return 0;
	return otherPlayer->get_numOfShots();
}

// resets all parameters from the player prior to restart a game
void Player::resetPlayer()
{
	board.initializeBoard();
}