#ifndef SIMULATION_H
#define SIMULATION_H

#include <optional>
#include <SFML/Window/Event.hpp>
#include "renderer.h"
#include "pendulum.h"
#include "agent.h"
#include "data_storage.h"


class Simulation {
private:
    sf::RenderWindow window;
    bool is_running;

    Pendulum& pendulum;
    Renderer renderer;

    SimulationLogContainer log_container;
    ActionResult current_action;
    Agent& agent;
    
    static constexpr float USER_PUSH_FORCE = 500.0f;
    static constexpr float SIMULATION_TIME_SECONDS = 30.0f; 
    static constexpr float MAX_AGENT_FORCE = 750.0f;

    void process_events();
    void update(float dt);
    void render();

    void handle_key_press(const sf::Event::KeyPressed& key);

    void reset();
    float calculate_reward();

public:
    Simulation(Pendulum& pendulum, Agent& agent);

    sf::Vector2i get_mouse_pos() const { return sf::Mouse::getPosition(window); }
    sf::RenderWindow& get_window() { return window; }
    Renderer& get_renderer() { return renderer; }

    void end_simulation() { is_running = false; }
    void run();
};

#endif