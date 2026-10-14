#include "agent.h"

Agent::Agent(NeuralNetwork network): actor(network) {}

const NeuralNetwork& Agent::get_network()
{
    return actor;
}

ActionResult Agent::get_action(const P_state& state, float base_force)
{
    std::vector<float> output = actor.forwardpass_cached(state);

    //tanh on output one of network for force coefficient, median and standard distribution for noraml distribution
    float force_coef = tanh(output[0]);
    float median = force_coef;
    float log_std = std::clamp(output[1], -4.0f, 4.0f);
    float sigma = exp(log_std);

    // exploration
    std::normal_distribution<float> dist(median,sigma);
    float sample = dist(gen);
    float sample_force = sample * base_force;
    float force = std::clamp(sample_force, -base_force, base_force);

    constexpr float LOG_SQRT_2PI = 0.9189385332f;

    float z = (sample - median) / sigma;
    float log_prob = -0.5f * z * z - log_std - LOG_SQRT_2PI;

    return {force, sample, log_prob};
}
