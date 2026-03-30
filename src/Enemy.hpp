#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Enemy {
public:
    sf::RectangleShape shape;
    std::string type;
    int attack_cooldown = 120;
    int health = 0;
    float start_x = 0.f;
    float patrol_speed = 0.05f;
    float patrol_range = 100.f;
    int patrol_direction = 1;
    int last_hit_attack = -1;

    Enemy(const std::string& enemy_type, const float x, const float y) {
        type = enemy_type;
        shape.setSize(sf::Vector2f(20.f, 20.f));
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(x, y);
        start_x = x;

        if (type == "bug") {
            health = 20;
        }
    }

    void draw(sf::RenderWindow& window) {window.draw(shape);}
    void move(const float x, const float y) {
        shape.move(x, y);
        start_x += x;
    }
};
