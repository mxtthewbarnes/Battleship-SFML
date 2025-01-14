
#pragma once

#include <Windows.h>
#include <SFML/Graphics.hpp>

// toggle button class
class ToggleButton
{
public:
    ToggleButton(const std::string& label)
    {
        buttonText.setString(label);
        isOn = false;

        button.setSize(sf::Vector2f(300, 50));
        button.setFillColor(sf::Color::Red); // Initial color
        button.setOutlineThickness(3.0f);
        button.setOutlineColor(sf::Color::Black);

        // Set up the text
        font.loadFromFile("./resources/Minecraft.ttf");
        buttonText.setFont(font);
        buttonText.setString(label);
        buttonText.setCharacterSize(24);
        buttonText.setFillColor(sf::Color::White);
    }

    void toggle()
    {
        isOn = !isOn;
        changeColor(true);
    }

    void changeColor(bool real)
    {
        //if ( (isOn && !hover) || (!isOn && hover) ) 
        if (isOn)
        {
            button.setFillColor(sf::Color::Green); // Change color when on
        }
        else
        {
            button.setFillColor(sf::Color::Red); // Change color when off
        }
        if (!real) button.setFillColor(sf::Color::Magenta); // Change color when hovering over button

        buttonText.setFillColor(sf::Color::White);
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(button);
        window.draw(buttonText);
    }

    bool isClicked(sf::RenderWindow& window)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // Check if the mouse click is within the button bounds
        return button.getGlobalBounds().contains(sf::Vector2f(mousePos));
    }

    void setPosition(float x, float y)
    {
        button.setPosition(x, y);
        buttonText.setPosition(x + 10, y + 10);
    }

    void updateHoverEffect(sf::RenderWindow& window)
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
        {
            changeColor(false);
        }
        else
        {
            changeColor(true);
        }
    }

    bool checkIfOn()
    {
        return isOn;
    }

    void setOn(bool value)
    {
        isOn = value;
        changeColor(true);
    }


private:
    sf::RectangleShape button;
    sf::Text buttonText;
    sf::Font font;
    bool isOn;
};
