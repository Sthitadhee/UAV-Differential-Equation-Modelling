#include "player.h"


Player::Player():
    thruster_mean_(0.04),
    angle_(0),
    angular_speed_(0),
    angular_acceleration_(0),
    x_position_(400),
    x_velocity_(0),
    x_acceleration_(0),
    y_position_(400),
    y_velocity_(0),
    y_acceleration_(0),
    target_counter_(0),
    is_dead_(false) {};

Player::Player(
        double thruster_mean,
        double angle,
        double angular_speed,
        double angular_acceleration,
        double x_position,
        double x_velocity,
        double x_acceleration,
        double y_position,
        double y_velocity,
        double y_acceleration,
        int target_counter,
        bool is_dead
    ): 
        thruster_mean_(thruster_mean),
        angle_(angle),
        angular_speed_(angular_speed),
        angular_acceleration_(angular_acceleration),
        x_position_(x_position),
        x_velocity_(x_velocity),
        x_acceleration_(x_acceleration),
        y_position_(y_position),
        y_velocity_(y_velocity),
        y_acceleration_(y_acceleration),
        target_counter_(target_counter),
        is_dead_(is_dead) {};

void Player::set_position(double position_x, double position_y) {
    this->x_position_ = position_x, this->y_position_ = position_y;
};

PID_Player::PID_Player():
    name("PID"),
    alpha(50),// transparency value of the uav
    thruster_amplitude(0.04),
    diff_amplitude(0.003),
    dt(1.0/60),
    xPID(PID(0.2, 0, 0.2, 25, -25)),
    aPID(PID(0.02, 0, 0.01, 1, -1)),
    yPID(PID(2.5, 0, 1.5, 100, -100)),
    dyPID(PID(1.0, 0, 0, 1.0, -1)){};

PID_Player::PID_Player(string a, int b, double c, double d, double e):
    name(a),
    alpha(b),// transparency value of the uav
    thruster_amplitude(c),
    diff_amplitude(d),
    dt(e),
    xPID(PID(0.2, 0, 0.2, 25, -25)),
    aPID(PID(0.02, 0, 0.01, 1, -1)),
    yPID(PID(2.5, 0, 1.5, 100, -100)),
    dyPID(PID(1.0, 0, 0, 1, -1)){};


Thrust PID_Player::act(double a, double b, double c, double d) {
    // def act(self, obs):
    double thrust_left = this->thruster_mean_, thrust_right = this->thruster_mean_;
    double error_x = a, error_y = b, dy = c, angle = d;
    // What is this ac??
    double ac = this->xPID.compute(-error_x, this->dt);
    double error_amplitude = ac - angle;
    double action1 = this->aPID.compute(-error_amplitude, this->dt);
    

    double dyc = this->yPID.compute(error_y, this->dt);
    double error_dy = dyc - dy;

    double action0 = this->dyPID.compute(-error_dy, this->dt);

    thrust_left += action0 * this->thruster_amplitude;
    thrust_right += action0 * this->thruster_amplitude;
    thrust_left += action1 * this->diff_amplitude;
    thrust_right -= action1 * this->diff_amplitude;


    Thrust thrust;
    thrust.thrust_left = thrust_left;
    thrust.thrust_right = thrust_right;
    return thrust;
};

PID::PID(double a, double b, double c, double d, double e):
    kp(a), ki(b), kd(c), saturation_max(d), saturation_min(e), error_last(0), integral_error(0) {};

void PID::set_error_last(double error) {
    this->error_last = error;
}

double PID::compute(double error, double dt) 
{
    double derivative_error = (error - this->error_last)/dt;
    this->integral_error += error * dt;
    double output = this->kp * error + this->ki * this->integral_error + this->kd * derivative_error;
    this->set_error_last(error);
    if(output > this->saturation_max && this->saturation_max) 
    {
        output = this->saturation_max;
    }
    else if(output < this->saturation_min && this->saturation_min)
    {
        output = this->saturation_min;
    }
    return output;
};