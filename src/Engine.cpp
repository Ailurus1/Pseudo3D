#include "../include/Engine.hpp"

Engine::Engine(std::vector<wall_corners_t> &walls, const size_t &window_width_p, const size_t &window_height_p) {
    time_without_update = 0.0, update_interval = 1.f / float(Constants::fps);
    window_width = window_width_p;
    window_height = window_height_p;
    player = Player(120, 120, 25);
    for (const auto &wall: walls) {
        map.addWall(Wall(wall.first.x, wall.first.y, wall.second.x, wall.second.y));
    }
}

void Engine::render(const bool &render_minimap) {
    Map::drawSky(window, sf::Color(175, 255, 245));
    Map::drawFloor(window, sf::Color(55, 55, 55));
    player.castRays(window, map.getSurfaces(), RenderSize::FULLSCREEN, RenderMode::RENDER_3D);
    if (render_minimap) {
        map.render(window, RenderSize::MINI);
        player.renderPlayer(window, RenderSize::MINI);
        player.castRays(window, map.getSurfaces(), RenderSize::MINI, RenderMode::RENDER_2D);
    }
    window.display();
}

void Engine::run() {
    window.create(sf::VideoMode(window_width, window_height), Constants::window_title, sf::Style::Close);
    window.setKeyRepeatEnabled(true);
    sf::Clock clock;
    clock.restart();

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
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
                player.move(map, Direction::FORWARD);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                player.move(map, Direction::BACKWARD);
            }
            time_without_update -= update_interval;
        }
        window.clear();
        render(true);
        time_without_update += clock.restart().asSeconds();
    }
}