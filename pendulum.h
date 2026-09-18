#ifndef PENDULUM_H
#define PENDULUM_H
#include "P_state.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>
#define GRAVITY 919.f
#define MASS 1
#define BOX_MASS 1




class Pendulum
{
private:
    sf::Vector2f init_direction;
    sf::Vector2f init_box_pos;
    float init_v;
    sf::Vertex line[2];
    sf::CircleShape ball;
    static constexpr sf::Vector2f box_size = {20.f,20.f};
    static constexpr float BALLRADIUS = 25.f;
    static constexpr float length = 200;
    float v = 0;
    //float theta;
    sf::RectangleShape box;
    float box_acceleration = 0;
    float box_v = 0;
    sf::Vector2f direction;


public:

    Pendulum(sf::Vector2f direction, sf::Vector2f windowsize,float v = 0.f, sf::Vector2f box_size = {20.f, 20.f});

    float get_angle();
    P_state get_state();

    void pen_draw(sf::RenderWindow& window);
    const sf::RectangleShape& get_box() {return box;};
    const sf::CircleShape& get_ball() {return ball;};
    const sf::Vector2f get_direction() {return direction;};
    void reset();


    void set_lenght();
    void keyboard_controll();

    void apply_force(float force);
    void pen_movement(float dt);
    void box_movement(float dt);
    void movement(float dt);
    
};


#endif