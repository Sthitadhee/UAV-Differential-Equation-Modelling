#include <string>
using namespace std;

class Player
{
public:
    double thruster_mean_;
    double angle_;
    double angular_speed_;
    double angular_acceleration_;
    double x_position_;
    double x_speed_;
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
        double x_speed,
        double x_acceleration,
        double y_position,
        double y_velocity,
        double y_acceleration,
        int target_counter,
        bool is_dead
    );
        
};

class PID_Player: public Player {
    public:
        string name;
        int alpha;// transparency value of the uav
        double thruster_amplitude;
        double diff_amplitude;
        double dt;

        PID_Player();

        PID_Player(
            string a,
            int b,
            double c,
            double d, 
            double e
        );

        void act(double a, double b, double c, double d, double e);
};

class PID {
    public:
        double kp;
        double ki;
        double kd; 
        double error_last;
        double integral_error;
        double saturation_max;
        double saturation_min;

    PID(double a, double b, double c, double d, double e);

    double compute(double error, double dt);
};