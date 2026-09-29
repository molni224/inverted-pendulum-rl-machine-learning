#include "agent.h"

Agent::Agent(NeuralNetwork network): actor(network) {}

ActionResult Agent::get_action(const P_state& state, float base_force)
{
    std::vector<float> output = actor.forwardpass(state);

    double force_coef = tanh(output[0]);
    float median = base_force * force_coef;
    float log_std = std::clamp(output[1], -4.0f, 4.0f);
    float sigma = exp(log_std);

    std::normal_distribution<float> dist(median,sigma);
    float sample = dist(gen);
    float force = std::clamp(sample, -base_force, base_force);

    constexpr float LOG_SQRT_2PI = 0.9189385332f;

    float z = (sample - median) / sigma;
    float log_prob = -0.5f * z * z - log_std - LOG_SQRT_2PI;

    return {force, sample, log_prob};
}
