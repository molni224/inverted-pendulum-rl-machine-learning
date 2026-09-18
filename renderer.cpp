#include "renderer.h"


Renderer::Renderer(): window(sf::VideoMode({1920, 1080}), "Pendulum")
{
    windowSize = sf::Vector2f(window.getSize());
    window.setFramerateLimit(60);
}

sf::RenderWindow& Renderer::get_window()
{
    return window;
}


void Renderer::run(Environment& env, Agent& actor)
{
    sf::Clock clock;
    P_state state = env.reset();

while (window.isOpen())
{
    while (const std::optional<sf::Event> event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
    }

    window.clear();
    
    // 3. Get dt as SECONDS (e.g., 0.016 at 60 FPS) and restart the clock
    float dt = clock.restart().asSeconds();

    float force = actor.get_action(state, 750.0f);

    StepResult result = env.step(force, dt);
    state = result.state;
    float reward = result.reward;
    bool done = result.done;


    env.pen_draw(window);

if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)))
    {
        state = env.reset();
    }
    
    window.display();
}
}