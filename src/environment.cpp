#include "environment.h"

Environment::Environment(Pendulum& pendulum) : pendulum(pendulum) {}

void Environment::pen_draw(sf::RenderWindow& window)
{
    pendulum.pen_draw(window);
}

float Environment::get_reward(const P_state& state)
{
    float reward = -state.cosangle - 0.001f*std::pow(state.v,2) - 0.0001f*std::pow(state.box_v, 2);
    return reward;
}

StepResult Environment::step(float force, float dt)
{
    pendulum.apply_force(force);
    pendulum.movement(dt);

    P_state state_after_movement = pendulum.get_state();
    float reward = get_reward(state_after_movement);

    return {state_after_movement, reward, done};

}

P_state Environment::reset()
{
    done = false;
    pendulum.reset();
    return pendulum.get_state();
}