#include "network.h"

//constructor of object
NeuralNetwork::NeuralNetwork(const std::vector<int>& architecture) : architecture(architecture)
{
    validate_architecture(architecture);
    for (size_t i = 1; i < architecture.size(); i++)
    {
        int input_size = architecture[i-1];
        int output_size = architecture[i];

        weights.push_back(std::vector<float>(input_size * output_size));
        bias.push_back(std::vector<float>(output_size, 0.0f)); // initialize bias vectors to 0.0f
        
    };
    initialize_weights();
};

//validate the input for the object constructor
void NeuralNetwork::validate_architecture(const std::vector<int>& architecture)
{
    if (architecture.size() < 2)
        throw std::invalid_argument("Network needs at least input and output layers");
    for (int size : architecture)
    {
        if(size <= 0)
        {
            throw std::invalid_argument("layer size must be a positive number");
        }
    }
}

// init weights with random numbers from a random seed
void NeuralNetwork::initialize_weights()
{
    std::random_device rd;
    unsigned int seed = rd();
    std::mt19937 gen(seed);

    for (size_t i = 1; i < architecture.size(); ++i)
    {
        int input_size = architecture[i - 1];

        float stddev = std::sqrt(2.0f / input_size);

        std::normal_distribution<float> dist(0.0f, stddev);

        for (float& weight : weights[i - 1])
        {
            weight = dist(gen);
        }
    }
}

//rectified lineral activation function
float NeuralNetwork::ReLU(float x)
{
    return std::max(0.0f,x);
}

//Convert output into normalized positive outputs
std::vector<float> NeuralNetwork::softmax(const std::vector<float>& input)
{
    std::vector<float> output(input.size(),0.0f);  
    float sum = 0;
    float max_value = input[0];

    for (float value : input)
    {
        if (value > max_value)
            max_value = value;
    }

    for(size_t i = 0; i< input.size(); i++)
    {
        output[i] = std::exp(input[i] - max_value);
        sum += output[i];
    }

    for (size_t i = 0; i< output.size(); i++)
    {
        output[i] /= sum;
    }

    return output;
}

//forwardpass of networks from inputlayer to output layer
//return non activated output layer
std::vector<float> NeuralNetwork::forwardpass(const P_state& state)
{
    float temp_sum;
    std::vector<float> input(state.data, state.data + 6);
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
    input = layer;
    return input;
}
