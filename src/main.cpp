//GAME

//Initialasation

#include <SFML/Graphics.hpp>

const float WIDTH = 1000.f;
const float HEIGHT = 1600.f;

class Player {
public:
    sf::RectangleShape shape;

    Player() {
        shape.setSize(sf::Vector2f(20.f, 20.f));
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(50.f, 50.f);
    }

    void draw(sf::RenderWindow& window) {window.draw(shape);}
};

//Mainloop

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "2D Game");
    Player player;

    while (window.isOpen()) {
        player.draw(window);
        window.display();
        window.clear(sf::Color::Black);
    }
}