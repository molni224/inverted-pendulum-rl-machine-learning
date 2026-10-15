#ifndef STRUCTS_H
#define STRUCTS_H

#include <cmath>
#include <vector>
#include <array>

#define PI 3.14159265358979323846264338327950288419
#define GRAVITY 919.f

struct Vector2f {
    float x;
    float y;
    
    float length() const { return std::sqrt(x*x + y*y); }
    
    Vector2f& operator+=(const Vector2f& v) { x += v.x; y += v.y; return *this; }
    Vector2f& operator-=(const Vector2f& v) { x -= v.x; y -= v.y; return *this; }
    Vector2f operator+(const Vector2f& v) const { return Vector2f{x + v.x, y + v.y}; }
    Vector2f operator-(const Vector2f& v) const { return Vector2f{x - v.x, y - v.y}; }
    Vector2f operator-() const { return Vector2f{-x, -y}; }
    Vector2f operator+() const { return *this; }
    Vector2f operator*(float scalar) const { return Vector2f{x * scalar, y * scalar}; }
    Vector2f operator/(float scalar) const { return Vector2f{x / scalar, y / scalar}; }
};

struct Object2D {
    Vector2f position;
    Vector2f speed;
    Vector2f acceleration;
};

/*
        |\  <- Anchor
        | \ 
    cos |  \ 
        |   \ 
        |____O  <- Bob
          sin
*/
struct PendulumState {
    float sin;                   
    float cos;                  
    float bob_speed;             
    float anchor_speed;          
    float anchor_posx_norm;      
                                 
    PendulumState(float sin, float cos, float bob_speed, float anchor_speed, float anchor_pos)
        : sin(sin), cos(cos), bob_speed(bob_speed), anchor_speed(anchor_speed), anchor_posx_norm(anchor_pos) {}

    std::array<float, 5> get_attributes() const{
        return {sin, cos, bob_speed, anchor_speed, anchor_posx_norm};
    }
};                               

struct ForwardsCache {
    std::vector<PendulumState> inputs;
    std::vector<std::vector<float>> pre_activation;
    std::vector<std::vector<float>> activation;

    void clear() {
        inputs.clear();
        for (size_t i = 0; i < inputs.size(); i++) {
            pre_activation[i].clear();
            activation[i].clear();
        
        }
    }
};

#endif