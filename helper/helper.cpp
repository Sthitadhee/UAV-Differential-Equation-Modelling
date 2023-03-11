#include "helper.h"

int random_position_gen(int position_dim, int percent_margin)
{
    random_device seed;  // Obtain a random number from hardware
    mt19937 gen(seed()); // Seed the generator

    int min = (int)(position_dim / percent_margin);
    int max = (int)(position_dim - position_dim / percent_margin);
    uniform_int_distribution<> distr(min, max);
    int random_value = distr(gen);

    return random_value;
}

Font create_font(const string &font_path)
{
    // Load font type
    Font Font_Type;
    if (!Font_Type.loadFromFile("../assets/fonts/" + font_path))
    {
        std::cerr << "Error loading Font - " + font_path << std::endl;
        exit(EXIT_FAILURE);
    }
    return Font_Type;
}

vector<Texture> load_texture(string name, int n_img, string file_path)
{
    vector<Texture> flight_animation_obj_texture(n_img);

    for (int i = 1; i < n_img; i++)
    {
        string path = file_path + to_string(i) + ".png";
        Texture texture;
        if (!texture.loadFromFile(path))
        {
            cerr << name + " is not loading" << endl;
            exit(EXIT_FAILURE);
        }
        // texture.setSmooth(true);
        flight_animation_obj_texture[i - 1] = texture;
    }
    return flight_animation_obj_texture;
}

void create_text(Text &txt, Color font_color, int WIDTH, int FPS_Y, int t_width)
{
    txt.setFillColor(font_color);
    txt.setPosition(WIDTH - t_width - FPS_Y, FPS_Y);
}

// @TODO 2: why does this does not draw the flight obj
// void create_sprite(Sprite& sprite, int scaling_factor, int c_x, int c_y)
// {
//     // sprite.setTexture(texture);
//     // Set the scaling factors
//     sprite.setScale(scaling_factor, scaling_factor);
//     // get the width and height of the flight obj
//     FloatRect bounds_flight_obj = sprite.getLocalBounds();
//     // set the position of the flight obj
//     cout << c_x - bounds_flight_obj.width * 0.5f * scaling_factor << endl;
//     sprite.setPosition(c_x - bounds_flight_obj.width * 0.5f * scaling_factor, c_y - bounds_flight_obj.height * 0.5f * scaling_factor);
// }


double cal_dist_btn_2_points(double x_flight, double x_target, double y_flight, double y_target)
{
    return sqrt(pow(x_flight - x_target, 2) + pow(y_flight - y_target, 2));
}