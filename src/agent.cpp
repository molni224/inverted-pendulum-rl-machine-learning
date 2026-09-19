#include "agent.h"

Agent::Agent(NeuralNetwork network): actor(network) {}

float Agent::get_action(const P_state& state, float base_force)
{
    std::vector<float> output = NeuralNetwork::softmax(actor.forwardpass(state));

    //output[0] = right output[1] = left
    return (base_force * (output[0]-output[1]));
    

}
