#ifndef RENDERER_H
#define RENDERER_H

#include "pendulum.h"
#include <SFML/Graphics.hpp>

class Renderer {
private:
    sf::RenderWindow& window;

    Pendulum& pendulum;

    sf::RectangleShape anchor;
    sf::Vertex rope[2];
    sf::CircleShape bob;

    static constexpr float ANCHOR_SIZE = 20.0f;
    static constexpr float BOB_RADIUS = 25.0f;

    void config_anchor();
    void config_bob();

    void update_parts_position();

public:
    Renderer(sf::RenderWindow& window, Pendulum& pendulum);

    void render();
};




#endif