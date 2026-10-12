#ifndef RENDERER_H
#define RENDERER_H

#include "trajectory.h"
#include "pendulum.h"
#include "agent.h"
#include "environment.h"

class Renderer {
private:
    sf::RenderWindow window;

public:
    float dt;
    sf::Vector2f windowSize;
    Renderer();
    sf::RenderWindow& get_window();
    void run(Environment& env, Agent& actor);
};




#endif