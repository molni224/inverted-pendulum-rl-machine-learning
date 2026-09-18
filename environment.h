#include "pendulum.h"
#include "P_state.h"

class Environment
{
private:
    Pendulum pendulum;
    bool done = false;
public:
    Environment(Pendulum& pendulum);
    P_state reset();
    Pendulum& get_pendulum(){return pendulum;};
    float get_reward(const P_state& state);
    void pen_draw(sf::RenderWindow& window);
    StepResult step(float force, float dt);

};