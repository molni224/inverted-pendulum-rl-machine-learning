#include "simulation.h"

Simulation::Simulation(Pendulum& pendulum): window(sf::VideoMode({1920, 1080}), "Pendulum"), is_running(true), pendulum(pendulum) {
    window.setFramerateLimit(60); 
}

Simulation::run() {
    sf::Clock clock;
    while (window.isOpen() && is_running) {
        sf::Time delta_time = clock.restart();
        process_events();
        render();
    }
}

Simulation::process_events() {

}

Simulation::render() {
    renderer.render();
}