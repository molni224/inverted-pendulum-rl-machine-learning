#include "network.h"

NeuralNetwork::NeuralNetwork(const std::vector<int>& architecture) 
: architecture(architecture), INPUT_SIZE(architecture[0]), OUTPUT_SIZE(architecture[architecture.size() - 1])
{
    validate_architecture(architecture);
    setup_nodes();
    initialize_weights();
}

void NeuralNetwork::validate_architecture(const std::vector<int>& architecture)
{
    if (architecture.size() < 2) {
        throw std::invalid_argument("Network needs at least input and output layers");
    }
    for (int size : architecture) {
        if(size <= 0) {
            throw std::invalid_argument("Layer size must be a positive number");
        }
    }
}

void NeuralNetwork::setup_nodes() {
    int number_of_nodes = std::accumulate(architecture.begin(), architecture.end(), 0);
    nodes.reserve(number_of_nodes);
}

void NeuralNetwork::initialize_weights() {
    std::random_device random;
    unsigned int seed = random();
    std::mt19937 generator(seed);

    for (int column = 1; column < static_cast<int>(architecture.size()); column++) {
        // Calculate random deviation for each column
        float standard_deviation_size = std::sqrt(2.0f / architecture[column-1]);
        std::normal_distribution<float> distribution(0.0f, standard_deviation_size);

        for (int row = 0; row < architecture[column]; row++) {
            // Reserve the weights (every node is connected to every node before it)
            int index = get_nodes_index(column, row);
            nodes[index].weights.reserve(architecture[column-1]);

            for (int weight_index = 0; weight_index < nodes[index].weights.size(); weight_index++) {
                float weight_value = static_cast<float>(distribution(generator));    // Generate random weight
                Node* source_node = &nodes[get_nodes_index(column-1, weight_index)]; // Source node that the weight coms from
                nodes[index].weights[weight_index] = Weight(weight_value, source_node);;
            }
        }
    }
}

float NeuralNetwork::ReLU(float x) {
    return std::max(0.0f,x);
}

int NeuralNetwork::get_nodes_index(int column, int row) const {
    return row * column + column;
}

std::vector<float> NeuralNetwork::softmax(const std::vector<float>& input) {
    //Convert output into normalized positive outputs
    std::vector<float> output(input.size(),0.0f);  
    float sum = 0;
    float max_value = input[0];

    for (float value : input) {
        if (value > max_value) {
            max_value = value;
        }
    }

    for(size_t i = 0; i< input.size(); i++) {
        output[i] = std::exp(input[i] - max_value);
        sum += output[i];
    }

    for (size_t i = 0; i< output.size(); i++) {
        output[i] /= sum;
    }

    return output;
}

/*
for (int column = 1; column < static_cast<int>(architecture.size()); column++) {
        

        for (int row = 0; row < architecture[column]; row++) {
            int index = get_nodes_index(column, row);

            for (int weight_index = 0; weight_index < nodes[index].weights.size(); weight_index++) {
                
            }
        }
    }
*/

std::vector<float> NeuralNetwork::forwardpass(const PendulumState& state) {
    // Set intput values
    auto pendulum_state_attributes = state.get_attributes();
    for (int i = 0; i < INPUT_SIZE; i++) {
        nodes[i].value = pendulum_state_attributes[i];
    }

    // Calculate the values to the input
    for (int i = INPUT_SIZE; i < nodes.size(); i++) {
        float current_value = nodes[i].bias;
        for (int weight_index = 0; weight_index < nodes[i].weights.size(); weight_index++) {
            Weight current_weight = nodes[i].weights[weight_index];
            current_value += current_weight.value * current_weight.source_node->value;
        }
    }

    size_t start_idx = nodes.size() - OUTPUT_SIZE - 1;
    std::vector<float> output_node_values;
    output_node_values.reserve(OUTPUT_SIZE);
    
    for (size_t i = 0; i < OUTPUT_SIZE; ++i) {
        output_node_values.push_back(nodes[start_idx + i].value);
    }
    
    return output_node_values;
}
    /*
    float temp_sum;
    std::vector<float> input(state.data, state.data + 5);
    std:utp:vector<float> output(state.data, state.data + 5);
    for (size_t a = 1; a < architecture.size()-1; a++)
    {
        std::vector<float> layer(architecture[a]);
        for (size_t b = 0; b < architecture[a]; b++)
        {
            temp_sum = bias[a-1][b];
            for (size_t c = 0; c < architecture[a-1]; c++)
            {
                temp_sum += input[c]*weights[a-1][b * architecture[a-1] + c];
            }
            layer[b] = ReLU(temp_sum);
        }
        input = layer;
    }

    size_t a = architecture.size()-1;
    std::vector<float> layer(architecture[a]);
    for (size_t b = 0; b < architecture[a]; b++)
    {
        temp_sum = bias[a-1][b];
        for (size_t c = 0; c < architecture[a-1]; c++)
        {
            temp_sum += input[c]*weights[a-1][b * architecture[a-1] + c];
        }
        layer[b] = temp_sum;
    }
    output = layer;
    return output;
    */
}

// same as normal forwardpass just caching every layer to pre/post_activation vectors
std::vector<float> NeuralNetwork::forwardpass_cached(const PendulumState& state)
{
    /*
    float temp_sum;
    std::vector<float> input(state.data, state.data + 5);
    std::vector<float> output(state.data, state.data + 5);

    cache.inputs.push_back(state);
    

    for (size_t a = 1; a < architecture.size()-1; a++)
    {
        std::vector<float> layer(architecture[a]);
        for (size_t b = 0; b < architecture[a]; b++)
        {
            temp_sum = bias[a-1][b];
            for (size_t c = 0; c < architecture[a-1]; c++)
            {
                temp_sum += input[c]*weights[a-1][b * architecture[a-1] + c];
            }
            cache.pre_activation[a-1].push_back(temp_sum);
            layer[b] = ReLU(temp_sum);
            cache.activation[a-1].push_back(layer[b]);
        }
        input = layer;
    }

    size_t a = architecture.size()-1;
    std::vector<float> layer(architecture[a]);
    for (size_t b = 0; b < architecture[a]; b++)
    {
        temp_sum = bias[a-1][b];
        for (size_t c = 0; c < architecture[a-1]; c++)
        {
            temp_sum += input[c]*weights[a-1][b * architecture[a-1] + c];
        }
        cache.pre_activation[a-1].push_back(temp_sum);
        layer[b] = temp_sum;
    }
    output = layer;
    return output;
    */
}
