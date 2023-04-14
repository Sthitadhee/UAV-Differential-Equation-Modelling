/*
Author: Sthitadhee Panthadas
All the class declarations of PID, Player
*/

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

struct Thrust {
    double thrust_left, thrust_right;
};

class PID {

    double error_last;
    public:
        double kp;
        double ki;
        double kd; 
        double integral_error;
        double saturation_max;
        double saturation_min;

    PID(double a, double b, double c, double d, double e);

    double compute(double error, double dt);

    void set_error_last(double error);
};

class Player
{
public:
    double thruster_mean_;
    double angle_;
    double angular_speed_;
    double angular_acceleration_;
    double x_position_;
    double x_velocity_;
    double x_acceleration_;
    double y_position_;
    double y_velocity_;
    double y_acceleration_;
    int target_counter_;
    bool is_dead_;

public:
    Player();
    
    Player(
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
    );

    void set_position(double position_x, double position_y);
        
};

class PID_Player: public Player {
    public:
        string name;
        int alpha;// transparency value of the uav
        double thruster_amplitude;
        double diff_amplitude;
        double dt;
        PID xPID;
        PID aPID;
        PID yPID;
        PID dyPID; //y (thrust) difference of delta y??

        PID_Player();

        PID_Player(
            string a,
            int b,
            double c,
            double d, 
            double e
        );

        Thrust act(double a, double b, double c, double d);
};

#endif