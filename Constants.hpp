#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

using wall_corners_t = std::pair<sf::Vector2f, sf::Vector2f>;

namespace Constants {
    constexpr int window_width = 1366;
    constexpr int window_height = 720;
    const std::string window_title = "Pseudo3D Renderer";
    const float basic_speed = 4.5;
    const float basic_angle_change = 0.25;
    const float ray_frequence = 0.001;
    const float ray_length = 1280.f;
    constexpr int fps = 60;
    const double eps = 1e-6;
}

namespace Levels {
    static std::vector<wall_corners_t> test_level = {{{90.f, 90.f}, {135.f, 800.f}},
                                                     {{90.f, 500.f}, {720.f, 545.f}},
                                                     {{450.f, 90.f}, {900.f, 135.f}},
                                                     {{855.f, 90.f}, {900.f, 280.f}},
                                                     {{650.f, 235.f}, {900.f, 280.f}},
                                                     {{0.f, 0.f}, {20.f, 1280.f}},
                                                     {{0.f, 1260.f}, {1280.f, 1280.f}},
                                                     {{1260.f, 0.f}, {1280.f, 1280.f}},
                                                     {{0.f, 0.f}, {1280.f, 20.f}}};
}

#endif