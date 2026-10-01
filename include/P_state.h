#ifndef P_State_H
#define P_State_H
#include <vector>
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

struct ForwardsCache
{
    std::vector<P_state> inputs;
    std::vector<std::vector<float>> pre_activation;
    std::vector<std::vector<float>> activation;


    void clear()
    {
        inputs.clear();
    for (size_t i = 0; i < inputs.size(); i++)
    {
        pre_activation[i].clear();
        activation[i].clear();
        
    }
    }
};

#endif