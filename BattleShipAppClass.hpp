
#pragma once

#include "Menu.hpp"
#include "MenuPlayerSetUp.hpp"
#include "HumanClass.hpp"
#include "ComputerClass.hpp"


class BattleShipApp
{
public:

	// constructor
	BattleShipApp();

	// runs the application
	void runApp();

	// destructor
	~BattleShipApp();

private:
	Player* player1;
	Player* player2;

	void createPlayer(Player** player, MenuPlayerSetUp& menu);
	void waitForKey(sf::RenderWindow& window);

};
