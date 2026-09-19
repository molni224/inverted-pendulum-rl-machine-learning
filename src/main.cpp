#include "main.h"

int main()
{
Renderer renderer;
Pendulum pendulum(sf::Vector2f{200,sf::radians(PI)}, renderer.windowSize);

NeuralNetwork network({5, 32, 32, 2});
Agent actor(network);
Environment env(pendulum);

//Pendulum pendulum((PI), renderer.windowSize);
renderer.run(env, actor);
return 0;
}









/*
P_state state = pendulum.get_state();
std::vector<float> testlist = NeuralNetwork::softmax(network.forwardpass(state));
std::cout << state.sinangle;

for (size_t i = 0; i < testlist.size(); i++)
{
    std::cout << std::setprecision(10) << testlist[i] << ' ';
};
std::cout << '\n' << std::setprecision(10) << testlist[0] + testlist[1]; 

*/