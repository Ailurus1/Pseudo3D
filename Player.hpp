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
        Player() = default;

        Player(const float &xx, const float &yy, const float &aa): x(xx), y(yy), angle(aa), dx(std::cos(aa)), dy(std::sin(aa)) {};

        float getX();

        float getY();

        float getAngle();

        void move(const Direction &direction);

        void changeAngle(const float &value);

        void renderPlayer(sf::RenderWindow &current_window, const RenderSize &render_size);

        void castRays(sf::RenderWindow &current_window, const std::vector<segment_t> &walls, const RenderSize &render_size, const RenderMode &render_mode);
};

#endif