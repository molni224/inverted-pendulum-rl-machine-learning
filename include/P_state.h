#ifndef P_State_H
#define P_State_H

union P_state {
struct 
{
    float sinangle; //sin and cos for continues smooth values
    float cosangle;
    float v;
    float box_v;
    float box_pos_norm;
};
    float data[5];
};

struct StepResult
{
    P_state state;
    float reward;
    bool done;
};

struct Trajectory
{
    std::vector<P_state> states;
    std::vector<float> raw_samples;   // pre-clip sampled force, needed to recompute log_prob's gradient later
    std::vector<float> log_probs;
    std::vector<float> rewards;

    void add(P_state state, float raw_sample, float log_prob, float reward)
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
    size_t get_size() const {return states.size();}
};

#endif