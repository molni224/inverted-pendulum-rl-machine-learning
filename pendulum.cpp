#include "pendulum.h"


Pendulum::Pendulum(sf::Vector2f direction, sf::Vector2f windowsize,float v, sf::Vector2f box_size) : direction(direction), init_direction(direction), init_v(v), init_box_pos(windowsize / 2.f)
{
    //direction
    //direction = {length,sf::radians(theta)};
    //theta = theta;
    //box
    box.setSize(box_size);
    box.setOrigin(box.getSize() / 2.f);
    box.setPosition(windowsize / 2.f);

    //ball
    ball.setRadius(BALLRADIUS);
    ball.setOrigin({BALLRADIUS,BALLRADIUS});
    ball.setPosition(box.getPosition()+direction);
    ball.setFillColor(sf::Color::Red);
    
}
void Pendulum::reset()
{
    box.setPosition(init_box_pos);
    ball.setPosition(box.getPosition()+init_direction);
    this->direction = init_direction;
    this->v = init_v;
    this->box_v = 0;
    this->box_acceleration = 0;
}

float Pendulum::get_angle()
{
    //base vector for angle calc
    sf::Vector2f BASEVECTOR {0,1};

    //vector for calcuating force direction
    sf::Vector2f calc_direction = ball.getPosition()-box.getPosition();

    float theta = calc_direction.angleTo(BASEVECTOR).asRadians();
    return theta;

}

P_state Pendulum::get_state()
{
    return P_state {
    static_cast<float>(std::sin(get_angle())),               //float sinangle;
    static_cast<float>(std::cos(get_angle())),               //float cosangle;
    this->v,                                                 //float v;
    this->box_v,                                             //float box_v;
    (this->box.getPosition().x - 10)/1900,                               //float box_pos_norm;
};
}

void Pendulum::pen_draw(sf::RenderWindow& window)
{
    //line
    line[0].position = box.getPosition();
    line[1].position = ball.getPosition();
    window.draw(line, 2, sf::PrimitiveType::Lines);
    window.draw(box);
    window.draw(ball);
}

void Pendulum::set_lenght()
{
    sf::Vector2f calc_direction = ball.getPosition()-box.getPosition();
    calc_direction = calc_direction/calc_direction.length();
    ball.setPosition(box.getPosition()+calc_direction*length);
}

void Pendulum::keyboard_controll()
{
    box_acceleration = 0;
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)))
    {
        box_acceleration = 1000.f;
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)))
    {
        box_acceleration = -1000.f;
    }

}

void Pendulum::box_movement(float dt)
{
    //std::cout << box_v << " | " << "\n";// << "|" << direction.y << "\n";
    sf::Vector2f BASE_VECTOR = {1,0};
    float d_coafficient = 0.001f;
    sf::Vector2f pos = box.getPosition();

    box_v += (box_acceleration - d_coafficient*box_v*abs(box_v))*dt;

// fix for sticking to wall
if ((pos.x >= 1910.0f && box_v > 0 && box_acceleration > 0) || (pos.x <= 10.0f && box_v < 0 && box_acceleration < 0))
{
    box_v = 0;
    box_acceleration = 0;
}
    box.move(BASE_VECTOR * box_v * dt);
    pos.x = std::clamp(box.getPosition().x,10.0f,1910.0f);

    box.setPosition(pos);
}

void Pendulum::apply_force(float force)
{
    box_acceleration = force/MASS;
}

void Pendulum::pen_movement(float dt)
{
    //more efficiency
    float local_v = this->v;
    float d_coafficient = 0.001f;
    //vector for calcuating force direction
    sf::Vector2f calc_direction = (ball.getPosition()-box.getPosition());

    //90 degrees Formula: \((x, y) \rightarrow (y, -x)\) dir.angleTo(BASEVECTOR).asDegrees()
    sf::Vector2f dir = {calc_direction.y,-calc_direction.x};
    
    //normalise and change orientation because lazy -1
    if (dir.length() != 0)
    {
        dir = -(dir/dir.length());      
    }
    else
    {
        ball.move({0.001f,0});
        calc_direction = ball.getPosition()-box.getPosition();
        //recalculating
        dir = {calc_direction.y,-calc_direction.x};
        dir = -(dir/dir.length());     
    }
    // F=ma && v = a*t
    float sin_theta = std::sin(get_angle());
    float F = sin_theta*MASS*GRAVITY;
    float a = F/MASS;
    float inertial_acceleration = (sin_theta)*(box_acceleration*MASS)/MASS;


    // vel with air resistance
    local_v += (a - d_coafficient*local_v*abs(local_v)-(inertial_acceleration))*dt;
    this->v = local_v;
    //float local_omega = local_v/length;
    //theta -= local_omega*dt;
    //sf::Vector2f pos = {length,sf::radians(theta)};
    
    

    //std::cout << get_angle() << " | ";// << "|" << direction.y << "\n";


    ball.move(local_v*dir*dt);

    //ball.setPosition(pos);
}

void Pendulum::movement(float dt)
{
    box_movement(dt);
    pen_movement(dt);
    set_lenght();
}