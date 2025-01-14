/***********************************************************************
* Programmer: Alba Raya Sanchez
* Class : CptS 122, Fall 2024; Lab Section 3
* Programming Assignment 9 - Battle Ship Game
* Date : December 4, 2024
* Description :
***********************************************************************/

#include "BattleShipAppClass.hpp"

enum status
{
    START, PLAYER1_SETUP, PLAYER2_SETUP, BOARD1_SETUP, BOARD2_SETUP, GAMEPLAY, OVER
};

// constructor
BattleShipApp::BattleShipApp()
{
    // Seed the random number generator with the current time
    srand((unsigned int)time(0));

    player1 = nullptr;
    player2 = nullptr;
}

// runs the application
void BattleShipApp::runApp()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "BATTLESHIP", sf::Style::Close);
    Menu menu(&window);
    MenuPlayerSetUp menuSetUpPlayer1(&window, string("PLAYER #1"));
    MenuPlayerSetUp menuSetUpPlayer2(&window, string("PLAYER #2"));

    status currentState = START;

    Player* current_player = nullptr;

    //load background pic for menu
    sf::Texture menuBackgroundTexture;
    if (!menuBackgroundTexture.loadFromFile("./resources/main-menu.png")) {
        cout << "Error: Unable to load menu background texture. Check file path." << endl;
        return;
    }
    sf::Sprite menuBackground(menuBackgroundTexture);


    //loads background pic for gameplay (the ocean) 
    sf::Texture gameplayBackgroundTexture;
    if (!gameplayBackgroundTexture.loadFromFile("./resources/image-copy.png")) {
        cout << "Error: Unable to load gameplay background texture. Check file path." << endl;
        return;
    }
    sf::Sprite gameplayBackground(gameplayBackgroundTexture);

    /*
    //calculates cell sizes and and board display
    float cellWidth = window.getSize().x / 23.0f;
    float cellHeight = window.getSize().y / 23.0f;
    float cellSize = std::min(cellWidth, cellHeight);
    Vector2i player1BoardPos(cellSize, cellSize);
    Vector2i player2BoardPos(cellSize*12, cellSize);
    */

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (currentState == OVER && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) window.close();
                else currentState = START; // starts a new round
            }
        }

        switch (currentState)
        {
        case START:
            menu.mouseHover();
            window.clear();
            window.draw(menuBackground);
            menu.render();
            window.display();

            if (menu.handleEvent(event))
            {
                currentState = PLAYER1_SETUP;
                cout << "button was clicked - switching to player 1 setup window." << endl;
            }
            break;

        case PLAYER1_SETUP:
            if (menuSetUpPlayer1.handleEvent(event))
            {
                currentState = PLAYER2_SETUP;
                cout << "button was clicked - switching to player 2 setup window." << endl;
                createPlayer(&player1, menuSetUpPlayer1);
                player1->get_board().set_window(window);
                player1->get_board().set_window_side(0);
            }
            menuSetUpPlayer1.updateHoverEffect();
            window.clear(sf::Color::Blue);
            menuSetUpPlayer1.render();
            window.display();
            break;

        case PLAYER2_SETUP:
            if (menuSetUpPlayer2.handleEvent(event))
            {
                currentState = BOARD1_SETUP;
                cout << "button was clicked \n switching to gameplay window." << endl;
                createPlayer(&player2, menuSetUpPlayer2);
                player2->get_board().set_window(window);
                player2->get_board().set_window_side(1);
                player1->set_otherPlayer(player2);
                player2->set_otherPlayer(player1);
            }
            menuSetUpPlayer2.updateHoverEffect();
            window.clear(sf::Color::Blue);
            menuSetUpPlayer2.render();
            window.display();
            break;

        case BOARD1_SETUP:
            player1->placeAllShips();
            currentState = BOARD2_SETUP;
            break;

        case BOARD2_SETUP:
            player2->placeAllShips();
            currentState = GAMEPLAY;

            current_player = nullptr;

            cout << "Starting gameplay..." << endl;

            ////resize window so both user and computers grids are visible to user
            //window.setSize(sf::Vector2u(1000, 1000));

            break;

        case GAMEPLAY:
            //clear window, set background picture
            window.clear();
            window.draw(gameplayBackground);

            // starting game
            if (current_player == nullptr)
            {
                if (rand() % 2) current_player = player1;
                else current_player = player1;
                player1->get_board().set_hiddenBoard(player2->canPeek());
                player2->get_board().set_hiddenBoard(player1->canPeek());
                current_player->get_board().set_message(string("Congrats! You Start!"));
                current_player->get_otherPlayer()->get_board().set_message(string("Where do you want to shoot?"));
            }
            // game already started
            else
            {
                current_player->playTurn();
                if (current_player->checkIfWinner())
                {
                    cout << current_player->get_name() << " wins!" << endl;
                    string msg = current_player->get_name() + string(" wins!");
                    current_player->get_board().set_message(msg);
                    currentState = OVER;
                }
                else
                {
                    current_player = current_player->get_otherPlayer();
                    string msg = current_player->get_name() + string(", where do you want to shoot?");
                    current_player->get_otherPlayer()->get_board().set_message(msg);
                }
            }

            current_player->get_board().displayBoard();
            current_player->get_otherPlayer()->get_board().displayBoard();

            if (currentState == OVER)
            {
                sf::Font font;
                if (!font.loadFromFile("./resources/sansation.ttf")) {
                    cout << "Error: Unable to load font for game over screen. Check file path." << endl;
                    return;
                }

                sf::Text gameOverMsg;
                gameOverMsg.setFont(font);
                gameOverMsg.setCharacterSize(30);
                gameOverMsg.setFillColor(sf::Color::Red);
                gameOverMsg.setString("Press any key to continue");
                gameOverMsg.setPosition(window.getSize().x * 0.300, window.getSize().x * 0.900);
                window.draw(gameOverMsg);
            }

            window.display();
            Sleep(50);
            if (currentState == OVER) waitForKey(window);
            break;

        case OVER:

            window.clear();
            sf::Font font;
            if (!font.loadFromFile("./resources/minecraft.ttf")) {
                cout << "Error: Unable to load font for game over screen. Check file path." << endl;
                return;
            }

            sf::Text gameOverText;
            sf::Text gameOverMsg;

            gameOverText.setFont(font);
            gameOverText.setCharacterSize(80);
            gameOverText.setFillColor(sf::Color::White);
            gameOverText.setString("Game Over!");
            gameOverText.setPosition(window.getSize().x * 0.250, window.getSize().x * 0.300);
            window.draw(gameOverText);

            gameOverMsg.setFont(font);
            gameOverMsg.setCharacterSize(30);
            gameOverMsg.setFillColor(sf::Color::White);
            gameOverMsg.setString("Press ESC to Quit or Enter for New Game");
            gameOverMsg.setPosition(window.getSize().x * 0.180, window.getSize().x * 0.400);
            window.draw(gameOverMsg);

            window.display();
            break;
        }
    }
}

// destructor
BattleShipApp::~BattleShipApp()
{
    if (player1 != nullptr) delete player1;
    if (player2 != nullptr) delete player2;
}

// instantiates an object for the player based on its setup menu
void BattleShipApp::createPlayer(Player** player, MenuPlayerSetUp& menu)
{
    if (*player != nullptr) delete (*player);
    if (menu.getTypePlayer() == 0) (*player) = new Human();
    if (menu.getTypePlayer() == 1) (*player) = new Computer();
    if (menu.getTypePlayer() == 2) (*player) = new Computer(); //new Remote(); // Remote class not implemented yet

    (*player)->set_name(menu.getPlayerName());
}

void BattleShipApp::waitForKey(sf::RenderWindow& window)
{
    while (window.isOpen())
    {
        sf::Event event;
        window.waitEvent(event);

        if (event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::KeyPressed) break;
    }
}