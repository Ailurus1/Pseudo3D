#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Map.hpp"
#include "Player.hpp"
#include "Constants.hpp"
#include "Utils.hpp"

void createMap(Map &map) {
    map.addWall(Wall(45, 45, 90, 545));
    map.addWall(Wall(90, 500, 720, 545));
    map.addWall(Wall(450, 90, 900, 135));
    map.addWall(Wall(855, 90, 900, 280));
    map.addWall(Wall(650, 235, 900, 280));

    map.addWall(Wall(0, 0, 20, 720));
    map.addWall(Wall(0, 700, 1280, 720));
    map.addWall(Wall(1260, 0, 1280, 720));
    map.addWall(Wall(0, 0, 1280, 20));
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Ray Casting", sf::Style::Close);
    window.setKeyRepeatEnabled(true);
    sf::Event event;

    Map map;

    createMap(map);

    Player player(150, 150, 25);

    float time_without_update = 0.0, update_interval = 1.f / float(Constants::fps);
    
    sf::Clock clock;
    clock.restart();

    std::vector<segment> all_walls = map.calculateAllSurfacesCoordinates();
    int count = 0;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                    window.close();
                    return 0;
            }
            else {
                break;
            }
        }
        if (time_without_update >= update_interval) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                player.changeAngle(-Constants::basic_angle_change);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                player.changeAngle(Constants::basic_angle_change);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                player.move(Direction::FORWARD);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                player.move(Direction::BACKWARD);
            }
            time_without_update -= update_interval;
        }
        window.clear();
        map.render(window);
        player.renderPlayer(window);
        player.castRays(window, all_walls);
        window.display();
        time_without_update += clock.restart().asSeconds();
    }
    return 0;
}