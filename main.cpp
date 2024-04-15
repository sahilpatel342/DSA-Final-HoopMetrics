#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Button {
private:
    sf::RectangleShape shape;
public:
    Button(float x, float y, float width, float height, sf::Font& font, std::string text) {
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
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    std::vector<Button> buttons;
    buttons.emplace_back(50, 650, 200, 50, font, "Button 1");
    buttons.emplace_back(300, 650, 200, 50, font, "Button 2");
    buttons.emplace_back(550, 650, 200, 50, font, "Button 3");
    buttons.emplace_back(50, 725, 200, 50, font, "Button 4");
    buttons.emplace_back(300, 725, 200, 50, font, "Button 5");
    buttons.emplace_back(550, 725, 200, 50, font, "Button 6");
    buttons.emplace_back(100, 450, 250, 150, font, "TOP 5\n1. Orlando Magic\n2. LA Lakers\n3. Miami Heat\n4. LA Lakers\n5. Orlando Magic");
    buttons.emplace_back(450, 450, 250, 150, font, "BOTTOM 5");

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