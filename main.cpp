/*
Author: Sthitadhee Panthadas
Main game loop file
*/

#include <iostream>
#include <string>
#include <random>
#include "player/player.h"
#include "variables/variables.h"
#include "helper/helper.h"
#include <utility>
#include <fstream>

int main()
{
    // Create an SFML window
    RenderWindow dep_quadcop_window(VideoMode(WIDTH, HEIGHT), "SFML window");

    // Set the maximum FPS
    dep_quadcop_window.setFramerateLimit(FPS);

    Font Roboto_Black_Font = create_font("Roboto-Black.ttf");

    Text fps_txt("60.00", Roboto_Black_Font, 30);
    FloatRect bounds = fps_txt.getLocalBounds();
    create_text(fps_txt, Color::White, WIDTH, FPS_Y, bounds.width);

    // cout << "Modified Text: " << fps_txt.getString().toAnsiString() << std::endl;

    vector<Texture> flight_animation_obj_texture(n_FLIGHT_OBJ_IMG);
    vector<Texture> target_animation_obj_texture(n_TARGET_OBJ_IMG);
    Texture cloud_obj_texture;

    // @TODO 1: why cant i initiate in the same line?
    flight_animation_obj_texture = load_texture("Drone image", n_FLIGHT_OBJ_IMG, "../assets/balloon-flat-asset-pack/png/objects/drone-sprites/drone-");
    target_animation_obj_texture = load_texture("Target image", n_TARGET_OBJ_IMG, "../assets/balloon-flat-asset-pack/png/balloon-sprites/crazy-orange/crazy-orange-");

    // Load the cloud texture from a file
    if (!cloud_obj_texture.loadFromFile("../assets/balloon-flat-asset-pack/png/background-elements/cloud-1.png"))
    {
        return 1;
    }

    /* -- Flight object -- */
    // // Create the sprite for the animation
    Sprite flight_animation_sprite(flight_animation_obj_texture[0]);
    // Set the scaling factors
    flight_animation_sprite.setScale(FLIGHT_OBJ_SCALE, FLIGHT_OBJ_SCALE);
    // get the width and height of the flight obj
    FloatRect bounds_flight_obj = flight_animation_sprite.getLocalBounds();
    // set the position of the flight obj
    flight_animation_sprite.setPosition(WINDOW_CENTER_X - bounds_flight_obj.width * 0.5f * FLIGHT_OBJ_SCALE, WINDOW_CENTER_Y - bounds_flight_obj.height * 0.5f * FLIGHT_OBJ_SCALE);

    CircleShape point1(2.f);
    CircleShape point2(2.f);
    point1.setPosition(WINDOW_CENTER_X, WINDOW_CENTER_Y);
    point1.setFillColor(Color::Red);

    IntRect r1(WINDOW_CENTER_X - bounds_flight_obj.width * 0.5f * FLIGHT_OBJ_SCALE, WINDOW_CENTER_Y - bounds_flight_obj.height * 0.5f * FLIGHT_OBJ_SCALE, bounds_flight_obj.width * FLIGHT_OBJ_SCALE, bounds_flight_obj.height * FLIGHT_OBJ_SCALE);

    // @TODO 2: why does this draw the flight obj?
    // create_sprite(flight_animation_sprite, FLIGHT_OBJ_SCALE, WINDOW_CENTER_X, WINDOW_CENTER_Y);

    /* -- Target object -- */

    // Create the sprite for the animation
    Sprite target_animation_sprite(target_animation_obj_texture[0]);
    // Set the scaling factors
    target_animation_sprite.setScale(TARGET_OBJ_SCALE, TARGET_OBJ_SCALE);
    // get the width and height of the target obj
    FloatRect bounds_target_obj = target_animation_sprite.getLocalBounds();
    
    // set the position of the target obj
    // target_animation_sprite.setPosition(WINDOW_CENTER_X + WIDTH / 5, WINDOW_CENTER_Y - HEIGHT / 4);
    double target_positions_x[n_targets + 1];
    double target_positions_y[n_targets + 1];
    bool show_graph = false;

    for (int i = 0; i < n_targets + 1; i++)
    {
        int target_x = random_position_gen(WIDTH, 30);
        int target_y = random_position_gen(HEIGHT, 40);

        target_positions_x[i] = target_x - bounds_target_obj.width * 0.5 * TARGET_OBJ_SCALE;
        target_positions_y[i] = target_y - bounds_target_obj.height * 0.5 * TARGET_OBJ_SCALE;

        // target_animation_sprite.setPosition(target_x - bounds_target_obj.width * 0.5 * TARGET_OBJ_SCALE + 10, target_y - bounds_target_obj.height * 0.5 * TARGET_OBJ_SCALE + 10);
    }

    // Create a clock to measure time between frames
    Clock flight_animation_clock, target_animation_clock, test_clock;
    int flight_obj_current_frame = 0, target_obj_current_frame = 0, frame_count = 0;

    /* -- cloud 1 -- */
    Sprite cloud_1(cloud_obj_texture);
    cloud_1.setScale(2, 2);
    cloud_1.setPosition(x_cloud1, y_cloud1);

    // Initiate player
    PID_Player players[1] = {PID_Player()};

    // set player initial position in the center of the window
    players[0].set_position(WINDOW_CENTER_X, WINDOW_CENTER_Y);
    
    // initiate required parameters
    double previous_angle = 0;
    double dist_btwn_target_flight_obj = 0;
    int step = 1;
    ofstream file("output.csv");

    // game loop
    while (dep_quadcop_window.isOpen())
    {
        Event event;
        // handle window close event
        while (dep_quadcop_window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                dep_quadcop_window.close();
            }
        }

        // handle what happens after n_targets
        // done to bring the game to an end and Uav to settle
        if (players[0].target_counter_ > n_targets)
        {
            dep_quadcop_window.clear(Color(131, 176, 181, 50));
            dep_quadcop_window.draw(cloud_1);
            dep_quadcop_window.draw(flight_animation_sprite);
            dep_quadcop_window.draw(fps_txt);
            dep_quadcop_window.display();
        }
        else
        {
            // target_animation_sprite.setPosition(target_positions_x[players[0].target_counter_], target_positions_y[players[0].target_counter_]);
            target_animation_sprite.setPosition(800, 600);
        }
        // Update the animation of flight obj and target in the game loop
        if (flight_animation_clock.getElapsedTime().asMilliseconds() > animation_speed)
        {
            /* -- Flight object texture-- */
            flight_obj_current_frame = (flight_obj_current_frame + 1) % (n_FLIGHT_OBJ_IMG - 1);
            flight_animation_sprite.setTexture(flight_animation_obj_texture[flight_obj_current_frame]);

            /* -- Target object texture -- */
            target_obj_current_frame = (target_obj_current_frame + 1) % (n_TARGET_OBJ_IMG - 1);
            target_animation_sprite.setTexture(target_animation_obj_texture[target_obj_current_frame]);
            flight_animation_clock.restart();
        }

        // cloud 1 animation
        if (x_cloud1 > WIDTH)
        {
            x_cloud1 = -cloud_1.getPosition().x / 2;
        }
        else
        {
            x_cloud1 += speed_cloud1;
        }
        cloud_1.setPosition(x_cloud1, y_cloud1);

        // clears the window for redrawing
        dep_quadcop_window.clear(Color(131, 176, 181, 50));

        dep_quadcop_window.draw(cloud_1);

        int P = sizeof(players) / sizeof(players[0]);

        // loop through player 
        // For project only 1 autonomous player is used
        for (int i = 0; i < P; i++)
        {
            if (players[0].target_counter_ <= n_targets)
            {
                dep_quadcop_window.draw(target_animation_sprite);
            }
            // initiate the required properties and parameters for the physics simulation
            players[0].y_acceleration_ = GRAVITY;
            players[0].x_acceleration_ = 0;
            players[0].angular_acceleration_ = 0;
            double thrust_left, thrust_right;
            double target_position_x = target_animation_sprite.getPosition().x + target_animation_sprite.getLocalBounds().width / 2;
            double target_position_y = target_animation_sprite.getPosition().y;

            // update the thrust_left and thrust_right
            if (players[0].name == "PID")
            {
                Thrust thrust = players[0].act(
                    target_position_x - (players[0].x_position_ + 25),
                    target_position_y - (players[0].y_position_ + 0),
                    players[0].y_velocity_,
                    players[0].angle_);
                thrust_left = thrust.thrust_left, thrust_right = thrust.thrust_right;
            }
            // update the physics variables
            players[0].x_acceleration_ += (-(thrust_left + thrust_right) * sin(players[0].angle_ * M_PI / 180)) / MASS_OF_OBJ;
            players[0].y_acceleration_ += (-(thrust_left + thrust_right) * cos(players[0].angle_ * M_PI / 180)) / MASS_OF_OBJ;
            players[0].angular_acceleration_ = ARM * (thrust_right - thrust_left) / MASS_OF_OBJ;

            players[0].x_velocity_ += players[0].x_acceleration_;
            players[0].y_velocity_ += players[0].y_acceleration_;
            players[0].angular_speed_ += players[0].angular_acceleration_;

            players[0].x_position_ += players[0].x_velocity_;
            players[0].y_position_ += players[0].y_velocity_;
            players[0].angle_ += players[0].angular_speed_;

            // error calculation using distance btn target and flight obj
            dist_btwn_target_flight_obj = cal_dist_btn_2_points(players[0].x_position_, target_position_x, players[0].y_position_, target_position_y);


            // taking 1000 samples more to see the stabilisation of the UAV in our graph
            // here the data of the updates are stored for graphing
            if (players[0].target_counter_ == 0 || step <= 1000)
            {
                cout << "working" << endl;
                file
                    << players[0].x_acceleration_
                    << ","
                    << players[0].y_acceleration_
                    << ","
                    << players[0].x_velocity_
                    << ","
                    << players[0].y_velocity_
                    << ","
                    << (players[0].x_position_ - WINDOW_CENTER_X)
                    << ","
                    << (players[0].y_position_ - WINDOW_CENTER_Y)
                    << "\n";
                // cout << players[0].angle_ << " " << previous_angle << " " << -players[0].angle_ + previous_angle << endl;
                if(players[0].target_counter_ == 0) {
                    step = 0;
                    cout << "zero" << endl;
                }
            }

            // tells when the UAV has reached the target
            if (dist_btwn_target_flight_obj < 40)
            {
                players[0].target_counter_ += 1;
            }
            else if (dist_btwn_target_flight_obj > 1000)
            {
                // players[0].is_dead_ = true;
            }

            // player draw
            // Update sprite frame based on current step
            // int frame_index = static_cast<int>(step * 0.3) % flight_animation_obj_texture.size();
            step++;
            // flight_animation_sprite.setTexture(flight_animation_obj_texture[frame_index]);
            
            // calculates the angle of the rotation required
            flight_animation_sprite.rotate(-players[0].angle_ + previous_angle);
            flight_animation_sprite.setOrigin(flight_animation_sprite.getLocalBounds().width / 2, flight_animation_sprite.getLocalBounds().height / 2);
            previous_angle = players[0].angle_;

            // updates the position of the UAV
            flight_animation_sprite.setPosition(
                players[0].x_position_,
                players[0].y_position_);
            dep_quadcop_window.draw(flight_animation_sprite);
        }

        // finally draws the other sprites
        dep_quadcop_window.draw(flight_animation_sprite);
        dep_quadcop_window.draw(fps_txt);
        dep_quadcop_window.draw(point1);
        dep_quadcop_window.draw(point2);
        // dep_quadcop_window.draw(r1);
        dep_quadcop_window.display();

        frame_count++;
        // for frame calculation and setting on the window
        if (test_clock.getElapsedTime().asSeconds() > 1.0f)
        {
            /* -- fps -- */
            double fps = frame_count / test_clock.getElapsedTime().asSeconds();
            string fps_str = to_string(fps);
            fps_txt.setString(fps_str.substr(0, 5));

            fps_txt.setPosition(WIDTH - bounds.width - FPS_Y, FPS_Y);
            frame_count = 0;
            test_clock.restart();
        }
    }
    // close the file object
    file.close();
    
    return 0;
}
