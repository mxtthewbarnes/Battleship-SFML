/***********************************************************************
* Programmer: Alba Raya Sanchez
* Class : CptS 122, Fall 2024; Lab Section 3
* Programming Assignment 9 - Battle Ship Game
* Date : December 4, 2024
* Description :
***********************************************************************/

#pragma once
#include "Ship.hpp"
#include "PlayerBaseClass.hpp"

class Human :public Player
{
public:

	Human() { canPeekOther = true; }

	// place all 5 ships on the player's board
	virtual void placeAllShips();

	// manages a turn of the game for this player
	virtual void playTurn();

	// resets all parameters from the player prior to restart a game
	virtual void resetPlayer();

private:
	void placeShip(Ship& newShip);
};