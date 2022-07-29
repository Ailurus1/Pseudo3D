#include "include/Engine.hpp"

int main() {
    Engine engine(Levels::labirinth_level, Constants::window_width, Constants::window_height);
    engine.run();
    return 0;
}