#include "agent.h"

Agent::Agent(NeuralNetwork network): actor(network) {}

float Agent::get_action(const P_state& state, float base_force)
{
    std::vector<float> output = actor.forwardpass(state);

    double force_coef = tanh(output[0]);
    float mu = base_force * force_coef;
    float log_std = std::clamp(output[1], -4.0f, 4.0f);


    return ();
    

}
