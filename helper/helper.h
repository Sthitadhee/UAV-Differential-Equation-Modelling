#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <random>

using namespace sf;
using namespace std;


#ifndef HELPER_H 

int random_position_gen(int position_dim, int percent_margin);
Font create_font(const string& font_path);
vector<Texture> load_texture(string name, int n_img, string file_path);
void create_text(Text &txt, Color font_color, int WIDTH, int FPS_Y, int t_width);

// @TODO 2
// void create_sprite(Sprite& sprite, int scaling_factor, int c_x, int c_y);

#endif