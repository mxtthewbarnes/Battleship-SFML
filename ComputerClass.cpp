

#include <Windows.h>
#include "ComputerClass.hpp"

// Constructor
Computer::Computer()
	: targetDetectedStart(-1, -1), targetDetectedEnd(-1, -1)
{
	canPeekOther = false;
}

void Computer::playTurn()
{
	int row = 0, col = 0, dir = 0;
	int valid_shot = 0;

	if (otherPlayer == nullptr) {
		std::cout << "Opponent player hasn't been configured yet" << endl;
		return;
	}

	while (valid_shot == 0)
	{
		row = rand() % otherPlayer->get_board().get_num_rows();   // random position for shot
		col = rand() % otherPlayer->get_board().get_num_cols();   // random position for shot

		// random direction for adjacent cell if selected cell was already used	
		// 1: left, 2: right , 3: up - 4: down	  
		dir = 1 + (rand() % 4);

		//loop to try adjacent cells if the random shot was already used (only for player 2)
		do
		{
			std::cout << "Computer trying to shoot at (" << row << ", " << col << ")" << std::endl;

			// manage shot to a position
			valid_shot = otherPlayer->get_board().shootPosition(row, col);
			/*
			Vector2i posShot(row, col);
			if (valid_shot == 1) // hit
			{
				if ((targetDetectedStart.x == -1) && (targetDetectedStart.y == -1))
					targetDetectedStart = posShot;
				if ((targetDetectedEnd.x == -1) && (targetDetectedEnd.y == -1))
					targetDetectedEnd = posShot;
				if ((targetDetectedStart.x <= 1 - posShot).length() < )
			}
			*/

			//move to adjacent cell
			if (dir == 1 || dir == 2) col--;
			if (dir == 3 || dir == 4) col++;

			// if got to end of board, move to next row or column
			if (col < 0) { col = otherPlayer->get_board().get_num_cols() - 1; row--; }
			if (col >= otherPlayer->get_board().get_num_cols()) { col = 0; row++; }
			if (row < 0) row = otherPlayer->get_board().get_num_rows() - 1;
			if (row >= otherPlayer->get_board().get_num_rows()) row = 0;

		} while (!valid_shot);
	}
	Sleep(1000);
}

// resets all parameters from the player prior to restart a game
void Computer::resetPlayer()
{
	Player::resetPlayer();
	targetDetectedStart = Vector2i(-1, -1);
	targetDetectedEnd = Vector2i(-1, -1);
}