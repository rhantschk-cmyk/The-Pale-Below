//GAME

//Initialasation

#include <SFML/Graphics.hpp>
#include <vector>

#include "Config.hpp"
#include "DemoLevel.hpp"
#include "Enemy.hpp"
#include "GameLogic.hpp"
#include "Platform.hpp"
#include "Player.hpp"

int main() {
    //Initialization 
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "2D Game");
    Player player;
    std::vector<Platform> platforms;
    std::vector<Enemy> enemys;

    player.shape.setPosition(CENTER_X, CENTER_Y);
    player.last_position = player.shape.getPosition();

    build_demo_level(platforms, enemys);

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
