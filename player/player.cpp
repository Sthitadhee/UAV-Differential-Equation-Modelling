#include <SFML/Graphics.hpp>

#include <iostream>
#include <player.h>

Player::Player():
    thruster_mean_(0.04f),
    angle_(0),
    angular_speed_(0),
    angular_acceleration_(0),
    x_position_(400),
    x_speed_(0),
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
        double x_speed,
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
        x_speed_(x_speed),
        x_acceleration_(x_acceleration),
        y_position_(y_position),
        y_velocity_(y_velocity),
        y_acceleration_(y_acceleration),
        target_counter_(target_counter),
        is_dead_(is_dead) {};

PID_Player::PID_Player():
    name("PID"),
    alpha(50),// transparency value of the uav
    thruster_amplitude(0.04),
    diff_amplitude(0.003),
    dt(1/60){};

PID_Player::PID_Player(string a, int b, double c, double d, double e):
    name(a),
    alpha(b),// transparency value of the uav
    thruster_amplitude(c),
    diff_amplitude(d),
    dt(e){};

void PID_Player::act(double a, double b, double c, double d, double e) {
    // def act(self, obs):
        // thruster_left = self.thruster_mean
        // thruster_right = self.thruster_mean

        // error_x, xd, error_y, yd, a, ad = obs

        // ac = self.xPID.compute(-error_x, self.dt)

        // error_a = ac - a
        // action1 = self.aPID.compute(-error_a, self.dt)

        // ydc = self.yPID.compute(error_y, self.dt)
        // error_yd = ydc - yd
        // action0 = self.ydPID.compute(-error_yd, self.dt)

        // thruster_left += action0 * self.thruster_amplitude
        // thruster_right += action0 * self.thruster_amplitude
        // thruster_left += action1 * self.diff_amplitude
        // thruster_right -= action1 * self.diff_amplitude

        // attitude
        // double xPID = PID(0.2, 0, 0.2, 25, -25);
        // double aPID = PID(0.02, 0, 0.01, 1, -1);

        //altitude
        // double yPID = PID(2.5, 0, 1.5, 100, -100F);
        // double ydPID = PID(1, 0, 0, 1, -1);
};

PID::PID(double a, double b, double c, double d, double e):
    kp(a), ki(b), kd(c), saturation_max(d), saturation_min(e), error_last(0), integral_error(0) {};

double PID::compute(double error, double dt) 
{
    double derivative_error = (error - this->error_last)/dt;
    this->integral_error += error * dt;
    double output = this->kp * error + this->ki * this->integral_error + this->kd * derivative_error;
    this->error_last = error;
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