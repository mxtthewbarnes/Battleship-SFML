
#pragma once

#include <stdlib.h> // srand (), rand ()
#include <time.h> // time ()

#include "Ship.hpp"

class Board
{

public:

	// Constructor
	Board();

	// Getters
	int get_num_rows() { return num_rows; }
	int get_num_cols() { return num_cols; }
	Ship& get_Ships(int s) { return *(shipList[s]); }
	int get_window_side() { return windowSide; }
	string get_player_name() { return playerName; }
	sf::RenderWindow* get_window() { return window; }

	// Setters
	void set_window(sf::RenderWindow& win) { window = &win; }
	void set_window_side(int side) { windowSide = side; }
	void set_player_name(string name) { playerName = name; }
	void set_message(string msg) { coutMessage = msg; }
	void set_hiddenBoard(bool hid) { hiddenBoard = hid; }

	void initializeBoard();
	bool placeShip(Ship* ship);
	void displayBoard();
	bool shootPosition(int row, int col);
	bool checkIfSunk(Ship& ship);
	bool checkIfAllSunk();
	int get_numOfShots();
	float getCellSize();
	void placeShipManual(Ship& ship);
	void playTurnForHuman();

	// Destructor
	~Board();


private:
	string playerName;
	string coutMessage;
	int num_rows;
	int num_cols;
	char sea[10][10];
	Ship* shipList[5];
	Vector2i displayPosition;
	sf::Sprite background;
	sf::RenderWindow* window;
	int windowSide;  // 0 for left size - 1 for right side
	bool hiddenBoard;

	int pos_ship(char id);
	void adjacent_cell(int* r, int* c, int dir);
	Vector2i get_displayPos();
	int scan_board_pos_dir(Vector2i& pos);
	void highlightCells(int size, sf::Vector2i mousePos, int dir);

};
