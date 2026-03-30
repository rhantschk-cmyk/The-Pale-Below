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
    sf::RectangleShape attack_shape;
    bool attacking = false;
    bool last_attack_input = false;
    int attack_timer = 0;
    const int attack_duration = 20;
    int last_direction = 1;
    int attack_id = 0;
    int health = 100;

    Player() {
        shape.setSize(sf::Vector2f(20.f, 20.f));
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(50.f, 50.f);
        last_position = shape.getPosition();
        attack_shape.setFillColor(sf::Color::Yellow);
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
            last_direction = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            shape.move(movement_speed, 0.f);
            last_direction = 1;
        }
    }
    //Lets Player jump while touching ground
    void jump() {
        if (touching_ground == true) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                touching_ground = false;
                falling_speed = jump_force;
            }
        }
    }
    void update_attack_position() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            attack_shape.setSize(sf::Vector2f(10.f, 30.f));
            attack_shape.setPosition(shape.getPosition().x + 5.f, shape.getPosition().y - 30.f);
        } else if (touching_ground == false && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            attack_shape.setSize(sf::Vector2f(10.f, 30.f));
            attack_shape.setPosition(shape.getPosition().x + 5.f, shape.getPosition().y + 20.f);
        } else if (last_direction == -1) {
            attack_shape.setSize(sf::Vector2f(30.f, 10.f));
            attack_shape.setPosition(shape.getPosition().x - 30.f, shape.getPosition().y + 5.f);
        } else {
            attack_shape.setSize(sf::Vector2f(30.f, 10.f));
            attack_shape.setPosition(shape.getPosition().x + 20.f, shape.getPosition().y + 5.f);
        }
    }
    void attack() {
        bool attack_input = sf::Keyboard::isKeyPressed(sf::Keyboard::F) || sf::Mouse::isButtonPressed(sf::Mouse::Left);

        if (attack_input && last_attack_input == false && attacking == false) {
            attacking = true;
            attack_timer = attack_duration;
            attack_id++;
            update_attack_position();
        }

        if (attacking == true) {
            update_attack_position();
            attack_timer--;

            if (attack_timer <= 0) {
                attacking = false;
            }
        }

        last_attack_input = attack_input;
    }
    //Draw Function für window logic
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        if (attacking == true) {
            window.draw(attack_shape);
        }
    }
};
