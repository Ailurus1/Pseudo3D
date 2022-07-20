#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Map.hpp"
#include "Player.hpp"
#include "Constants.hpp"
#include "Utils.hpp"

void createMap(Map &map) {
    map.addWall(Wall(90, 90, 135, 800));
    map.addWall(Wall(90, 500, 720, 545));
    map.addWall(Wall(450, 90, 900, 135));
    map.addWall(Wall(855, 90, 900, 280));
    map.addWall(Wall(650, 235, 900, 280));

    map.addWall(Wall(0, 0, 20, 1280));
    map.addWall(Wall(0, 1260, 1280, 1280));
    map.addWall(Wall(1260, 0, 1280, 1280));
    map.addWall(Wall(0, 0, 1280, 20));
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1366, 720), "Pseudo3D Renderer", sf::Style::Close);
    window.setKeyRepeatEnabled(true);
    sf::Event event;

    Map map;

    createMap(map);

    Player player(150, 150, 25);

    float time_without_update = 0.0, update_interval = 1.f / float(Constants::fps);
    
    sf::Clock clock;
    clock.restart();

    std::vector<segment_t> all_walls = map.calculateAllSurfacesCoordinates();
    int count = 0;

    RenderSize render_size = RenderSize::MINI;

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
        // map.render(window, RenderSize::FULLSCREEN);
        // player.renderPlayer(window, RenderSize::FULLSCREEN);
        player.castRays(window, all_walls, RenderSize::FULLSCREEN, RenderMode::RENDER_3D);
        map.render(window, render_size);
        player.renderPlayer(window, render_size);
        player.castRays(window, all_walls, render_size, RenderMode::RENDER_2D);
        window.display();
        time_without_update += clock.restart().asSeconds();
    }
    return 0;
}