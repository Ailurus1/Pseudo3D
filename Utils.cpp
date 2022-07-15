#include "Utils.hpp"

Utils::Line::Line(const sf::Vector2f &p, const sf::Vector2f &q) {
    a = p.y - q.y, b = q.x - p.x, c = - a * p.x - b * p.y;

    float norm_coef = 1.f / sqrt (a * a + b * b);
    if (abs(norm_coef) > Constants::eps) {
        a *= norm_coef,  b *= norm_coef,  c *= norm_coef;
    }
}

float Utils::radians(const float &degrees) {
    return degrees * M_PI / 180.f;
}

float Utils::det(const float &a, const float &b, const float &c, const float &d) {
    return a * d - b * c;
}

bool Utils::between(const float &l, const float &r, const float &x) {
    return std::min(l, r) - x <= Constants::eps && std::max(l,r) - x >= -Constants::eps;
}

float Utils::distance(const sf::Vector2f &a, const sf::Vector2f &b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

std::optional<sf::Vector2f> Utils::segmentIntersection(const sf::Vector2f &start_a, const sf::Vector2f &end_a, const sf::Vector2f &start_b, const sf::Vector2f &end_b) {
    float denominator = (end_a.x - start_a.x) * (end_b.y - start_b.y) - (end_a.y - start_a.y) * (end_b.x - start_b.x);
    if (std::abs(denominator) < Constants::eps) {
        return std::nullopt;
    }
    float t = ((start_a.x - start_b.x) * (start_b.y - end_b.y) - (start_a.y - start_b.y) * (start_b.x - end_b.x)) / ((end_a.x - start_a.x) * (end_b.y - start_b.y) - (end_a.y - start_a.y) * (end_b.x - start_b.x));
    float u = ((end_a.x - start_a.x) * (start_a.y - start_b.y) - (end_a.y - start_a.y) * (start_a.x - start_b.x)) / ((end_a.x - start_a.x) * (end_b.y - start_b.y) - (end_a.y - start_a.y) * (end_b.x - start_b.x));

    return (t >= Constants::eps && (1 - t) >= Constants::eps && u >= Constants::eps && (1 - u) >= Constants::eps ? 
            std::optional(sf::Vector2f({start_a.x + t * (end_a.x - start_a.x), start_a.y + t * (end_a.y - start_a.y)}))
            : std::nullopt);
}

bool Utils::sameHalfplane(const sf::Vector2f &a, const sf::Vector2f &b, const sf::Vector2f &relative_point) {
    return (((a.x - relative_point.x > 0) == (b.x - relative_point.x > 0)) || ((a.x - relative_point.x < 0) == (b.x - relative_point.x < 0))) && 
           (((a.y - relative_point.y > 0) == (b.y - relative_point.y > 0)) || ((a.y - relative_point.y < 0) == (b.y - relative_point.y < 0)));
}

float Utils::getScale(const RenderMode &render_mode) {
    switch (render_mode) {
        case RenderMode::FULLSCREEN:
            return 1.0;
        case RenderMode::MEDIUM:
            return 0.5;
        case RenderMode::MINI:
            return 0.2;
        default:
            return 1.0;
    }
}