#include "Player.hpp"

float Player::getX() {
    return x;
}

float Player::getY() {
    return y;
}

float Player::getAngle() {
    return angle;
}

void Player::move(const Direction &direction) {
    switch (direction) {
        case Direction::FORWARD:
            x += dx * std::cos(angle) * speed, y += dy * std::sin(angle) * speed;
            break;
        case Direction::BACKWARD:
            x -= dx * std::cos(angle) * speed, y -= dy * std::sin(angle) * speed;
            break;
        default:
            break;
    }
}

void Player::changeAngle(const float &value) {
    angle += value * Constants::basic_angle_change;
    if (angle < 0) {
        angle += 360;
    }
    else if (angle > 360) {
        angle -= 360;
    }
    dx = std::cos(Utils::radians(angle));
    dy = std::sin(Utils::radians(angle));
}

void Player::renderPlayer(sf::RenderWindow &current_window, const RenderMode &render_mode) {
    float scale = Utils::getScale(render_mode);
    sf::CircleShape player;
    player.setFillColor(sf::Color::Red);
    player.setRadius(10 * scale);
    player.setPosition(x * scale, y * scale);
    current_window.draw(player);
}

void Player::castRays(sf::RenderWindow &current_window, const std::vector<segment_t> &walls, const RenderMode &render_mode) {
    float scale = Utils::getScale(render_mode);

    for (int i = -32; i <= 32; ++i) {
        sf::Vector2f ray_start = {x + 10, y + 10}, ray_end = {x + Constants::ray_length * std::cos(angle + i * Constants::ray_frequence), 
                                                            y + Constants::ray_length * std::sin(angle + i * Constants::ray_frequence)};
        bool intersectionFound = false;
        sf::Vector2f first_intersection = ray_end;
        for (const auto &wall: walls) {
            auto intersection = Utils::segmentIntersection(ray_start, ray_end, wall.first, wall.second);
            if (intersection != std::nullopt) {
                if (!intersectionFound) {
                    intersectionFound = true;
                }
                float current_dist = std::sqrt(std::pow(intersection.value().x - ray_start.x, 2) + std::pow(intersection.value().y - ray_start.y, 2)), 
                    global_dist = std::sqrt(std::pow(first_intersection.x - ray_start.x, 2) + std::pow(first_intersection.y - ray_start.y, 2));
                if (current_dist - global_dist < Constants::eps) {
                    first_intersection = intersection.value();
                }
            }
        }

        ray_start.x *= scale, ray_start.y *= scale;
        first_intersection.x *= scale, first_intersection.y *= scale;

        sf::Vertex line[] =
        {
            sf::Vertex(ray_start),
            sf::Vertex(first_intersection)
        };
        current_window.draw(line, 2, sf::Lines);
    }
}