#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {
private:
    sf::RenderWindow* window;
    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    sf::Font font;
    sf::Text startText;
    sf::RectangleShape startButton;

public:
    Menu(sf::RenderWindow* win) : window(win) {
        if (!bgTexture.loadFromFile("C:/Users/matthewbarnes/source/repos/PA9/PA9/assets/main-menu.png")) {
            throw std::runtime_error("Unable to load background, check file path.");
        }
        bgSprite.setTexture(bgTexture);

        if (!font.loadFromFile("C:/Users/matthewbarnes/source/repos/PA9/PA9/assets/minecraft.ttf")) {
            throw std::runtime_error("Unable to load font, check file path.");
        }

        startText.setFont(font);
        startText.setString("START");
        startText.setCharacterSize(30);
        startText.setFillColor(sf::Color::White);

        float padding = 20.0f;
        sf::FloatRect textBounds = startText.getLocalBounds();
        startButton.setSize(sf::Vector2f(textBounds.width + 2 * padding, textBounds.height + 2 * padding));
        startButton.setFillColor(sf::Color::Yellow);
        startButton.setOutlineThickness(9.0f);
        startButton.setOutlineColor(sf::Color::Black);

        float buttonX = (window->getSize().x - startButton.getSize().x) / 2;
        float buttonY = (4.0f * static_cast<float>(window->getSize().y) / 5.0f) - (static_cast<float>(startButton.getSize().y) / 2.0f);        startButton.setPosition(buttonX, buttonY);
        startText.setPosition(
            startButton.getPosition().x + padding,
            startButton.getPosition().y + padding
        );
    }

    void render() {
        window->draw(bgSprite);
        window->draw(startButton);
        window->draw(startText);
    }

    bool handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
            if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                std::cout << "Starting game\n";
                return true;
            }
        }
        return false;
    }

    void mouseHover() {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
        if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
            startButton.setFillColor(sf::Color::Red);
            startText.setFillColor(sf::Color::Black);
        }
        else {
            startButton.setFillColor(sf::Color::Yellow);
            startText.setFillColor(sf::Color::Black);
        }
    }
};