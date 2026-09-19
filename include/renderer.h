#ifndef RENDERER_H
#define RENDERER_H


#include "pendulum.h"
#include "agent.h"
#include "environment.h"
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844

class Pendulum;

class Renderer
{
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