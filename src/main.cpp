//GAME

//Initialasation

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

//Window
const float WIDTH = 1000.f;
const float HEIGHT = 1600.f;


//Classes

class Player {
public:
    //Player Hitbox
    sf::RectangleShape shape;
    //If true Player will fall downwards
    bool touching_ground = false;
    //How fast the Player gains speed when falling
    const float gravity_force = 0.05f;
    //actual downspeed of Player
    float falling_speed= 0.f;
    //How fast the Player moves left and right
    const float movement_speed = 0.2f;
    //How strong the Player jumps upwards
    const float jump_force = -3.f;

    Player() {
        shape.setSize(sf::Vector2f(20.f, 20.f));
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(50.f, 50.f);
    }
    //Falling if not touching ground
    void gravity() {
        if (touching_ground == false) {
            falling_speed += gravity_force;
        } else {
            falling_speed = 0.f;
        }
        shape.move(0.f, falling_speed);
    }
    //This function should be called when player is touching ground
    void collides(int i) {
        if (i == 1) {
            touching_ground = true;
        } else {
            touching_ground = false;
        }
    }
    //Moves Player left and right
    void movement() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            shape.move(-movement_speed, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            shape.move(movement_speed, 0.f);
        }
    }
    //Lets Player jump while touching ground
    void jump() {
        if (touching_ground == true) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                touching_ground = false;
                falling_speed = jump_force;
            }
        }
    }
    //Draw Function für window logic
    void draw(sf::RenderWindow& window) {window.draw(shape);}
};

class Platform {
public:
    sf::RectangleShape shape; //Platform Hitbox

    Platform(const float x, const float y, const float width, const float height) {
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(x, y);
    }
    //Draw function for window logic
    void draw(sf::RenderWindow& window) {window.draw(shape);}
};

//Functions

bool collision(const sf::RectangleShape& a, const sf::RectangleShape& b) {return a.getGlobalBounds().intersects(b.getGlobalBounds());} //notices collision between 2 sf::RectangleShapes (Hitboxes)

void update_window(sf::RenderWindow& window) {
    sf::Event event; //For window poll logic
    //Closing window when Closing Button is pressed
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        }
    //Display everything
    window.display();
    window.clear(sf::Color::Black);
}

//Player function
//All Player Code Here
void update_player(sf::RenderWindow& window, Player& player) {
    player.draw(window);
    player.movement();
    player.jump();
    player.gravity();
}

//Platform function
//includes Player collision with platforms
void update_platforms(std::vector<Platform>& platforms, sf::RenderWindow& window, Player& player) {
    for (auto& platform : platforms) {
        if (collision(platform.shape, player.shape)) {
            player.collides(1);
        } else {
            player.collides(0);
        }
        platform.draw(window);
    }
}

//Mainloop

int main() {
    //Initialization 
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "2D Game");
    Player player;
    std::vector<Platform> platforms;

    //Test-Platform
    platforms.push_back(Platform(30.f, 70.f, 100.f, 10.f));

    //Calling update functions while window not closed
    while (window.isOpen()) {
        update_player(window, player);
        update_platforms(platforms, window, player);
        update_window(window);
    }
    //End of the Code
    return 0;
}
