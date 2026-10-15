#include "simulation.h"

Simulation::Simulation(Pendulum& pendulum, Agent& agent)
    : window(sf::VideoMode({1920, 1080}), "Pendulum"), is_running(true), 
      pendulum(pendulum), renderer(window, pendulum), agent(agent) 
{
    window.setFramerateLimit(60); 
}

void Simulation::run() {
    sf::Time timer = sf::seconds(SIMULATION_TIME_SECONDS);
    sf::Clock clock;
    while (window.isOpen() && is_running) {
        if (timer < sf::Time::Zero) this->reset();

        sf::Time delta_time = clock.restart();
        process_events();
        update(delta_time.asSeconds());
        render();

        timer -= delta_time;
    }
}

void Simulation::process_events() {
    // User Input
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
            is_running = false;
        }

        // Keyboard Press
        if (const auto* key_press = event->getIf<sf::Event::KeyPressed>()) {
            handle_key_press(*key_press);
        }
    }

    // Neural network action
    current_action = agent.get_action(pendulum.get_current_state(), MAX_AGENT_FORCE);    
}

void Simulation::handle_key_press(const sf::Event::KeyPressed&) {
    // Reset
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
        this->reset();
        std::cout << "reset" << std::endl;
    }
    // Push anchor right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        pendulum.apply_force_to_anchor(USER_PUSH_FORCE);
    }
    // Push anchor left
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        pendulum.apply_force_to_anchor(-USER_PUSH_FORCE);
    }
}

void Simulation::update(float dt) {
    PendulumState prev_state = pendulum.get_current_state();

    pendulum.move(dt);

    log_container.add(prev_state, current_action.raw_sample, current_action.log_prob, calculate_reward());
}

void Simulation::render() {
    renderer.render();
}

void Simulation::reset() {
    pendulum.reset();
    log_container.clear();
}

float Simulation::calculate_reward() {
    float anchor_speed_reward_weight = 0.0001f;
    float bob_speed_reward_weight    = 0.001f;

    PendulumState state = pendulum.get_current_state();

    // Maximize y (-cos) and penalize speed
    float bob_speed_penalty = bob_speed_reward_weight * (state.bob_speed * state.bob_speed);
    float anchor_speed_penalty = anchor_speed_reward_weight * (state.anchor_speed * state.anchor_speed);
    
    float reward = -state.cos - anchor_speed_penalty - bob_speed_penalty;
    return reward;
}