#include "renderer.h"

Renderer::Renderer(sf::RenderWindow& window, Pendulum& pendulum) 
    : window(window), pendulum(pendulum) 
{
    config_anchor();
    config_bob();
}

void Renderer::config_anchor() {
    anchor.setSize({ANCHOR_SIZE, ANCHOR_SIZE});
    anchor.setOrigin(anchor.getSize() / 2.0f);
    anchor.setPosition({pendulum.get_anchor().position.x, pendulum.get_anchor().position.y});
}

void Renderer::config_bob() {
    bob.setRadius(BOB_RADIUS);
    bob.setOrigin({BOB_RADIUS, BOB_RADIUS});
    bob.setFillColor(sf::Color::Red);
}

void Renderer::update_parts_position() {
    // Anchor
    anchor.setPosition({pendulum.get_anchor().position.x, pendulum.get_anchor().position.y});

    // Rope
    rope[0].position = {pendulum.get_anchor().position.x, pendulum.get_anchor().position.y};
    rope[1].position = {pendulum.get_bob().position.x, pendulum.get_bob().position.y};

    // Bob
    bob.setPosition({pendulum.get_bob().position.x, pendulum.get_bob().position.y});
}

void Renderer::render() {
    window.clear();
    update_parts_position();

    window.draw(rope, 2, sf::PrimitiveType::Lines);
    window.draw(anchor);
    window.draw(bob);
    
    window.display();
}