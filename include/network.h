#ifndef NETWORK_H
#define NETWORK_H

#include "structs.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <numeric>

struct Node {
    float value = 0;
    float bias = 0;
    std::vector<Weight> weights;
};

struct Weight {
    float value;
    Node* source_node;

    Weight(float value, Node* source_node) : value(value), source_node(source_node) {};
};

class NeuralNetwork {
private:
    static constexpr float LEARNING_RATE = 0.001f;
    const int INPUT_SIZE;
    const int OUTPUT_SIZE;

    const std::vector<int> architecture;
    std::vector<Node> nodes;

    ForwardsCache cache;
    
    void validate_architecture(const std::vector<int>& architecture);
    void setup_nodes();
    void initialize_weights();

    int get_nodes_index(int column, int row) const;

public:
    NeuralNetwork(const std::vector<int>& architecture);

    static float ReLU(float x);
    static std::vector<float> softmax(const std::vector<float>& input);
    
    std::vector<float> forwardpass(const PendulumState& input);
    std::vector<float> forwardpass_cached(const PendulumState& input);

    void backwardpass();
    float loss_func();
    void backpass();
};


#endif