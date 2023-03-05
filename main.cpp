#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <random>
#include "helper/helper.h" 
#include "player/player.h"
#include "variables/variables.h" 

using namespace sf; // sf comes from SFML
using namespace std; // sf comes from SFML

// int random_position_gen(int position_dim, int percent_margin);
// Font create_font(const string& font_path);
void create_text(Text& txt, Font font, int char_size, Color color, String font_detail) ;

int main()
{
    VideoMode mode = VideoMode::getDesktopMode();
    const int WIDTH = mode.width / WIDTH_SCALE;
    const int HEIGHT = mode.height / WIDTH_SCALE + mode.height / EXTRA_HEIGHT_SCALE;
    const int WINDOW_CENTER_X = (int)(WIDTH / 2);
    const int WINDOW_CENTER_Y = (int)(HEIGHT / 2);

    // Create an SFML window
    RenderWindow dep_quadcop_window(VideoMode(WIDTH, HEIGHT), "SFML window");

    // Set the maximum FPS
    dep_quadcop_window.setFramerateLimit(FPS);

    Font Roboto_Black_Font = create_font("Roboto-Black.ttf");

    Text fps_txt("90", Roboto_Black_Font, 30);
    fps_txt.setFillColor(Color::White);

    // cout << "Modified Text: " << fps_txt.getString().toAnsiString() << std::endl;

    vector<Texture> flight_animation_obj_texture(n_FLIGHT_OBJ_IMG); 
    vector<Texture> target_animation_obj_texture(n_TARGET_OBJ_IMG);

    // flight_animation_obj_texture.resize(n_FLIGHT_OBJ_IMG);

    flight_animation_obj_texture = load_texture("Drone image", n_FLIGHT_OBJ_IMG, "../assets/balloon-flat-asset-pack/png/objects/drone-sprites/drone-");
    target_animation_obj_texture = load_texture("Target image", n_TARGET_OBJ_IMG, "../assets/balloon-flat-asset-pack/png/balloon-sprites/crazy-orange/crazy-orange-");

    /* -- Flight object -- */

    // Create the sprite for the animation
    Sprite flight_animation_sprite(flight_animation_obj_texture[0]);
    // Set the scaling factors
    flight_animation_sprite.setScale(FLIGHT_OBJ_SCALE, FLIGHT_OBJ_SCALE);
    // get the width and height of the flight obj
    FloatRect bounds_flight_obj = flight_animation_sprite.getLocalBounds();
    // set the position of the flight obj
    flight_animation_sprite.setPosition(WINDOW_CENTER_X - bounds_flight_obj.width * 0.5f * FLIGHT_OBJ_SCALE, WINDOW_CENTER_Y - bounds_flight_obj.height * 0.5f * FLIGHT_OBJ_SCALE);

    /* -- Target object -- */

    // Create the sprite for the animation
    Sprite target_animation_sprite(target_animation_obj_texture[0]);
    // Set the scaling factors
    target_animation_sprite.setScale(TARGET_OBJ_SCALE, TARGET_OBJ_SCALE);
    // get the width and height of the target obj
    FloatRect bounds_target_obj = target_animation_sprite.getLocalBounds();
    // set the position of the target obj
    target_animation_sprite.setPosition(WINDOW_CENTER_X + WIDTH/5, WINDOW_CENTER_Y - HEIGHT/4);

    // Create a clock to measure time between frames
    Clock flight_animation_clock, target_animation_clock, test_clock;
    int flight_obj_current_frame = 0, target_obj_current_frame = 0, frame_count = 0;

    // array<PID_Player, 1> players = {PID_Player()};
    
    while (dep_quadcop_window.isOpen())
    {
        Event event;
        while (dep_quadcop_window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                dep_quadcop_window.close();
            }
        }
        // Update the animation
        if (flight_animation_clock.getElapsedTime().asMilliseconds() > animation_speed)
        {
            /* -- Flight object -- */
            flight_obj_current_frame = (flight_obj_current_frame + 1) % (n_FLIGHT_OBJ_IMG - 1);
            flight_animation_sprite.setTexture(flight_animation_obj_texture[flight_obj_current_frame]);

            /* -- Target object -- */
            target_obj_current_frame = (target_obj_current_frame + 1) % (n_TARGET_OBJ_IMG - 1);
            target_animation_sprite.setTexture(target_animation_obj_texture[target_obj_current_frame]);
            flight_animation_clock.restart();
        }

        if (target_animation_clock.getElapsedTime().asSeconds() > 3.0f)
        {
            /* random */
            int target_x = random_position_gen(WIDTH, 10);
            int target_y = random_position_gen(HEIGHT, 15);

            target_animation_sprite.setPosition(target_x - bounds_target_obj.width * 0.5 * TARGET_OBJ_SCALE, target_y - bounds_target_obj.height * 0.5 * TARGET_OBJ_SCALE);
            target_animation_clock.restart();
        }

        dep_quadcop_window.clear(Color(131, 176, 181, 50));
        dep_quadcop_window.draw(flight_animation_sprite);
        dep_quadcop_window.draw(target_animation_sprite);
        dep_quadcop_window.draw(fps_txt);
        dep_quadcop_window.display();

        frame_count++;
        if (test_clock.getElapsedTime().asSeconds() > 1.0f)
        {
            /* -- fps -- */
            float fps = frame_count / test_clock.getElapsedTime().asSeconds();
            // cout << fps << endl;
            string fps_str = "fps: " + to_string(fps);
            fps_txt.setString(fps_str.substr(0, 10));
            FloatRect bounds = fps_txt.getLocalBounds();
            fps_txt.setPosition(WIDTH - bounds.width - FPS_Y, FPS_Y);
            frame_count = 0;
            test_clock.restart();
        }
    }

    printf("Hello, World \n");

    return 0;
}




