#ifndef PENDULUM_H
#define PENDULUM_H

#include "structs.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>


// init: rope_direction, anchor position, bob_speed  (only for reset)
// anchor: pos, speed, acceleration 
// bob: pos, speed
class Pendulum {
private:
    static constexpr float ANCHOR_DRAG_COEFF 0.001f;
    static constexpr float BOB_DRAG_COEFF 0.001f;

    // Doesnt matter for movement but helps understanding equations (Can be any value)
    static constexpr float ANCHOR_MASS 1;
    static constexpr float BOB_MASS 1;

    static constexpr float ROPE_LENGTH = 200;
    static constexpr float TRACK_LENGTH = 1900;

    // Initital values for reset backup
    Object2D init_anchor;
    Object2D init_bob;

    Object2D anchor;
    Object2D bob;

    void move_anchor(float dt);
    void move_bob(float dt);
    void correct_length();

public:
    Pendulum(Object2D anchor, Object2D bob);

    Object2D& get_anchor() {return anchor;}
    Object2D& get_bob() {return bob;}
    PendulumState get_current_state();

    void reset(float dt);
    void move(float dt);
    void apply_force_anchor(float force);

}


class Pendulum {
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


    void set_lenght(); //!!! TODO

    void keyboard_controll();

    void apply_force(float force);
    void pen_movement(float dt);
    void box_movement(float dt);
    void movement(float dt);
    
};


#endif