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

            if (!texture.loadFromFile(imagePath)) {
                cout << "Failed to load texture from file: " << imagePath << endl;
            }
            else {
                cout << "Texture loaded successfully from file: " << imagePath << endl;
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
        window.draw(sprite);
    }

    sf::Text text;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "DSA FINAL");

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
    buttons.emplace_back(25, 500, 250, 150, font, "TOP 5:\n1. Orlando Magic\n2. LA Lakers\n3. Miami Heat\n4. LA Lakers\n5. Orlando Magic");
    buttons.emplace_back(525, 500, 250, 150, font, "BOTTOM 5");
    buttons.emplace_back(150, 30, 500, 50, font, "PLEASE SELECT AN OPTION FROM DOWN BELOW");
    buttons.emplace_back(300, 525, 200, 100, font, "Merge Sort:\nSelection Sort:");

    buttons.emplace_back(80, 100, 640, 390,font,"bruh", "map.png");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    int x = mouse.x;
                    int y = mouse.y;
                    cout << x << endl;
                    cout << y << endl;
                    for (auto& button : buttons) {
                        if (button.isMouseOver(window)) {
                            std::cout << "Button clicked: " << button.text.getString().toAnsiString() << std::endl;
                            buttons.emplace_back(x, y, 17, 25,font,"", "pin.png");
                        }
                    }
                }
            }
        }
        sf::Color color(151, 151, 151);
        window.clear(color);
        for (auto& button : buttons) {
            button.draw(window);
        }
        window.display();
    }

    return 0;
}


/*
Trailblazers: (111, 131)
Warriors: (98, 236)
Kings: (106, 220)
Clippers: (124, 291)
Lakers: (115, 275)
Suns: (204, 321)
Jazz: (216, 221)
Nuggets: (307, 245)
OKC: (379, 306)
Timberwolves: (407, 149)
Bucks: (485, 197)
Bulls: (484, 211)
Pacers: (507, 248)
Pistons: (536, 197)
Cavs: (555, 206)
Toronto: (578, 175)
Mavs: (384, 344)
Spurs: (360, 385)
Rockets: (410, 388)
Pelicans: (473, 377)
Grizzlies: (476, 303)
Hawks: (536, 316)
Magic: (595, 389)
Heat: (613, 410)
Hornets: (587, 298)
Wizards: (625, 239)
Sixers: (644, 222)
Nets: (664, 205)
Knicks: (651, 202)
Celtics: (676, 184)
*/