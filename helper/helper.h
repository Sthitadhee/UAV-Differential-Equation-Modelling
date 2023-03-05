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

#endif