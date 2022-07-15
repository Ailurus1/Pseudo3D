#include "Map.hpp"

std::vector<Wall> Map::getWalls() {
    return walls;
}

void Wall::setColor(const sf::Color &new_color) {
    color = new_color;
}

void Map::addWall(const Wall &wall) {
    walls.emplace_back(wall);
}

void Map::drawWall(sf::RenderWindow &current_window, const Wall &wall) {
    sf::RectangleShape wall_rectangle(sf::Vector2f(abs(wall.right_lower_x - wall.left_upper_x), abs(wall.right_lower_y - wall.left_upper_y)));
    wall_rectangle.setPosition(wall.left_upper_x, wall.left_upper_y);
    wall_rectangle.setFillColor(wall.color);
    current_window.draw(wall_rectangle);
}

void Map::render(sf::RenderWindow &current_window) {
    for (const auto &wall: walls) {
        drawWall(current_window, wall);
    }
}

std::vector<segment> Map::calculateAllSurfacesCoordinates() {
    std::vector<segment> res;
    for (const auto &wall: walls) {
        res.push_back({{wall.left_upper_x, wall.left_upper_y}, {wall.right_lower_x, wall.left_upper_y}});
        res.push_back({{wall.left_upper_x, wall.left_upper_y}, {wall.left_upper_x, wall.right_lower_y}});
        res.push_back({{wall.left_upper_x, wall.right_lower_y}, {wall.right_lower_x, wall.right_lower_y}});
        res.push_back({{wall.right_lower_x, wall.left_upper_y}, {wall.right_lower_x, wall.right_lower_y}});
    }
    return res;
}