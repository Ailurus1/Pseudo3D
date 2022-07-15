#ifndef UTILS_HPP
#define UTILS_HPP

#define _USE_MATH_DEFINES

#include <vector>
#include <cmath>
#include <optional>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Constants.hpp"

using segment_t = std::pair<sf::Vector2f, sf::Vector2f>;

enum class RenderSize {
    FULLSCREEN,
    MEDIUM,
    MINI
};

enum class RenderMode {
    RENDER_2D,
    RENDER_3D
};

namespace Utils {
    struct Line {
        float a, b, c; // a*x + b*y + c = 0

        Line(const float &aa, const float &bb, const float &cc): a(aa), b(bb), c(cc) {};

        Line(const sf::Vector2f &p, const sf::Vector2f &q);
    };

    float radians(const float &degrees);

    float det(const float &a, const float &b, const float &c, const float &d);

    bool between(const float &l, const float &r, const float &x);

    float distance(const sf::Vector2f &a, const sf::Vector2f &b);

    std::optional<sf::Vector2f> segmentIntersection(const sf::Vector2f &start_a, const sf::Vector2f &end_a, const sf::Vector2f &start_b, const sf::Vector2f &end_b);

    bool sameHalfplane(const sf::Vector2f &a, const sf::Vector2f &b, const sf::Vector2f &relative_point);

    float getScale(const RenderSize &render_mode);
}

#endif