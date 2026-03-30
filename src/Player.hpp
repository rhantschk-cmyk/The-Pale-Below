#pragma once

#include <SFML/Graphics.hpp>

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
    float falling_speed = 0.f;
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
