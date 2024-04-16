#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;

class Button {
private:
    sf::RectangleShape shape;
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Button(float x, float y, float width, float height, sf::Font& font, std::string text, std::string imagePath = "") {
        shape.setPosition(sf::Vector2f(x, y));
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(sf::Color::White);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(2.0f);

        this->text.setFont(font);
        this->text.setString(text);
        this->text.setCharacterSize(20);
        this->text.setFillColor(sf::Color::Black);
        sf::FloatRect textBounds = this->text.getLocalBounds();
        this->text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        this->text.setPosition(sf::Vector2f(x + width / 2.0f, y + height / 2.0f));

        if (!imagePath.empty()) {
            cout << "Hello" << endl;
            if (!texture.loadFromFile(imagePath)) {
                std::cout << "Failed to load texture from file: " << imagePath << std::endl;
            }
            sprite.setTexture(texture);
            sprite.setPosition(sf::Vector2f(x, y));
            sprite.setScale(width / texture.getSize().x, height / texture.getSize().y);
        }
    }


    bool isMouseOver(sf::RenderWindow& window) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        return shape.getGlobalBounds().contains(mousePos);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }

    sf::Text text;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Buttons");

    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    std::vector<Button> buttons;
    buttons.emplace_back(50, 670, 200, 50, font, "Button 1");
    buttons.emplace_back(300, 670, 200, 50, font, "Button 2");
    buttons.emplace_back(550, 670, 200, 50, font, "Button 3");
    buttons.emplace_back(50, 735, 200, 50, font, "Button 4");
    buttons.emplace_back(300, 735, 200, 50, font, "Button 5");
    buttons.emplace_back(550, 735, 200, 50, font, "Button 6");
    buttons.emplace_back(100, 500, 250, 150, font, "TOP 5\n1. Orlando Magic\n2. LA Lakers\n3. Miami Heat\n4. LA Lakers\n5. Orlando Magic");
    buttons.emplace_back(450, 500, 250, 150, font, "BOTTOM 5");

    buttons.emplace_back(90, 60, 620, 410,font,"", "Map.png");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (auto& button : buttons) {
                        if (button.isMouseOver(window)) {
                            std::cout << "Button clicked: " << button.text.getString().toAnsiString() << std::endl;
                            // You can add specific actions for each button here
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        for (auto& button : buttons) {
            button.draw(window);
        }
        window.display();
    }

    return 0;
}