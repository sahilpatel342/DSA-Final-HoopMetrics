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

// Function to get the coordinates of a specified team
vector<int> get_team_coordinates(const string& team_name) {
    // Map storing the team names as keys and their corresponding coordinates as values
    map<string, pair<int, int>> team_coordinates = {
            {"Trail Blazers", {111, 131}},
            {"Warriors", {98, 236}},
            {"Kings", {106, 220}},
            {"Clippers", {124, 291}},
            {"Lakers", {115, 275}},
            {"Suns", {204, 321}},
            {"Jazz", {216, 221}},
            {"Nuggets", {307, 245}},
            {"Thunder", {379, 306}},
            {"Timberwolves", {407, 149}},
            {"Bucks", {485, 197}},
            {"Bulls", {484, 211}},
            {"Pacers", {507, 248}},
            {"Pistons", {536, 197}},
            {"Cavs", {555, 206}},
            {"Raptors", {578, 175}},
            {"Mavericks", {384, 344}},
            {"Spurs", {360, 385}},
            {"Rockets", {410, 388}},
            {"Pelicans", {473, 377}},
            {"Grizzlies", {476, 303}},
            {"Hawks", {536, 316}},
            {"Magic", {595, 389}},
            {"Heat", {613, 410}},
            {"Hornets", {587, 298}},
            {"Wizards", {625, 239}},
            {"76ers", {644, 222}},
            {"Nets", {664, 205}},
            {"Knicks", {651, 202}},
            {"Celtics", {676, 184}}
    };

    // Find the coordinates for the specified team
    auto it = team_coordinates.find(team_name);

    // If the team is found, return the coordinates as a vector
    if (it != team_coordinates.end()) {
        return {it->second.first, it->second.second};
    } else {
        // If the team is not found, return an empty vector
        return {};
    }
}


int main() {

    std::unordered_map<std::string, Team> teams;
    std::vector<Game> games;

    load_teams("teams.csv", teams);
    load_games("games.csv", games);

    std::vector<string> FGP_list_merge;
    std::vector<string> FGP_list_min;
    string FGP_merge_time;
    string FGP_min_time;
    vector<pair<string, float>> FGP_data = computeAndSortFG(games);
    for (int i = 0; i < 5; i++) {
        FGP_list_merge[i] = FGP_data[i].first;
    }
    for (int i = 5; i < 10; i++) {
        FGP_list_merge[i] = FGP_data[i].first;
    }
    FGP_merge_time = FGP_data[10].second;
    FGP_min_time = FGP_data[10].second;

    std::vector<string> regular_season_list_merge;
    std::vector<string> regular_season_list_min;
    string regular_season_merge_time;
    string regular_season_min_time;
    vector<pair<string, float>> regular_season_data = computeAndSortWins(games);
    for (int i = 0; i < 5; i++) {
        FGP_list_merge[i] = regular_season_data[i].first;
    }
    for (int i = 5; i < 10; i++) {
        FGP_list_merge[i] = regular_season_data[i].first;
    }
    FGP_merge_time = regular_season_data[10].second;
    FGP_min_time = regular_season_data[10].second;

    std::vector<string> FTP_list_merge;
    std::vector<string> FTP_list_min;
    string FTP_merge_time;
    string FTP_min_time;
    vector<pair<string, float>> FTP_data = computeAndSortFG(games);
    for (int i = 0; i < 5; i++) {
        FGP_list_merge[i] = FTP_data[i].first;
    }
    for (int i = 5; i < 10; i++) {
        FGP_list_merge[i] = FTP_data[i].first;
    }
    FGP_merge_time = FTP_data[10].second;
    FGP_min_time = FTP_data[10].second;

    std::vector<string> PD_list_merge;
    std::vector<string> PD_list_min;
    string PD_merge_time;
    string PD_min_time;
    vector<pair<string, float>> PD_data = computeAndSortPointDiff(games);
    for (int i = 0; i < 5; i++) {
        FGP_list_merge[i] = PD_data[i].first;
    }
    for (int i = 5; i < 10; i++) {
        FGP_list_merge[i] = PD_data[i].first;
    }
    FGP_merge_time = PD_data[10].second;
    FGP_min_time = PD_data[10].second;



    //std::vector<string> regular_season_list_merge = {"Magic", "Heat", "Warriors", "Lakers", "Pacers"};
    //std::vector<string> regular_season_list_min = {"Hornets", "Pistons", "Wizards", "Warriors", "Jazz"};

    //std::vector<string> FTP_list_merge = {"Hawks", "Thunder", "Rockets", "Spurs", "Jazz"};
    //std::vector<string> FTP_list_min = {"Suns", "Pistons", "Wizards", "Warriors", "Pelicans"};

    //std::vector<string> PD_list_merge = {"Kings", "Pistons", "Wizards", "Celtics", "Jazz"};
    //std::vector<string> PD_list_min = {"Raptors", "76ers", "Wizards", "Bucks", "Timberwolves"};

    //std::vector<string> FGP_list_merge = {"Mavericks", "Pistons", "Knicks", "Warriors", "Jazz"};
    //std::vector<string> FGP_list_min = {"Trail Blazers", "Bulls", "Wizards", "Warriors", "76ers"};

    string currentSelection = "Regular Season Wins";

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
            buttons.emplace_back(300, 525, 200, 100, font, "Merge Sort: " + regular_season_merge_time + "\nMin Heap:" + regular_season_min_time);
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
            buttons.emplace_back(300, 525, 200, 100, font, "Merge Sort: " + FGP_merge_time + "\nMin Heap:" + FGP_min_time);
            buttons.emplace_back(0, 660, 800, 1, font, "");
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
            buttons.emplace_back(300, 525, 200, 100, font, "Merge Sort: " + PD_merge_time + "\nMin Heap:" + PD_min_time);
            buttons.emplace_back(0, 660, 800, 1, font, "");
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
            buttons.emplace_back(300, 525, 200, 100, font, "Merge Sort: " + FTP_merge_time + "\nMin Heap:" + FTP_min_time);
            buttons.emplace_back(0, 660, 800, 1, font, "");
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
        sf::Color colorGray(151, 151, 151);
        sf::Color colorGreen(56, 206, 0);
        sf::Color colorYellow(240, 232, 0);
        window.clear(colorGray);
        for (auto& button : buttons) {
            button.draw(window);
        }
        if (currentSelection == "Regular Season Wins") {
            sf::CircleShape circle1(15);
            sf::CircleShape circle2(15);
            sf::CircleShape circle3(15);
            sf::CircleShape circle4(15);
            sf::CircleShape circle5(15);

            // Set the fill color of the circle to blue
            circle1.setFillColor(colorGreen);
            circle2.setFillColor(colorGreen);
            circle3.setFillColor(colorGreen);
            circle4.setFillColor(colorGreen);
            circle5.setFillColor(colorGreen);

            // Set the position of the circle (x, y) coordinates
            vector<int> coordinates1 = get_team_coordinates(regular_season_list_merge[0]);
            circle1.setPosition(coordinates1[0], coordinates1[1]);
            window.draw(circle1);

            vector<int> coordinates2 = get_team_coordinates(regular_season_list_merge[1]);
            circle2.setPosition(coordinates2[0], coordinates2[1]);
            window.draw(circle2);

            vector<int> coordinates3 = get_team_coordinates(regular_season_list_merge[2]);
            circle3.setPosition(coordinates3[0], coordinates3[1]);
            window.draw(circle3);

            vector<int> coordinates4 = get_team_coordinates(regular_season_list_merge[3]);
            circle4.setPosition(coordinates4[0], coordinates4[1]);
            window.draw(circle4);

            vector<int> coordinates5 = get_team_coordinates(regular_season_list_merge[4]);
            circle5.setPosition(coordinates5[0], coordinates5[1]);
            window.draw(circle5);


            sf::CircleShape circle6(15);
            sf::CircleShape circle7(15);
            sf::CircleShape circle8(15);
            sf::CircleShape circle9(15);
            sf::CircleShape circle10(15);

            // Set the fill color of the circle to blue
            circle6.setFillColor(sf::Color::Red);
            circle7.setFillColor(sf::Color::Red);
            circle8.setFillColor(sf::Color::Red);
            circle9.setFillColor(sf::Color::Red);
            circle10.setFillColor(sf::Color::Red);

            // Set the position of the circle (x, y) coordinates
            vector<int> coordinates6 = get_team_coordinates(regular_season_list_min[0]);
            circle6.setPosition(coordinates6[0], coordinates6[1]);
            window.draw(circle6);

            vector<int> coordinates7 = get_team_coordinates(regular_season_list_min[1]);
            circle7.setPosition(coordinates7[0], coordinates7[1]);
            window.draw(circle7);

            vector<int> coordinates8 = get_team_coordinates(regular_season_list_min[2]);
            circle8.setPosition(coordinates8[0], coordinates8[1]);
            window.draw(circle8);

            vector<int> coordinates9 = get_team_coordinates(regular_season_list_min[3]);
            circle9.setPosition(coordinates9[0], coordinates9[1]);
            window.draw(circle9);

            vector<int> coordinates10 = get_team_coordinates(regular_season_list_min[4]);
            circle10.setPosition(coordinates10[0], coordinates10[1]);
            window.draw(circle10);
        }
        else if (currentSelection == "Field Goal Percentage") {
            sf::CircleShape circle1(15);
            sf::CircleShape circle2(15);
            sf::CircleShape circle3(15);
            sf::CircleShape circle4(15);
            sf::CircleShape circle5(15);

            // Set the fill color of the circle to blue
            circle1.setFillColor(colorGreen);
            circle2.setFillColor(colorGreen);
            circle3.setFillColor(colorGreen);
            circle4.setFillColor(colorGreen);
            circle5.setFillColor(colorGreen);

            // Set the position of the circle (x, y) coordinates
            vector<int> coordinates1 = get_team_coordinates(FGP_list_merge[0]);
            circle1.setPosition(coordinates1[0], coordinates1[1]);
            window.draw(circle1);

            vector<int> coordinates2 = get_team_coordinates(FGP_list_merge[1]);
            circle2.setPosition(coordinates2[0], coordinates2[1]);
            window.draw(circle2);

            vector<int> coordinates3 = get_team_coordinates(FGP_list_merge[2]);
            circle3.setPosition(coordinates3[0], coordinates3[1]);
            window.draw(circle3);

            vector<int> coordinates4 = get_team_coordinates(FGP_list_merge[3]);
            circle4.setPosition(coordinates4[0], coordinates4[1]);
            window.draw(circle4);

            vector<int> coordinates5 = get_team_coordinates(FGP_list_merge[4]);
            circle5.setPosition(coordinates5[0], coordinates5[1]);
            window.draw(circle5);


            sf::CircleShape circle6(15);
            sf::CircleShape circle7(15);
            sf::CircleShape circle8(15);
            sf::CircleShape circle9(15);
            sf::CircleShape circle10(15);

            // Set the fill color of the circle to blue
            circle6.setFillColor(sf::Color::Red);
            circle7.setFillColor(sf::Color::Red);
            circle8.setFillColor(sf::Color::Red);
            circle9.setFillColor(sf::Color::Red);
            circle10.setFillColor(sf::Color::Red);

            // Set the position of the circle (x, y) coordinates
            vector<int> coordinates6 = get_team_coordinates(FGP_list_min[0]);
            circle6.setPosition(coordinates6[0], coordinates6[1]);
            window.draw(circle6);

            vector<int> coordinates7 = get_team_coordinates(FGP_list_min[1]);
            circle7.setPosition(coordinates7[0], coordinates7[1]);
            window.draw(circle7);

            vector<int> coordinates8 = get_team_coordinates(FGP_list_min[2]);
            circle8.setPosition(coordinates8[0], coordinates8[1]);
            window.draw(circle8);

            vector<int> coordinates9 = get_team_coordinates(FGP_list_min[3]);
            circle9.setPosition(coordinates9[0], coordinates9[1]);
            window.draw(circle9);

            vector<int> coordinates10 = get_team_coordinates(FGP_list_min[4]);
            circle10.setPosition(coordinates10[0], coordinates10[1]);
            window.draw(circle10);
        }
        else if (currentSelection == "Point Differential") {
            sf::CircleShape circle1(15);
            sf::CircleShape circle2(15);
            sf::CircleShape circle3(15);
            sf::CircleShape circle4(15);
            sf::CircleShape circle5(15);

            // Set the fill color of the circle to blue
            circle1.setFillColor(colorGreen);
            circle2.setFillColor(colorGreen);
            circle3.setFillColor(colorGreen);
            circle4.setFillColor(colorGreen);
            circle5.setFillColor(colorGreen);

            // Set the position of the circle (x, y) coordinates
            vector<int> coordinates1 = get_team_coordinates(PD_list_merge[0]);
            circle1.setPosition(coordinates1[0], coordinates1[1]);
            window.draw(circle1);

            vector<int> coordinates2 = get_team_coordinates(PD_list_merge[1]);
            circle2.setPosition(coordinates2[0], coordinates2[1]);
            window.draw(circle2);

            vector<int> coordinates3 = get_team_coordinates(PD_list_merge[2]);
            circle3.setPosition(coordinates3[0], coordinates3[1]);
            window.draw(circle3);

            vector<int> coordinates4 = get_team_coordinates(PD_list_merge[3]);
            circle4.setPosition(coordinates4[0], coordinates4[1]);
            window.draw(circle4);

            vector<int> coordinates5 = get_team_coordinates(PD_list_merge[4]);
            circle5.setPosition(coordinates5[0], coordinates5[1]);
            window.draw(circle5);


            sf::CircleShape circle6(15);
            sf::CircleShape circle7(15);
            sf::CircleShape circle8(15);
            sf::CircleShape circle9(15);
            sf::CircleShape circle10(15);

            // Set the fill color of the circle to blue
            circle6.setFillColor(sf::Color::Red);
            circle7.setFillColor(sf::Color::Red);
            circle8.setFillColor(sf::Color::Red);
            circle9.setFillColor(sf::Color::Red);
            circle10.setFillColor(sf::Color::Red);

            // Set the position of the circle (x, y) coordinates
            vector<int> coordinates6 = get_team_coordinates(PD_list_min[0]);
            circle6.setPosition(coordinates6[0], coordinates6[1]);
            window.draw(circle6);

            vector<int> coordinates7 = get_team_coordinates(PD_list_min[1]);
            circle7.setPosition(coordinates7[0], coordinates7[1]);
            window.draw(circle7);

            vector<int> coordinates8 = get_team_coordinates(PD_list_min[2]);
            circle8.setPosition(coordinates8[0], coordinates8[1]);
            window.draw(circle8);

            vector<int> coordinates9 = get_team_coordinates(PD_list_min[3]);
            circle9.setPosition(coordinates9[0], coordinates9[1]);
            window.draw(circle9);

            vector<int> coordinates10 = get_team_coordinates(PD_list_min[4]);
            circle10.setPosition(coordinates10[0], coordinates10[1]);
            window.draw(circle10);
        }
        else if (currentSelection == "Free Throw Percentage") {
            sf::CircleShape circle1(15);
            sf::CircleShape circle2(15);
            sf::CircleShape circle3(15);
            sf::CircleShape circle4(15);
            sf::CircleShape circle5(15);

            // Set the fill color of the circle to blue
            circle1.setFillColor(colorGreen);
            circle2.setFillColor(colorGreen);
            circle3.setFillColor(colorGreen);
            circle4.setFillColor(colorGreen);
            circle5.setFillColor(colorGreen);

            // Set the position of the circle (x, y) coordinates
            vector<int> coordinates1 = get_team_coordinates(FTP_list_merge[0]);
            circle1.setPosition(coordinates1[0], coordinates1[1]);
            window.draw(circle1);

            vector<int> coordinates2 = get_team_coordinates(FTP_list_merge[1]);
            circle2.setPosition(coordinates2[0], coordinates2[1]);
            window.draw(circle2);

            vector<int> coordinates3 = get_team_coordinates(FTP_list_merge[2]);
            circle3.setPosition(coordinates3[0], coordinates3[1]);
            window.draw(circle3);

            vector<int> coordinates4 = get_team_coordinates(FTP_list_merge[3]);
            circle4.setPosition(coordinates4[0], coordinates4[1]);
            window.draw(circle4);

            vector<int> coordinates5 = get_team_coordinates(FTP_list_merge[4]);
            circle5.setPosition(coordinates5[0], coordinates5[1]);
            window.draw(circle5);


            sf::CircleShape circle6(15);
            sf::CircleShape circle7(15);
            sf::CircleShape circle8(15);
            sf::CircleShape circle9(15);
            sf::CircleShape circle10(15);

            // Set the fill color of the circle to blue
            circle6.setFillColor(sf::Color::Red);
            circle7.setFillColor(sf::Color::Red);
            circle8.setFillColor(sf::Color::Red);
            circle9.setFillColor(sf::Color::Red);
            circle10.setFillColor(sf::Color::Red);

            // Set the position of the circle (x, y) coordinates
            vector<int> coordinates6 = get_team_coordinates(FTP_list_min[0]);
            circle6.setPosition(coordinates6[0], coordinates6[1]);
            window.draw(circle6);

            vector<int> coordinates7 = get_team_coordinates(FTP_list_min[1]);
            circle7.setPosition(coordinates7[0], coordinates7[1]);
            window.draw(circle7);

            vector<int> coordinates8 = get_team_coordinates(FTP_list_min[2]);
            circle8.setPosition(coordinates8[0], coordinates8[1]);
            window.draw(circle8);

            vector<int> coordinates9 = get_team_coordinates(FTP_list_min[3]);
            circle9.setPosition(coordinates9[0], coordinates9[1]);
            window.draw(circle9);

            vector<int> coordinates10 = get_team_coordinates(FTP_list_min[4]);
            circle10.setPosition(coordinates10[0], coordinates10[1]);
            window.draw(circle10);
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