

#pragma once
#include "Ship.hpp"
#include "BoardClass.hpp"

class Player
{

public:
	// Constructor
	Player()
	{
		name = "";
		otherPlayer = nullptr;
		canPeekOther = false;
	}

	// Getters
	string& get_name() { return name; }
	int get_numOfShots();
	Board& get_board() { return board; }
	Player* get_otherPlayer() { return otherPlayer; }

	// Setters
	void set_name(string& str) {
		name = str;
		board.set_player_name(name);
	}
	void set_board(Board& newBoard) { board = newBoard; }
	void set_otherPlayer(Player* other) { otherPlayer = other; }

	// checks if the player is able to peek at the other player board
	bool canPeek() { return canPeekOther; }

	// checks if player has won the game
	bool checkIfWinner();

	// place all 5 ships on the player's board
	virtual void placeAllShips();

	// manages a turn of the game for this player
	virtual void playTurn() {}

	// resets all parameters from the player prior to restart a game
	virtual void resetPlayer();

	// Destructor
	~Player() {}

protected:

	string name;
	Board board;
	Player* otherPlayer;
	bool canPeekOther;

private:
	char gen_dir();
	void gen_start_pt(char dir, int ship_length, Ship* ship);

	// place ship
	void placeShip(Ship* ship);
};
