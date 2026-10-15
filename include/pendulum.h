#ifndef PENDULUM_H
#define PENDULUM_H
#include "structs.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>





class Pendulum
{
private:
    static constexpr float GRAVITY = 919.f;
    static constexpr int MASS = 1;
    static constexpr int BOX_MASS = 1;
    static constexpr float BALLRADIUS = 25.f;
    static constexpr float length = 200;
    static constexpr sf::Vector2f box_size = {20.f,20.f};

    sf::Vector2f init_direction;
    sf::Vector2f init_box_pos;
    float init_v;

    sf::CircleShape ball;
    sf::RectangleShape box;
    sf::Vector2f direction;
    float v = 0;
    float box_acceleration = 0;
    float box_v = 0;


public:

    Pendulum(sf::Vector2f direction, sf::Vector2f windowsize,float v = 0.f, sf::Vector2f box_size = {20.f, 20.f});

    float get_angle() const;
    P_state get_state() const;

    void pen_draw(sf::RenderWindow& window) const;
    const sf::RectangleShape& get_box() const {return box;};
    const sf::CircleShape& get_ball() const {return ball;};
    sf::Vector2f get_direction() const {return direction;};
    void reset();


    void set_lenght();
    void keyboard_controll();

    void apply_force(float force);
    void pen_movement(float dt);
    void box_movement(float dt);
    void movement(float dt);
    
};


#endif