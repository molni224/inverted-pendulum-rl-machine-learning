#ifndef SIMULATION_H
#define SIMULATION_H

#include "renderer.h"
#include "pendulum.h"

class Simulation {
private:
    sf::RenderWindow window;
    Renderer renderer;
    bool is_running;

    Pendulum pendulum;

    void process_events();
    void render();

public:
    Simulation(Pendulum& pendulum);

    sf::Vector2i get_mouse_pos() const { return sf::Mouse::getPosition(window); }
    sf::RenderWindow& get_window() { return window; }
    Renderer& get_renderer() { return renderer; }

    void end_simulation() { is_running = false; }
    void run();

};

#endif