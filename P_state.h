#ifndef P_State_H
#define P_State_H

union P_state {
struct 
{
    float sinangle; //sin and cos for continues smooth values
    float cosangle;
    float v;
    float box_v;
    float box_pos_norm;
};
    float data[5];
};

struct StepResult
{
    P_state state;
    float reward;
    bool done;
};

#endif