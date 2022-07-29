#include "Engine.hpp"

int main() {
    Engine engine(Levels::test_level, Constants::window_width, Constants::window_height);
    engine.run();
    return 0;
}