#include "main.h"

int main()
{
Renderer renderer;
NeuralNetwork network({5, 32, 32, 2});
Agent actor(network);
Pendulum pendulum(sf::Vector2f{200,sf::radians(PI)}, renderer.windowSize);
Environment env(pendulum);
P_state state = pendulum.get_state();
std::cout << state.sinangle;
std::vector<float> testlist = NeuralNetwork::softmax(network.forwardpass(state));

//Pendulum pendulum((PI), renderer.windowSize);
renderer.run(env, actor);
return 0;
}




/*

for (size_t i = 0; i < testlist.size(); i++)
{
    std::cout << std::setprecision(10) << testlist[i] << ' ';
};
std::cout << '\n' << std::setprecision(10) << testlist[0] + testlist[1]; 

*/