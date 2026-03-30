#pragma once

#include <SFML/Graphics.hpp>

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
