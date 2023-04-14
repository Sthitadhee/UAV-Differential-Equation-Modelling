#ifndef VARIABLE_H
#define VARIABLE_H

#include <SFML/Graphics.hpp>

using namespace sf;  // sf comes from SFML

const double WIDTH_SCALE = 1.2; // scales the width personal preference
const int EXTRA_HEIGHT_SCALE = 25;
const double FLIGHT_OBJ_SCALE = 0.4, TARGET_OBJ_SCALE = 0.3;
const int FPS = 60, FPS_Y = 20;

// Physics constants
const double GRAVITY = 0.08;
const int MASS_OF_OBJ = 1, ARM = 25;

// Constants needed for graphics
// milliseconds per frame -> animation_speed
const int n_FLIGHT_OBJ_IMG = 5, n_TARGET_OBJ_IMG = 8;
const float animation_speed = 50;
double x_cloud1 = 150.00, y_cloud1 = 200.00, speed_cloud1 = 0.5;

VideoMode mode = VideoMode::getDesktopMode();
const int WIDTH = mode.width / WIDTH_SCALE;
const int HEIGHT = mode.height / WIDTH_SCALE + mode.height / EXTRA_HEIGHT_SCALE;
const int WINDOW_CENTER_X = (int)(WIDTH / 2);
const int WINDOW_CENTER_Y = (int)(HEIGHT / 2);

int n_targets = 3;

#endif