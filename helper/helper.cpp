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

Font create_font(const string& font_path) 
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