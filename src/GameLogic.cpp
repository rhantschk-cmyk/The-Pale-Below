#include "GameLogic.hpp"

#include "Config.hpp"

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
        player.attack();
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
            float player_center_x = player_bounds.left + player_bounds.width / 2.f;
            bool center_over_platform = player_center_x >= platform_bounds.left && player_center_x <= platform_bounds.left + platform_bounds.width;
            bool horizontal_overlap = player_bounds.left + player_bounds.width > platform_bounds.left && player_bounds.left < platform_bounds.left + platform_bounds.width;
            bool vertical_overlap = player_bounds.top + player_bounds.height > platform_bounds.top && player_bounds.top < platform_bounds.top + platform_bounds.height;

            if (last_player_bounds.top + last_player_bounds.height <= platform_bounds.top && horizontal_overlap && center_over_platform) {
                player.shape.setPosition(player.shape.getPosition().x, platform_bounds.top - player_bounds.height);
                player.falling_speed = 0.f;
                player.collides(1);
            } else if (last_player_bounds.top >= platform_bounds.top + platform_bounds.height && horizontal_overlap) {
                player.shape.setPosition(player.shape.getPosition().x, platform_bounds.top + platform_bounds.height);
                player.falling_speed = 0.f;
            } else if (last_player_bounds.left + last_player_bounds.width <= platform_bounds.left && vertical_overlap) {
                player.shape.setPosition(platform_bounds.left - player_bounds.width, player.shape.getPosition().y);
            } else if (last_player_bounds.left >= platform_bounds.left + platform_bounds.width && vertical_overlap) {
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
    for (int i = 0; i < enemys.size(); i++) {
        Enemy& enemy = enemys[i];

        if (enemy.type == "bug") {
            enemy.shape.move(enemy.patrol_speed * enemy.patrol_direction, 0.f);

            if (enemy.shape.getPosition().x <= enemy.start_x) {
                enemy.shape.setPosition(enemy.start_x, enemy.shape.getPosition().y);
                enemy.patrol_direction = 1;
            } else if (enemy.shape.getPosition().x >= enemy.start_x + enemy.patrol_range) {
                enemy.shape.setPosition(enemy.start_x + enemy.patrol_range, enemy.shape.getPosition().y);
                enemy.patrol_direction = -1;
            }

            if (player.attacking == true && collision(enemy.shape, player.attack_shape) && enemy.last_hit_attack != player.attack_id) {
                enemy.health -= 10;
                enemy.last_hit_attack = player.attack_id;
            }

            if (enemy.health <= 0) {
                enemys.erase(enemys.begin() + i);
                i--;
            }
        } else {
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
}

void draw_enemys(std::vector<Enemy>& enemys, sf::RenderWindow& window) {
    for (auto& enemy : enemys) {
        enemy.draw(window);
    }
}
