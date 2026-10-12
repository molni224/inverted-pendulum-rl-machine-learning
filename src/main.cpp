#include "renderer.h"
#include "network.h"

int main() {
    Simulation sim;
    
    Renderer renderer;
    Pendulum pendulum(sf::Vector2f{200,sf::radians(PI)}, renderer.windowSize);

    NeuralNetwork network({5, 32, 32, 2});
    Agent actor(network);
    Environment env(pendulum);

    //Pendulum pendulum((PI), renderer.windowSize);
    renderer.run(env, actor);
    return 0;
}
