#ifndef AGENT_H
#define AGENT_H
#include "network.h"
#include <algorithm>
#include "P_state.h"
#include <iostream>

struct ActionResoult
{
    float force;
    float log_prob;
};


class Agent
{
private:
    NeuralNetwork actor;
    float reward;
    std::mt19937 gen{std::random_device{}()};

public:
    Agent(NeuralNetwork actor);

    ActionResoult get_action(const P_state& state, float base_force);





};




#endif