#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

using wall_corners_t = std::pair<sf::Vector2f, sf::Vector2f>;

namespace Constants {
    constexpr short offset = 10;
    constexpr int window_width = 1366;
    constexpr int window_height = 720;
    const std::string window_title = "Pseudo3D Renderer";
    const float basic_speed = 4.0;
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

    static std::vector<wall_corners_t> labirinth_level = {{{0.f, 0.f}, {720.f, 80.f}},
                                                         {{800.f, 80.f}, {1000.f, 160.f}},
                                                         {{0.f, 170.f}, {550.f, 250.f}},
                                                         {{800.f, 80.f}, {880.f, 580.f}},
                                                         {{1080.f, 160.f}, {1160.f, 1100.f}},
                                                         {{120.f, 1020.f}, {1080.f, 1100.f}},
                                                         {{140.f, 370.f}, {550.f, 450.f}},
                                                         {{220.f, 370.f}, {300.f, 820.f}},
                                                         {{220.f, 520.f}, {550.f, 600.f}},
                                                         {{220.f, 740.f}, {880.f, 820.f}},
                                                         {{0.f, 520.f}, {120.f, 600.f}},
                                                         {{120.f, 680.f}, {300.f, 760.f}},
                                                         {{720.f, 880.f}, {850.f, 1080.f}},
                                                         {{520.f, 800.f}, {650.f, 900.f}},
                                                         {{0.f, 0.f}, {20.f, 1280.f}},
                                                         {{0.f, 1260.f}, {1280.f, 1280.f}},
                                                         {{1260.f, 0.f}, {1280.f, 1280.f}},
                                                         {{0.f, 0.f}, {1280.f, 20.f}}};
}

#endif