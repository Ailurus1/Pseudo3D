#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Utils.hpp"
#include "Constants.hpp"
#include "Map.hpp"

enum class Direction {
    FORWARD,
    BACKWARD
};

class Player {
    protected:
        float x, y, angle, speed = Constants::basic_speed;
        float dx = 0, dy = 0;
    public:
        Player();

        Player(const float &xx, const float &yy, const float &aa): x(xx), y(yy), angle(aa), dx(std::cos(aa)), dy(std::sin(aa)) {};

        [[nodiscard]] float getX() const;

        [[nodiscard]] float getY() const;

        [[nodiscard]] float getAngle() const;

        void setPosition(const sf::Vector2f &coords);

        static bool checkCollision(Map &map, const float &xx, const float &yy);

        void move(Map &map, const Direction &direction);

        void changeAngle(const float &value);

        void renderPlayer(sf::RenderWindow &current_window, const RenderSize &render_size) const;

        void castRays(sf::RenderWindow &current_window, const std::vector<segment_t> &walls, const RenderSize &render_size, const RenderMode &render_mode) const;
};

#endif