#ifndef STRUCTS_H
#define STRUCTs_H

#include <cmath>
#include <vector>

#define PI 3.14159265358979323846264338327950288419
#define GRAVITY 919.f
#define ANCHOR_DRAG_COEFF 0.001f
#define BOB_DRAG_COEFF 0.001f



struct Vector2f {
    float x;
    float y;

    float length() {
        return std::sqrt(x*x + y*y);
    }

    // Összeadás és értékadás (v1 += v2)
    Vector2f& operator+=(const Vector2f& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    // Kivonás és értékadás (v1 -= v2)
    Vector2f& operator-=(const Vector2f& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    
    // Sima összeadás (v3 = v1 + v2)
    Vector2f operator+(const Vector2f& v) const {
        return Vector2f{x + v.x, y + v.y};
    }

    // Sima kivonás (v3 = v1 - v2)
    Vector2f operator-(const Vector2f& v) const {
        return Vector2f{x - v.x, y - v.y};
    }

    Vector2f operator-() const {
        return Vector2f{-x, -y};
    }

    Vector2f operator+() const {
        return *this;
    }
}; 

struct Object2D {
    Vector2f position;
    Vector2f speed;
    Vector2f acceleration;

};

struct PendulumState {
    float sin;                   //        |\  <- Anchor
    float cos;                   //        | \ 
    float bob_speed;             //    cos |  \ 
    float anchor_speed;          //        |   \ 
    float anchor_posx_norm;      //        |____O  <- Bob
                                 //         sin
    PendulumState(float sin, float cos, float bob_speed, float anchor_speed, float anchor_pos)
        : sin(sin), cos(cos), bob_speed(bob_speed), anchor_speed(anchor_speed), anchor_posc_norm(anchor_pos) {}
};                               


struct StepResult {
    PendulumState state;
    float reward;
    bool is_done;
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