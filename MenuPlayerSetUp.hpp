/***********************************************************************
* Programmer: Alba Raya Sanchez
* Class : CptS 122, Fall 2024; Lab Section 3
* Programming Assignment 9 - Battle Ship Game
* Date : December 4, 2024
* Description :
***********************************************************************/

#pragma once

#include "ToggleButton.hpp"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class MenuPlayerSetUp {
private:
    sf::RenderWindow* window;
    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    sf::Font font;

    sf::Text menuCaptionText;

    sf::Text nameCaption;
    sf::Text nameText;
    sf::RectangleShape nameBox;

    string humanLabel = "Human Player";
    string computerLabel = "Computer";
    string remoteLabel = "Remote Player";
    ToggleButton humanButton;
    ToggleButton computerButton;
    ToggleButton remoteButton;

    sf::Text continuteText;
    sf::RectangleShape continueButton;

    string playerNumber;
    string playerName;
    string playerRemoteIP;
    int playerType;

public:
    MenuPlayerSetUp(sf::RenderWindow* win, string& playerID)
        : window(win), playerNumber(playerID),
        humanButton(humanLabel), computerButton(computerLabel), remoteButton(remoteLabel)
    {
        float posX = 0.0, posY = 0.0, padding = 0.0;
        sf::FloatRect textBounds;

        // initializes output variables
        playerType = 0;
        playerName = playerID;
        playerRemoteIP = "";

        // loads font
        if (!font.loadFromFile("./resources/Minecraft.ttf")) {
            throw std::runtime_error("Unable to load font, check file path.");
        }

        // caption
        menuCaptionText.setFont(font);
        menuCaptionText.setString(playerNumber);
        menuCaptionText.setCharacterSize(60);
        menuCaptionText.setFillColor(sf::Color::White);

        textBounds = menuCaptionText.getLocalBounds();
        posX = (window->getSize().x - textBounds.width) / 2;
        posY = (1 * window->getSize().y / 9) - (textBounds.height / 2);
        menuCaptionText.setPosition(posX, posY);

        // player name text box
        nameCaption.setFont(font);
        nameCaption.setString("NAME: ");
        nameCaption.setCharacterSize(30);
        nameCaption.setFillColor(sf::Color::White);

        textBounds = nameCaption.getLocalBounds();
        posX = (1 * window->getSize().x / 4) - (textBounds.width / 2);
        posY = (2 * window->getSize().y / 9) - (textBounds.height / 2);
        nameCaption.setPosition(posX, posY);

        padding = 15.0;
        nameBox.setSize(sf::Vector2f(400, 50));
        nameBox.setFillColor(sf::Color::White);
        nameBox.setOutlineThickness(2.0f);
        nameBox.setOutlineColor(sf::Color::Black);
        posX = posX + textBounds.width + padding;
        nameBox.setPosition(posX, posY);

        nameText.setFont(font);
        nameText.setString(playerName);
        nameText.setCharacterSize(30);
        nameText.setFillColor(sf::Color::Black);
        nameText.setPosition(nameBox.getPosition().x + padding, nameBox.getPosition().y);

        // toggle button options (human, computer, remote)
        posX = (1 * window->getSize().x / 2) - 150;
        posY = (3 * window->getSize().y / 9) - 25;
        humanButton.setPosition(posX, posY);
        posY = (4 * window->getSize().y / 9) - 25;
        computerButton.setPosition(posX, posY);
        posY = (5 * window->getSize().y / 9) - 25;
        remoteButton.setPosition(posX, posY);

        // human player by default
        humanButton.setOn(true);
        computerButton.setOn(false);
        remoteButton.setOn(false);

        // continue button
        continuteText.setFont(font);
        continuteText.setString("CONTINUE");
        continuteText.setCharacterSize(30);
        continuteText.setFillColor(sf::Color::Yellow);

        padding = 15.0f;
        textBounds = continuteText.getLocalBounds();
        continueButton.setSize(sf::Vector2f(textBounds.width + 2 * padding, textBounds.height + 2 * padding));
        continueButton.setFillColor(sf::Color::Black);
        continueButton.setOutlineThickness(9.0f);
        continueButton.setOutlineColor(sf::Color::Black);

        posX = (window->getSize().x - continueButton.getSize().x) / 2;
        posY = (8 * window->getSize().y / 9) - (continueButton.getSize().y / 2);
        continueButton.setPosition(posX, posY);
        continuteText.setPosition(continueButton.getPosition().x + padding, continueButton.getPosition().y + padding);
    }

    void render()
    {
        window->draw(bgSprite);

        window->draw(menuCaptionText);

        window->draw(nameCaption);
        window->draw(nameBox);
        window->draw(nameText);

        // toggle buttons
        humanButton.draw(*window);
        computerButton.draw(*window);
        remoteButton.draw(*