/*
Author: Sthitadhee Panthadas
Helper functions declarations used in the main file
*/


#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <random>
#include <cmath>

using namespace sf;
using namespace std;


#ifndef HELPER_H 

int random_position_gen(int position_dim, int percent_margin);
Font create_font(const string& font_path);
vector<Texture> load_texture(string name, int n_img, string file_path);
void create_text(Text &txt, Color font_color, int WIDTH, int FPS_Y, int t_width);
double cal_dist_btn_2_points(double x_flight, double x_target, double y_flight, double y_target);
// void drawLineGraph(RenderWindow& window, vector<float>& x_values, const vector<float>& y_values); 

// @TODO 2
// void create_sprite(Sprite& sprite, int scaling_factor, int c_x, int c_y);

#endif