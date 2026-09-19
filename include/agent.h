#ifndef AGENT_H
#define AGENT_H
#include "network.h"
#include "P_state.h"
#include <iostream>


class Agent
{
private:
    NeuralNetwork actor;
    float reward;

public:
    Agent(NeuralNetwork actor);

    float get_action(const P_state& state, float base_force);





};




#endif