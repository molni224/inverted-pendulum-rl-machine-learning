#ifndef PENDULUM_H
#define PENDULUM_H

#include "structs.h"
#include <cmath>
#include <algorithm>


class Pendulum {
private:
    static constexpr float ANCHOR_DRAG_COEFF = 0.001f;
    static constexpr float BOB_DRAG_COEFF = 0.001f;

    // Doesn't matter for movement but helps understanding equations (Can be any value)
    static constexpr float ANCHOR_MASS = 1.0f;
    static constexpr float BOB_MASS = 1.0f;

    static constexpr float ROPE_LENGTH = 200;
    static constexpr float TRACK_LENGTH = 1900;

    // Initial values for reset backup
    Object2D init_anchor;
    Object2D init_bob;

    Object2D anchor;
    Object2D bob;

    void move_anchor(float dt);
    void move_bob(float dt);
    void correct_length();

public:
    Pendulum(Object2D anchor, Object2D bob);

    const Object2D& get_anchor() const {return anchor;}
    const Object2D& get_bob() const {return bob;}
    PendulumState get_current_state() const;

    void reset();
    void move(float dt);
    void apply_force_to_anchor(float force);

};

#endif