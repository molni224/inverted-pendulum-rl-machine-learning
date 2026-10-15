#include "pendulum.h"

Pendulum::Pendulum(Object2D anchor, Object2D bob) : init_anchor(anchor), init_bob(bob), anchor(anchor), bob(bob) {}

PendulumState Pendulum::get_current_state() const {
    float sin = fabs(anchor.position.x - bob.position.x) / ROPE_LENGTH;
    float cos = fabs(anchor.position.y - bob.position.y) / ROPE_LENGTH;
    float anchor_posx_norm = anchor.position.x / TRACK_LENGTH;  // Normalized position to the track length between 0 and 1 (left is 0 right is 1)

    PendulumState state(sin, cos, bob.speed.length(), anchor.speed.length(), anchor_posx_norm);

    return state;
}

void Pendulum::reset() {
    anchor = init_anchor;
    bob = init_bob;
}

void Pendulum::move_anchor(float dt) {
    Vector2f drag_acceleration = anchor.speed * fabs(anchor.speed.x) * ANCHOR_DRAG_COEFF; // speed is squared but we need the direction with the sign
    anchor.speed += (anchor.acceleration - drag_acceleration) * dt;
    anchor.position += anchor.speed * dt;
}

void Pendulum::move_bob(float dt) {
    Vector2f anchor_to_bob = bob.position - anchor.position;

    // Tangent vector (perpendicular to the rope)
    Vector2f tangent = {-anchor_to_bob.y, anchor_to_bob.x};
    tangent = tangent / tangent.length(); // Normalize

    Vector2f gravity_acceleration = {0.0f, GRAVITY};
    Vector2f inertial_acceleration = {-anchor.acceleration.x, 0.0f};
    Vector2f total_external_accel = gravity_acceleration + inertial_acceleration;

    float tangential_scalar = (total_external_accel.x * tangent.x) + (total_external_accel.y * tangent.y);
    Vector2f tangential_accel_vector = tangent * tangential_scalar;

    // Drag
    Vector2f drag = bob.speed * fabs(bob.speed.length()) * BOB_DRAG_COEFF;

    // Apply acceleration
    this->bob.speed += (tangential_accel_vector - drag) * dt;
    this->bob.position += this->bob.speed * dt;
}

void Pendulum::correct_length() {
    Vector2f anchor_to_bob = bob.position - anchor.position;       
    anchor_to_bob = anchor_to_bob / anchor_to_bob.length();  // Normalize the vector
    
    bob.position= anchor.position + anchor_to_bob * ROPE_LENGTH;
}

void Pendulum::move(float dt) {
    move_anchor(dt);
    move_bob(dt);
    correct_length();
}

void Pendulum::apply_force_to_anchor(float force) {
    anchor.acceleration.x = force / ANCHOR_MASS;
}