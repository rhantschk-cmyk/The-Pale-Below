#pragma once

#include <SFML/Graphics.hpp>

class Platform {
public:
    sf::RectangleShape shape; //Platform Hitbox

    Platform(const float x, const float y, const float width, const float height) {
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(x, y);

        if (texture_loaded() == true) {
            shape.setTexture(&texture());
        }
    }
    //Draw function for window logic
    void draw(sf::RenderWindow& window) {window.draw(shape);}
    //Moves Platform for screen scrolling
    void move(const float x, const float y) {shape.move(x, y);}

private:
    static sf::Texture& texture() {
        static sf::Texture platform_texture;
        return platform_texture;
    }

    static bool texture_loaded() {
        static bool loaded = texture().loadFromFile("assets/textures/platform.png");
        return loaded;
    }
};
