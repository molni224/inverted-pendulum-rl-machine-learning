#include "simulation.h"

int main() {
    // Neural Network
    NeuralNetwork network({5, 32, 32, 2});
    Agent actor(network);

    // Pendulum
    Object2D anchor_init = {{1920.0f / 2.0f, 1080.0f / 2.0f}, {0,0}, {0,0}};
    Object2D bob_init = {{1920.0f / 2.0f, 1080.0f / 2.0f + 200.0f}, {0,0}, {0,0}};
    Pendulum pendulum(anchor_init, bob_init);
    
    // Simulation
    Simulation sim(pendulum, actor);
    sim.run();
    
    return 0;
}
