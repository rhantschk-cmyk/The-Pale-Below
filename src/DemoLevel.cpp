#include "DemoLevel.hpp"

void build_demo_level(std::vector<Platform>& platforms, std::vector<Enemy>& enemys) {
    //Start area
    platforms.push_back(Platform(-300.f, 810.f, 950.f, 20.f));
    platforms.push_back(Platform(-300.f, 620.f, 420.f, 20.f));
    platforms.push_back(Platform(280.f, 620.f, 370.f, 20.f));

    //Vertical shaft into lower tunnels
    platforms.push_back(Platform(120.f, 620.f, 20.f, 520.f));
    platforms.push_back(Platform(260.f, 620.f, 20.f, 520.f));
    platforms.push_back(Platform(140.f, 930.f, 120.f, 20.f));
    platforms.push_back(Platform(0.f, 1080.f, 700.f, 20.f));
    platforms.push_back(Platform(-120.f, 1260.f, 320.f, 20.f));
    platforms.push_back(Platform(360.f, 1260.f, 260.f, 20.f));

    //Middle tunnels
    platforms.push_back(Platform(700.f, 1080.f, 550.f, 20.f));
    platforms.push_back(Platform(700.f, 900.f, 300.f, 20.f));
    platforms.push_back(Platform(1080.f, 900.f, 170.f, 20.f));
    platforms.push_back(Platform(980.f, 720.f, 270.f, 20.f));
    platforms.push_back(Platform(980.f, 720.f, 20.f, 380.f));
    platforms.push_back(Platform(1230.f, 720.f, 20.f, 380.f));

    //Boss room tunnel
    platforms.push_back(Platform(1250.f, 1080.f, 350.f, 20.f));
    platforms.push_back(Platform(1450.f, 900.f, 150.f, 20.f));

    //Boss room rectangle
    platforms.push_back(Platform(1600.f, 720.f, 620.f, 20.f));
    platforms.push_back(Platform(1600.f, 1180.f, 620.f, 20.f));
    platforms.push_back(Platform(1600.f, 720.f, 20.f, 480.f));
    platforms.push_back(Platform(2200.f, 720.f, 20.f, 480.f));

    //Extra tunnel branches around boss room
    platforms.push_back(Platform(1680.f, 960.f, 180.f, 20.f));
    platforms.push_back(Platform(1960.f, 860.f, 180.f, 20.f));

    //Bug enemies in tunnels
    enemys.push_back(Enemy("bug", 60.f, 790.f));
    enemys.push_back(Enemy("bug", 250.f, 790.f));
    enemys.push_back(Enemy("bug", 40.f, 1060.f));
    enemys.push_back(Enemy("bug", 210.f, 1060.f));
    enemys.push_back(Enemy("bug", 430.f, 1240.f));
    enemys.push_back(Enemy("bug", 790.f, 1060.f));
    enemys.push_back(Enemy("bug", 1040.f, 700.f));
    enemys.push_back(Enemy("bug", 1680.f, 1160.f));
    enemys.push_back(Enemy("bug", 1860.f, 1160.f));
    enemys.push_back(Enemy("bug", 2020.f, 1160.f));
    enemys.push_back(Enemy("bug", 1710.f, 940.f));
    enemys.push_back(Enemy("bug", 1990.f, 840.f));

    //Regular enemies guarding narrower passages
    enemys.push_back(Enemy("enemy", 520.f, 790.f));
    enemys.push_back(Enemy("enemy", 520.f, 1240.f));
    enemys.push_back(Enemy("enemy", 900.f, 1060.f));
    enemys.push_back(Enemy("enemy", 1140.f, 880.f));
    enemys.push_back(Enemy("enemy", 1180.f, 700.f));
    enemys.push_back(Enemy("enemy", 1500.f, 1060.f));
    enemys.push_back(Enemy("enemy", 1760.f, 1160.f));
    enemys.push_back(Enemy("enemy", 2080.f, 1160.f));
}
