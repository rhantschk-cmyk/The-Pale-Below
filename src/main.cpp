//GAME

//Initialasation

#include <SFML/Graphics.hpp>

const float WIDTH = 1000.f;
const float HEIGHT = 1600.f;



class Player {
public:
    sf::RectangleShape shape;
    bool touching_ground = false;
    const float gravity_force = 0.05f;
    float falling_speed= 0.f;

    Player() {
        shape.setSize(sf::Vector2f(20.f, 20.f));
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(50.f, 50.f);
    }

    void gravity() {
        if (touching_ground == false) {
            falling_speed += gravity_force;
        } else {
            falling_speed = 0.f;
        }
        shape.move(0.f, falling_speed);
    }

    void draw(sf::RenderWindow& window) {window.draw(shape);}
};

//Functions

void update_window(sf::RenderWindow& window) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        }
    window.display();
    window.clear(sf::Color::Black);
}

void update_player(sf::RenderWindow& window, Player& player) {
    player.draw(window);
    player.gravity();
}

//Mainloop

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "2D Game");
    Player player;

    while (window.isOpen()) {
        update_player(window, player);
        update_window(window);
    }
    return 0;
}