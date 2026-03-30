#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Enemy.hpp"
#include "Platform.hpp"
#include "Player.hpp"

bool collision(const sf::RectangleShape& a, const sf::RectangleShape& b);

void update_window(sf::RenderWindow& window);
void update_player(Player& player);
void update_camera(std::vector<Platform>& platforms, std::vector<Enemy>& enemys, Player& player);
void update_platforms(std::vector<Platform>& platforms, Player& player);
void draw_platforms(std::vector<Platform>& platforms, sf::RenderWindow& window);
void update_enemys(std::vector<Enemy>& enemys, Player& player);
void draw_enemys(std::vector<Enemy>& enemys, sf::RenderWindow& window);
