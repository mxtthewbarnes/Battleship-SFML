
#pragma once
#include "PlayerBaseClass.hpp"

class Computer : public Player
{
private:
	Vector2i targetDetectedStart;
	Vector2i targetDetectedEnd;

public:
	// Constructor
	Computer();

	// manages a turn of the game for this player
	void playTurn();

	// resets all parameters from the player prior to restart a game
	virtual void resetPlayer();

	// Destructor
	~Computer() {};
};
