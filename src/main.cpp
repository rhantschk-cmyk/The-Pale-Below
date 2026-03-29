//GAME

//Initialasation

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

//Window
const float WIDTH = 1000.f;
const float HEIGHT = 1600.f;
const float CENTER_X = WIDTH / 2.f - 10.f;
const float CENTER_Y = HEIGHT / 2.f - 10.f;


//Classes

class Player {
public:
    //Player Hitbox
    sf::RectangleShape shape;
    //Player position from previous frame
    sf::Vector2f last_position;
    //If true Player will fall downwards
    bool touching_ground = false;
    //How fast the Player gains speed when falling
    const float gravity_force = 0.01f;
    //actual downspeed of Player
    float falling_speed= 0.f;
    //How fast the Player moves left and right
    const float movement_speed = 0.2f;
    //How strong the Player jumps upwards
    const float jump_force = -1.3f;
    //How strong the Player gets pushed upwards after taking damage
    const float damage_jump_force = -1.f;
    //How far the Player gets pushed away from an Enemy
    const float damage_knockback = 40.f;
    int health = 100;

    Player() {
        shape.setSize(sf::Vector2f(20.f, 20.f));
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(50.f, 50.f);
        last_position = shape.getPosition();
    }
    //Saves Player position before movement
    void save_last_position() {
        last_position = shape.getPosition();
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
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(x, y);
    }
    //Draw function for window logic
    void draw(sf::RenderWindow& window) {window.draw(shape);}
    //Moves Platform for screen scrolling
    void move(const float x, const float y) {shape.move(x, y);}
};

class Enemy {
public:
    sf::RectangleShape shape;
    int attack_cooldown = 120;

    Enemy(const float x, const float y) {
        shape.setSize(sf::Vector2f(20.f, 20.f));
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(x, y);
    }

    void draw(sf::RenderWindow& window) {window.draw(shape);}
    void move(const float x, const float y) {shape.move(x, y);}
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
void update_player(Player& player) {
    player.save_last_position();
    if (player.health > 0) {
        player.movement();
        player.jump();
    }
    player.gravity();
}

//Camera function
//keeps Player centered by moving the world
void update_camera(std::vector<Platform>& platforms, std::vector<Enemy>& enemys, Player& player) {
    float offset_x = CENTER_X - player.shape.getPosition().x;
    float offset_y = CENTER_Y - player.shape.getPosition().y;

    player.shape.move(offset_x, offset_y);

    for (auto& platform : platforms) {
        platform.move(offset_x, offset_y);
    }

    for (auto& enemy : enemys) {
        enemy.move(offset_x, offset_y);
    }
}

//Platform function
//includes Player collision with platforms
void update_platforms(std::vector<Platform>& platforms, Player& player) {
    player.collides(0);
    for (auto& platform : platforms) {
        if (collision(platform.shape, player.shape)) {
            sf::FloatRect player_bounds = player.shape.getGlobalBounds();
            sf::FloatRect platform_bounds = platform.shape.getGlobalBounds();
            sf::FloatRect last_player_bounds(player.last_position, player.shape.getSize());

            if (last_player_bounds.top + last_player_bounds.height <= platform_bounds.top) {
                player.shape.setPosition(player.shape.getPosition().x, platform_bounds.top - player_bounds.height);
                player.falling_speed = 0.f;
                player.collides(1);
            } else if (last_player_bounds.top >= platform_bounds.top + platform_bounds.height) {
                player.shape.setPosition(player.shape.getPosition().x, platform_bounds.top + platform_bounds.height);
                player.falling_speed = 0.f;
            } else if (last_player_bounds.left + last_player_bounds.width <= platform_bounds.left) {
                player.shape.setPosition(platform_bounds.left - player_bounds.width, player.shape.getPosition().y);
            } else if (last_player_bounds.left >= platform_bounds.left + platform_bounds.width) {
                player.shape.setPosition(platform_bounds.left + platform_bounds.width, player.shape.getPosition().y);
            }
        }
    }
}

void draw_platforms(std::vector<Platform>& platforms, sf::RenderWindow& window) {
    for (auto& platform : platforms) {
        platform.draw(window);
    }
}

//Enemy function

void update_enemys(std::vector<Enemy>& enemys, Player& player) {
    for (auto& enemy : enemys) {
        if (collision(enemy.shape, player.shape) && enemy.attack_cooldown == 120) {
            player.health -= 20;

            if (player.shape.getPosition().x < enemy.shape.getPosition().x) {
                player.shape.move(-player.damage_knockback, 0.f);
            } else {
                player.shape.move(player.damage_knockback, 0.f);
            }
            enemy.attack_cooldown = 0;
            player.touching_ground = false;
            player.falling_speed = player.damage_jump_force;
        } else if (enemy.attack_cooldown < 120) {
            enemy.attack_cooldown++;
        }
    }
}

void draw_enemys(std::vector<Enemy>& enemys, sf::RenderWindow& window) {
    for (auto& enemy : enemys) {
        enemy.draw(window);
    }
}

//Mainloop

int main() {
    //Initialization 
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "2D Game");
    Player player;
    std::vector<Platform> platforms;
    std::vector<Enemy> enemys;

    player.shape.setPosition(CENTER_X, CENTER_Y);
    player.last_position = player.shape.getPosition();

    //Test-Platform
    platforms.push_back(Platform(0.f, 800.f, 1000.f, 10.f));
    //Test Gegner
    enemys.push_back(Enemy(500.f, 780.f));

    //Calling update functions while window not closed
    while (window.isOpen()) {
        update_player(player);
        update_platforms(platforms, player);
        update_enemys(enemys, player);
        update_camera(platforms, enemys, player);
        draw_platforms(platforms, window);
        draw_enemys(enemys, window);
        player.draw(window);
        update_window(window);
    }
    //End of the Code
    return 0;
}
