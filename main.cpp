#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "NBA_Data_Manip"

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

    std::unordered_map<std::string, Team> teams;
    std::vector<Game> games;

    std::vector<string> regular_season_list_merge = {"Magic", "Heat", "Warriors", "Lakers", "Pacers"};
    std::vector<string> regular_season_list_min = {"Hornets", "Pistons", "Wizards", "Warriors", "Jazz"};

    std::vector<string> FTP_list_merge = {"Hawks", "Thunder", "Rockets", "Spurs", "Jazz"};
    std::vector<string> FTP_list_min = {"Suns", "Pistons", "Wizards", "Warriors", "Pelicans"};

    std::vector<string> PD_list_merge = {"Kings", "Pistons", "Wizards", "Celtics", "Jazz"};
    std::vector<string> PD_list_min = {"Raptors", "76ers", "Wizards", "Bucks", "Timberwolves"};

    std::vector<string> FGP_list_merge = {"Mavericks", "Pistons", "Knicks", "Warriors", "Jazz"};
    std::vector<string> FGP_list_min = {"Trail Blazers", "Bulls", "Wizards", "Warriors", "76ers"};

    string currentSelection = "Regular Season Wins";

    load_teams("teams.csv", teams);
    //load_games("games.csv", games);

    //cout << games[0].home_team_id << endl;


    for (auto i = teams.begin(); i != teams.end(); i++) {
        cout << i->first << "-" << i->second.team_name << endl;
    }

    sf::RenderWindow window(sf::VideoMode(800, 800), "DSA FINAL");

    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    std::vector<Button> buttons;

    while (window.isOpen()) {

        if (currentSelection == "Regular Season Wins") {
            buttons.emplace_back(75, 670, 275, 50, font, "Regular Season Wins");
            buttons.emplace_back(75, 735, 275, 50, font, "Field Goal Percentage");
            buttons.emplace_back(450, 670, 275, 50, font, "Point Differential");
            buttons.emplace_back(450, 735, 275, 50, font, "Free Throw Percentage");
            buttons.emplace_back(25, 500, 250, 150, font, "TOP 5:\n1. " + regular_season_list_merge[0] + "\n2. " + regular_season_list_merge[1] + "\n3. " + regular_season_list_merge[2] + "\n4. " + regular_season_list_merge[3] + "\n5. " + regular_season_list_merge[4]);
            buttons.emplace_back(525, 500, 250, 150, font, "BOTTOM 5:\n1. " + regular_season_list_min[0] + "\n2. " + regular_season_list_min[1] + "\n3. " + regular_season_list_min[2] + "\n4. " + regular_season_list_min[3] + "\n5. " + regular_season_list_min[4]);
            buttons.emplace_back(150, 30, 500, 50, font, "PLEASE SELECT AN OPTION FROM DOWN BELOW");
            buttons.emplace_back(300, 525, 200, 100, font, "Merge Sort:\nSelection Sort:");
            buttons.emplace_back(0, 660, 800, 1, font, "");

            buttons.emplace_back(80, 100, 640, 390,font,"bruh", "map.png");
        }
        else if (currentSelection == "Field Goal Percentage") {
            buttons.emplace_back(75, 670, 275, 50, font, "Regular Season Wins");
            buttons.emplace_back(75, 735, 275, 50, font, "Field Goal Percentage");
            buttons.emplace_back(450, 670, 275, 50, font, "Point Differential");
            buttons.emplace_back(450, 735, 275, 50, font, "Free Throw Percentage");
            buttons.emplace_back(25, 500, 250, 150, font, "TOP 5:\n1. " + FGP_list_merge[0] + "\n2. " + FGP_list_merge[1] + "\n3. " + FGP_list_merge[2] + "\n4. " + FGP_list_merge[3] + "\n5. " + FGP_list_merge[4]);
            buttons.emplace_back(525, 500, 250, 150, font, "BOTTOM 5:\n1. " + FGP_list_min[0] + "\n2. " + FGP_list_min[1] + "\n3. " + FGP_list_min[2] + "\n4. " + FGP_list_min[3] + "\n5. " + FGP_list_min[4]);
            buttons.emplace_back(150, 30, 500, 50, font, "PLEASE SELECT AN OPTION FROM DOWN BELOW");
            buttons.emplace_back(300, 525, 200, 100, font, "Merge Sort:\nSelection Sort:");

            buttons.emplace_back(80, 100, 640, 390,font,"bruh", "map.png");
        }
        else if (currentSelection == "Point Differential") {
            buttons.emplace_back(75, 670, 275, 50, font, "Regular Season Wins");
            buttons.emplace_back(75, 735, 275, 50, font, "Field Goal Percentage");
            buttons.emplace_back(450, 670, 275, 50, font, "Point Differential");
            buttons.emplace_back(450, 735, 275, 50, font, "Free Throw Percentage");
            buttons.emplace_back(25, 500, 250, 150, font, "TOP 5:\n1. " + PD_list_merge[0] + "\n2. " + PD_list_merge[1] + "\n3. " + PD_list_merge[2] + "\n4. " + PD_list_merge[3] + "\n5. " + PD_list_merge[4]);
            buttons.emplace_back(525, 500, 250, 150, font, "BOTTOM 5:\n1. " + PD_list_min[0] + "\n2. " + PD_list_min[1] + "\n3. " + PD_list_min[2] + "\n4. " + PD_list_min[3] + "\n5. " + PD_list_min[4]);
            buttons.emplace_back(150, 30, 500, 50, font, "PLEASE SELECT AN OPTION FROM DOWN BELOW");
            buttons.emplace_back(300, 525, 200, 100, font, "Merge Sort:\nSelection Sort:");

            buttons.emplace_back(80, 100, 640, 390,font,"bruh", "map.png");
        }

        else if (currentSelection == "Free Throw Percentage") {
            buttons.emplace_back(75, 670, 275, 50, font, "Regular Season Wins");
            buttons.emplace_back(75, 735, 275, 50, font, "Field Goal Percentage");
            buttons.emplace_back(450, 670, 275, 50, font, "Point Differential");
            buttons.emplace_back(450, 735, 275, 50, font, "Free Throw Percentage");
            buttons.emplace_back(25, 500, 250, 150, font, "TOP 5:\n1. " + FTP_list_merge[0] + "\n2. " + FTP_list_merge[1] + "\n3. " + FTP_list_merge[2] + "\n4. " + FTP_list_merge[3] + "\n5. " + FTP_list_merge[4]);
            buttons.emplace_back(525, 500, 250, 150, font, "BOTTOM 5:\n1. " + FTP_list_min[0] + "\n2. " + FTP_list_min[1] + "\n3. " + FTP_list_min[2] + "\n4. " + FTP_list_min[3] + "\n5. " + FTP_list_min[4]);
            buttons.emplace_back(150, 30, 500, 50, font, "PLEASE SELECT AN OPTION FROM DOWN BELOW");
            buttons.emplace_back(300, 525, 200, 100, font, "Merge Sort:\nSelection Sort:");

            buttons.emplace_back(80, 100, 640, 390,font,"bruh", "map.png");
        }

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
                            if (button.text.getString().toAnsiString() == "Regular Season Wins") {
                                currentSelection = "Regular Season Wins";
                            }
                            else if (button.text.getString().toAnsiString() == "Field Goal Percentage") {
                                currentSelection = "Field Goal Percentage";
                            }
                            else if (button.text.getString().toAnsiString() == "Point Differential") {
                                currentSelection = "Point Differential";
                            }
                            else if (button.text.getString().toAnsiString() == "Free Throw Percentage") {
                                currentSelection = "Free Throw Percentage";
                            }
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
        buttons.clear();
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