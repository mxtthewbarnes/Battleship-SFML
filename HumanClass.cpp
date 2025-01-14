
#include "HumanClass.hpp"

void Human::placeShip(Ship& newShip)
{
    board.placeShipManual(newShip);

    //board.displayBoard();
    //otherPlayer->get_board().displayBoard();
    //board.get_window()->display();
}

void Human::placeAllShips()
{
    Ship* newShip = nullptr;

    newShip = new Ship("Carrier", 5, 'c', Vector2i(0, 0), 1);
    placeShip(*newShip);
    newShip = nullptr;

    newShip = new Ship("Battleship", 4, 'b', Vector2i(0, 0), 1);
    placeShip(*newShip);
    newShip = nullptr;

    newShip = new Ship("Cruiser", 3, 'r', Vector2i(0, 0), 1);
    placeShip(*newShip);
    newShip = nullptr;

    newShip = new Ship("Submarine", 3, 's', Vector2i(0, 0), 1);
    placeShip(*newShip);
    newShip = nullptr;

    newShip = new Ship("Destroyer", 2, 'd', Vector2i(0, 0), 1);
    placeShip(*newShip);
    newShip = nullptr;
}

void Human::playTurn()
{
    otherPlayer->get_board().playTurnForHuman();
}

// resets all parameters from the player prior to restart a game
void Human::resetPlayer()
{
    Player::resetPlayer();
}