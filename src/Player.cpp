#include "../include/Player.hpp"

Player::Player() {
    x = Constants::window_width / 2.f;
    y = Constants::window_height / 2.f;
    angle = 0.f;
}

float Player::getX() const {
    return x;
}

float Player::getY() const {
    return y;
}

float Player::getAngle() const {
    return angle;
}

void Player::setPosition(const sf::Vector2f &coords) {
    x = coords.x;
    y = coords.y;
}

bool Player::checkCollision(Map &map, const float &xx, const float &yy) {
    std::vector<Wall> walls = map.getWalls();
    for (const auto &wall: walls) {
        if (xx >= wall.left_upper_x && xx <= wall.right_lower_x && yy <= wall.right_lower_y && yy >= wall.left_upper_y) {
            return false;
        }
    }
    return true;
}

void Player::move(Map &map, const Direction &direction) {
    switch (direction) {
        case Direction::FORWARD:
            if (Player::checkCollision(map, x + dx * std::cos(angle) * speed + Constants::offset, y + dy * std::sin(angle) * speed *
                                                    (static_cast<float>(Constants::window_width) / static_cast<float>(Constants::window_height)) + Constants::offset)) {
                x += dx * std::cos(angle) * speed;
                y += dy * std::sin(angle) * speed * (static_cast<float>(Constants::window_width) / static_cast<float>(Constants::window_height));
            }
            break;
        case Direction::BACKWARD:
            if (Player::checkCollision(map, x - dx * std::cos(angle) * speed + Constants::offset, y - dy * std::sin(angle) * speed *
                                                    (static_cast<float>(Constants::window_width) / static_cast<float>(Constants::window_height))) + Constants::offset) {
                x -= dx * std::cos(angle) * speed;
                y -= dy * std::sin(angle) * speed * (static_cast<float>(Constants::window_width) / static_cast<float>(Constants::window_height));
            }
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

void Player::renderPlayer(sf::RenderWindow &current_window, const RenderSize &render_size) const {
    float scale = Utils::getScale(render_size);
    sf::CircleShape player;
    player.setFillColor(sf::Color::Red);
    player.setRadius(10 * scale);
    player.setPosition(x * scale, y * scale);
    current_window.draw(player);
}

void Player::castRays(sf::RenderWindow &current_window, const std::vector<segment_t> &walls, const RenderSize &render_size,
                      const RenderMode &render_mode) const {
    size_t horizontal_offset = 0;
    int max_dist = std::ceil(std::sqrt(Constants::window_width * Constants::window_width + Constants::window_height * Constants::window_height));
    int color_coef = max_dist / 255;
    for (int i = -(Constants::window_width / 2); i <= Constants::window_width / 2; ++i) {
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
                float current_dist = std::sqrt(std::pow(intersection.value().x - ray_start.x, 2) +
                                                  std::pow(intersection.value().y - ray_start.y, 2)),
                      global_dist = std::sqrt(std::pow(first_intersection.x - ray_start.x, 2) +
                                                 std::pow(first_intersection.y - ray_start.y, 2));
                if (current_dist - global_dist < Constants::eps) {
                    first_intersection = intersection.value();
                }
            }
        }
        if (render_mode == RenderMode::RENDER_2D) {
            float scale = Utils::getScale(render_size);

            ray_start.x *= scale, ray_start.y *= scale;
            first_intersection.x *= scale, first_intersection.y *= scale;

            sf::Vertex line[] = {sf::Vertex(ray_start), sf::Vertex(first_intersection)};
            current_window.draw(line, 2, sf::PrimitiveType::Lines);
        }
        else {
            float width_coef = 1.f / (static_cast<float>(Constants::window_width));
            auto current_dist = static_cast<float>(std::sqrt(std::pow(first_intersection.x - ray_start.x, 2) + std::pow(first_intersection.y - ray_start.y, 2)));

            int color_offset = static_cast<int>(current_dist) / color_coef;
            sf::Vertex line[] = {sf::Vertex(
                    sf::Vector2f(static_cast<float>(i + (Constants::window_width / 2)) + width_coef * horizontal_offset,
                                           static_cast<float>(Constants::window_height / 2) * (1.f + 135.f / current_dist)),
                                           sf::Color(255 - color_offset, 255 - color_offset, 255 - color_offset)), sf::Vertex(
                    sf::Vector2f(static_cast<float>(i + (Constants::window_width / 2)) + width_coef * horizontal_offset,
                                           static_cast<float>(Constants::window_height / 2) * (1.f - 135.f / current_dist)),
                                           sf::Color(255 - color_offset, 255 - color_offset, 255 - color_offset))};

            current_window.draw(line, 2, sf::PrimitiveType::Lines);
            ++horizontal_offset;
        }
    }
}