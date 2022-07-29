#include "Map.hpp"

std::vector<Wall> Map::getWalls() {
    return walls;
}

void Wall::setColor(const sf::Color &new_color) {
    color = new_color;
}

void Map::addWall(const Wall &wall) {
    walls.emplace_back(wall);
    surfaces.push_back({{wall.left_upper_x, wall.left_upper_y}, {wall.right_lower_x, wall.left_upper_y}});
    surfaces.push_back({{wall.left_upper_x, wall.left_upper_y}, {wall.left_upper_x, wall.right_lower_y}});
    surfaces.push_back({{wall.left_upper_x, wall.right_lower_y}, {wall.right_lower_x, wall.right_lower_y}});
    surfaces.push_back({{wall.right_lower_x, wall.left_upper_y}, {wall.right_lower_x, wall.right_lower_y}});
}

void Map::drawWall(sf::RenderWindow &current_window, const Wall &wall) {
    sf::RectangleShape wall_rectangle(sf::Vector2f(std::abs(wall.right_lower_x - wall.left_upper_x),std::abs(wall.right_lower_y - wall.left_upper_y)));
    wall_rectangle.setPosition(wall.left_upper_x, wall.left_upper_y);
    wall_rectangle.setFillColor(wall.color);
    current_window.draw(wall_rectangle);
}

void Map::render(sf::RenderWindow &current_window, const RenderSize &render_size) {
    float scale = Utils::getScale(render_size);
    sf::Vector2f left_upper_background = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()}, right_lower_background = {std::numeric_limits<float>::min(), std::numeric_limits<float>::min()};
    for (const auto &wall: walls) {
        left_upper_background.x = std::min(wall.left_upper_x * scale, left_upper_background.x);
        left_upper_background.y = std::min(wall.left_upper_y * scale, left_upper_background.y);
        right_lower_background.x = std::max(wall.right_lower_x * scale, right_lower_background.x);
        right_lower_background.y = std::max(wall.right_lower_y * scale, right_lower_background.y);
    }
    sf::RectangleShape background_rectangle(sf::Vector2f(right_lower_background.x - left_upper_background.x, right_lower_background.y - left_upper_background.y));
    background_rectangle.setPosition(left_upper_background.x, left_upper_background.y);
    background_rectangle.setFillColor(sf::Color::Black);
    current_window.draw(background_rectangle);
    for (auto wall: walls) {
        wall.left_upper_x *= scale;
        wall.left_upper_y *= scale;
        wall.right_lower_x *= scale;
        wall.right_lower_y *= scale;
        drawWall(current_window, wall);
    }
}

std::vector<segment_t> Map::getSurfaces() {
    return surfaces;
}