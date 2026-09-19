#ifndef NETWORK_H
#define NETWORK_H
#include "P_state.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>

class NeuralNetwork
{
private:
    float l_rate = 0.001f;
    std::vector<int> architecture;
    std::vector<std::vector<float>> weights;
    std::vector<std::vector<float>> bias;
   
    
    void initialize_weights();
    
    
    
public:
    static float ReLU(float x);
    static std::vector<float> softmax(const std::vector<float>& input);
    NeuralNetwork(const std::vector<int>& architecture);
    void validate_architecture(const std::vector<int>& architecture);
    
    std::vector<float> forwardpass(const P_state& input);
    void backpass();
};


#endif