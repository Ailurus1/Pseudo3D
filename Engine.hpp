#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>
#include <SFML/Graphics.hpp>

#include "Map.hpp"
#include "Player.hpp"

class Engine {
    protected:
        sf::RenderWindow window;
        Map map;
        Player player;
        float time_without_update, update_interval;
        size_t window_width, window_height;
    public:
        Engine(std::vector<wall_corners_t> &walls, const size_t &window_width_p, const size_t &window_height_p);

        void render(const bool &render_minimap);

        void run();
};

#endif