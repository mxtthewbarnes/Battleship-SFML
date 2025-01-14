

#include "BoardClass.hpp"

// constructor	
Board::Board()
{
	num_rows = 10;
	num_cols = 10;

	playerName = "";

	initializeBoard();

	for (int i = 0; i < 5; i++) shipList[i] = nullptr;

	displayPosition.x = 0;
	displayPosition.y = 0;

	sf::Font font;
	if (!font.loadFromFile("./resources/minecraft.ttf")) {
		throw std::runtime_error("Unable to load font, check file path.");
	}

	//loads background pic for gameplay (the ocean) 
	sf::Texture gameplayBackgroundTexture;
	if (!gameplayBackgroundTexture.loadFromFile("./resources/image-copy.png")) {
		cout << "Error: Unable to load gameplay background texture. Check file path." << endl;
		return;
	}
	background.setTexture(gameplayBackgroundTexture);
}

void Board::initializeBoard()
{
	int row_index = 0, col_index = 0;

	for (int row_index = 0; row_index < num_rows; ++row_index)
	{
		for (int col_index = 0; col_index < num_cols; ++col_index)
		{
			sea[row_index][col_index] = '~'; // place water symbols on the board
		}
	}
	hiddenBoard = false;
}

// returns true if the ship was placed and false if it couldn't be placed
bool Board::placeShip(Ship* ship)
{
	int pos = pos_ship(ship->getID());
	if (pos == -1 || ship == nullptr) {
		std::cout << "Invalid ship or ID" << std::endl;
		return false;
	}
	for (int cell = 0, r = ship->getStartPos().x, c = ship->getStartPos().y; cell < ship->getSize(); cell++) {
		if (r < 0 || r >= num_rows || c < 0 || c >= num_cols || sea[r][c] != '~') {
			std::cout << "Placement failed for " << ship->getName() << " at (" << r << ", " << c << ")" << std::endl;
			return false;
		}
		adjacent_cell(&r, &c, ship->getDirection());
	}
	for (int cell = 0, r = ship->getStartPos().x, c = ship->getStartPos().y; cell < ship->getSize(); cell++) {
		sea[r][c] = ship->getID();
		adjacent_cell(&r, &c, ship->getDirection());
	}
	if (shipList[pos] != nullptr) {
		delete shipList[pos];
		shipList[pos] = nullptr;
	}
	shipList[pos] = ship;
	std::cout << ship->getName() << " placed successfully." << std::endl;
	coutMessage = ship->getName() + string(" placed successfully.");
	return true;
}

void Board::displayBoard()
{
	float cellSize = getCellSize();
	Vector2i displayPos = get_displayPos();

	sf::Font font;
	if (!font.loadFromFile("./resources/sansation.ttf")) {
		throw std::runtime_error("Unable to load font, check file path.");
	}

	sf::Text captionText;
	captionText.setFont(font);
	captionText.setString(playerName);
	captionText.setCharacterSize(50);
	captionText.setFillColor(sf::Color::Yellow);

	sf::FloatRect textBounds;
	float padding = 15.0f;
	textBounds = captionText.getLocalBounds();
	sf::RectangleShape captionBox;
	captionBox.setSize(sf::Vector2f(textBounds.width + 2 * padding, textBounds.height + 2 * padding));
	captionBox.setFillColor(sf::Color::Black);
	captionBox.setOutlineThickness(9.0f);
	captionBox.setOutlineColor(sf::Color::Black);

	float posX = displayPos.x + (cellSize * 5) - (textBounds.width / 2);
	float posY = (1.0 * window->getSize().y / 9) - (textBounds.height / 2);
	captionBox.setPosition(posX - padding, posY);
	captionText.setPosition(posX, posY);

	window->draw(captionBox);
	window->draw(captionText);

	sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
	cell.setOutlineThickness(2);
	cell.setOutlineColor(sf::Color::Black);
	for (int row = 0; row < num_rows; ++row) {
		for (int col = 0; col < num_cols; ++col) {
			cell.setPosition(displayPos.x + col * cellSize, displayPos.y + row * cellSize);
			if (sea[row][col] == '~') {
				cell.setFillColor(sf::Color::Transparent);
			}
			else if (sea[row][col] == '*') {
				cell.setFillColor(sf::Color(255, 0, 0, 180)); //110
			}
			else if (sea[row][col] == 'm') {
				cell.setFillColor(sf::Color(255, 255, 255, 180));
			}
			else {
				if (hiddenBoard) cell.setFillColor(sf::Color::Transparent);
				else cell.setFillColor(sf::Color::Green);
			}
			window->draw(cell);
		}
	}

	sf::Text messageText;
	messageText.setFont(font);
	messageText.setString(coutMessage);
	if (coutMessage.length() < 40) messageText.setCharacterSize(20);
	else messageText.setCharacterSize(15);
	messageText.setFillColor(sf::Color::Yellow);

	padding = 15.0f;
	textBounds = messageText.getLocalBounds();
	sf::RectangleShape messageBox;
	messageBox.setSize(sf::Vector2f(textBounds.width + 2 * padding, textBounds.height + 2 * padding));
	messageBox.setFillColor(sf::Color::Black);
	messageBox.setOutlineThickness(9.0f);
	messageBox.setOutlineColor(sf::Color::Black);

	posX = displayPos.x + (cellSize * 5) - (textBounds.width / 2);
	//posY = (8.0 * window->getSize().y / 9) - (textBounds.height / 2);
	posY = displayPos.y + (cellSize * 11);
	messageBox.setPosition(posX - padding, posY - padding);
	messageText.setPosition(posX, posY);

	window->draw(messageBox);
	window->draw(messageText);
}

// shoot to a given position - return false if pos repeated
bool Board::shootPosition(int row, int col)
{
	// check if out of board
	if (row < 0 || row >= num_rows || col < 0 || col >= num_cols)
	{
		// message for human player to repeat shot
		char buf[500];
		snprintf(buf, 500, "Position (%d, %d) is out of board. Try another one.\n", row, col);
		coutMessage = string(buf);
		printf(buf);
		return false;
	}

	// check if position was already shot before
	if (sea[row][col] == 'm' || sea[row][col] == '*')
	{
		// message for human player to repeat shot
		char buf[500];
		snprintf(buf, 500, "Position (%d, %d) was already shot. Try another one.\n", row, col);
		coutMessage = string(buf);
		printf(buf);
		return false;
	}

	// check if miss
	if (sea[row][col] == '~')
	{
		// set position to miss
		sea[row][col] = 'm';

		// print message 
		char buf[500];
		snprintf(buf, 500, "(%d, %d) is a miss!", row, col);
		coutMessage = string(buf);
		printf(buf);
	}
	else // hit
	{
		char sunk_ship_code = sea[row][col];

		// set position to hit
		sea[row][col] = '*';

		// print messages 
		char buf[500];
		snprintf(buf, 500, "(%d, %d) is a hit!", row, col);
		coutMessage = string(buf);
		printf(buf);
		if (checkIfSunk(*(shipList[pos_ship(sunk_ship_code)])))
		{
			char buf[500];
			snprintf(buf, 500, "%s is sunk!", shipList[pos_ship(sunk_ship_code)]->getName().c_str());
			coutMessage = string(buf);
			printf(buf);
		}
	}

	return true;
}

bool Board::checkIfSunk(Ship& ship)
{
	for (int r = 0; r < num_rows; r++) // for each row
	{
		for (int c = 0; c < num_cols; c++) // for each column
		{
			// check if there is any cell on the board for the type of ship that was hit
			if (sea[r][c] == ship.getID())	return false;
		}
	}

	// return true if sunk ship
	return true;
}

// checks if all ships on the board are sunk
bool Board::checkIfAllSunk()
{
	for (int i = 0; i < 5; i++) {
		if (shipList[i] == nullptr) return false;
		if (!(checkIfSunk(*(shipList[i])))) return false;
	}
	return true;
}

// desstructor	
Board::~Board()
{
	for (int i = 0; i < 5; i++)
		if (shipList[i] != nullptr) delete shipList[i];
}

// position of ship within the array depending on ID
int Board::pos_ship(char id)
{
	if (id == 'c') return 0;
	if (id == 'b') return 1;
	if (id == 'r') return 2;
	if (id == 's') return 3;
	if (id == 'd') return 4;
}

// move to next cell depending on direction
void Board::adjacent_cell(int* r, int* c, int dir)
{
	if (dir == 1) (*c)--;  // left
	if (dir == 2) (*c)++;  // right
	if (dir == 3) (*r)--;  // up
	if (dir == 4) (*r)++;  // down
}

float Board::getCellSize()
{
	//calculates cell sizes and and board display
	float cellWidth = window->getSize().x / 23.0f;
	float cellHeight = window->getSize().y / 23.0f;
	float cellSize = std::min(cellWidth, cellHeight);
	return cellSize;
}

Vector2i Board::get_displayPos()
{
	float cellSize = getCellSize();
	float posY = (2.0 * window->getSize().y / 9);
	Vector2i player1BoardPos(cellSize * (1 + (11 * windowSide)), posY);
	return player1BoardPos;
}


// scan start position and output in pos
// returns direction pointed by mouse as well
int Board::scan_board_pos_dir(Vector2i& pos)
{
	bool startSelected = false;
	float cellSize = getCellSize();
	Vector2i displayPos = get_displayPos();
	sf::Vector2i mousePos;
	sf::RectangleShape highlight(sf::Vector2f(cellSize, cellSize));
	highlight.setFillColor(sf::Color(0, 255, 0, 100));
	highlight.setOutlineThickness(2);
	highlight.setOutlineColor(sf::Color::Black);

	int direction = 0;

	//loads background pic for gameplay (the ocean) 
	sf::Texture gameplayBackgroundTexture;
	if (!gameplayBackgroundTexture.loadFromFile("./resources/image-copy.png")) {
		cout << "Error: Unable to load gameplay background texture. Check file path." << endl;
		return 0;
	}
	sf::Sprite gameplayBackground(gameplayBackgroundTexture);

	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}

			//detecting mouse 
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				mousePos = sf::Mouse::getPosition(*window);

				int col = static_cast<int>((mousePos.x - displayPos.x) / cellSize);
				int row = static_cast<int>((mousePos.y - displayPos.y) / cellSize);

				if (row >= 0 && row < get_num_rows() && col >= 0 && col < get_num_cols()) {
					if (!startSelected) {
						//set start position 
						pos.x = row;
						pos.y = col;
						startSelected = true;

						std::cout << "Start position selected at (" << row << ", " << col << ")" << std::endl;
						coutMessage = "Pick a Direction";

					}
					else {
						//second click detemrines direction of ship 
						//int newCol = static_cast<int>((mousePos.x - displayPos.x) / cellSize);
						//int newRow = static_cast<int>(std::round((mousePos.y - displayPos.y) / cellSize));
						if (row == pos.x && col < pos.y) {
							direction = 1; //left
						}
						else if (row == pos.x && col > pos.y) {
							direction = 2; //right
						}
						else if (col == pos.y && row < pos.x) {
							direction = 3; //up
						}
						else if (col == pos.y && row > pos.x) {
							direction = 4; //down
						}

						if (direction != 0) {
							std::cout << "Direction selected: " << direction << std::endl;
							return direction;
						}
						else {
							std::cout << "Invalid direction. Please click a valid adjacent cell." << std::endl;
							coutMessage = "Invalid direction. Click a cell in the same row or column.";
						}
					}
				}
				else {
					std::cout << "Invalid click. Please select a cell within the grid." << std::endl;
					coutMessage = "Invalid click. Please select a cell within the grid.";
				}
			}
		}

		window->clear();
		window->draw(gameplayBackground);
		displayBoard();
		if (startSelected) {
			highlight.setPosition(displayPos.x + pos.y * cellSize, displayPos.y + pos.x * cellSize);
			window->draw(highlight);
		}
		window->display();
	}

	return direction;
}

// place ship for humans
void Board::placeShipManual(Ship& ship)
{
	Vector2i pos;
	bool validPlacement = false;

	hiddenBoard = false;

	while (!validPlacement) {

		coutMessage = string("Pick Start Cell for ") + ship.getName();

		ship.setDirection(scan_board_pos_dir(pos));
		ship.setStartPos(pos);

		if (placeShip(&ship)) {
			validPlacement = true;
		}
		else {
			std::cout << "Invalid placement. Try again!" << std::endl;
			coutMessage = "Invalid placement. Try again!";
		}

	}
}


void Board::highlightCells(int size, sf::Vector2i mousePos, int dir)
{
	float cellSize = getCellSize();
	Vector2i displayPos = get_displayPos();

	int col = (mousePos.x - displayPos.x) / cellSize;
	int row = (mousePos.y - displayPos.y) / cellSize;
	for (int i = 0; i < size; i++) {
		sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
		cell.setPosition(
			displayPos.x + (col + (dir == 2 ? i : (dir == 1 ? -i : 0))) * cellSize,
			displayPos.y + (row + (dir == 4 ? i : (dir == 3 ? -i : 0))) * cellSize
		);
		cell.setFillColor(sf::Color(0, 255, 0, 100));
		cell.setOutlineThickness(1);
		cell.setOutlineColor(sf::Color::Black);
		window->draw(cell);
	}
}


void Board::playTurnForHuman()
{
	float cellSize = getCellSize();
	Vector2i displayPos = get_displayPos();

	bool validShot = false;

	while (!validShot && window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
				//int col = static_cast<int>(std::round((mousePos.x - displayPos.x) / cellSize));
				//int row = static_cast<int>(std::round((mousePos.y - displayPos.y) / cellSize));
				int col = static_cast<int>((mousePos.x - displayPos.x) / cellSize);
				int row = static_cast<int>((mousePos.y - displayPos.y) / cellSize);

				if (row >= 0 && row < get_num_rows() &&
					col >= 0 && col < get_num_cols()) {
					validShot = shootPosition(row, col);
					if (!validShot) {
						std::cout << "Invalid shot. Try again!" << std::endl;
						coutMessage = string("Invalid shot. Try again!");
					}
				}
			}
		}

	}
}

// returns number of shots tried on this board
int Board::get_numOfShots()
{
	int count = 0;
	for (int r = 0; r < num_rows; r++) // for each row
	{
		for (int c = 0; c < num_cols; c++) // for each column
		{
			// check if position was already shot before
			if (sea[r][c] == 'm' || sea[r][c] == '*') count++;
		}
	}
	return count;
}