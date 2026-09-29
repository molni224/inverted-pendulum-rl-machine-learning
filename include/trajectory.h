#ifndef TRAJECTORY_H
#define TRAJECTORY_H
#include "P_state.h"
#include <vector>
#include <numeric>
#include <cmath>

struct Trajectory
{
    std::vector<P_state> states;
    std::vector<float> raw_samples;
    std::vector<float> log_probs;
    std::vector<float> rewards;

    void add(const P_state& state, float raw_sample, float log_prob, float reward)
    {
        states.push_back(state);
        raw_samples.push_back(raw_sample);
        log_probs.push_back(log_prob);
        rewards.push_back(reward);
    }

    void clear()
    {
        states.clear();
        raw_samples.clear();
        log_probs.clear();
        rewards.clear();
    }

    size_t size() const { return states.size(); }

    // discounted return per timestep, computed backward
    std::vector<float> compute_returns(float gamma = 0.99f) const
    {
        std::vector<float> returns(rewards.size());
        float running_return = 0.0f;

        for (int t = static_cast<int>(rewards.size()) - 1; t >= 0; --t)
        {
            running_return = rewards[t] + gamma * running_return;
            returns[t] = running_return;
        }
        return returns;
    }

    // optional: normalize returns to mean 0, std 1 — stabilizes training
    static void normalize(std::vector<float>& returns)
    {
        if (returns.empty()) return;

        float mean = std::accumulate(returns.begin(), returns.end(), 0.0f) / returns.size();

        float sq_sum = 0.0f;
        for (float r : returns) sq_sum += (r - mean) * (r - mean);
        float stddev = std::sqrt(sq_sum / returns.size());

        constexpr float EPS = 1e-8f;  // avoid divide-by-zero if all returns are identical
        for (float& r : returns)
            r = (r - mean) / (stddev + EPS);
    }
};

#endif