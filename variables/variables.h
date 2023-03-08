#pragma once

#include <SFML/Graphics.hpp>

const float WIDTH_SCALE = 1.2f; // scales the width personal preference
const int EXTRA_HEIGHT_SCALE = 25;
const float FLIGHT_OBJ_SCALE = 0.6f, TARGET_OBJ_SCALE = 0.3f;
const int FPS = 90, FPS_Y = 20;

// Physics constants
const float GRAVITY = 9.8f;
const int MASS_OF_OBJ = 1, ARM = 25;

// Constants needed for graphics
// milliseconds per frame -> animation_speed
const int n_FLIGHT_OBJ_IMG = 5, n_TARGET_OBJ_IMG = 8, animation_speed = 50;
double x_cloud1 = 150.00, y_cloud1 = 200.00, speed_cloud1 = 0.5;

VideoMode mode = VideoMode::getDesktopMode();
const int WIDTH = mode.width / WIDTH_SCALE;
const int HEIGHT = mode.height / WIDTH_SCALE + mode.height / EXTRA_HEIGHT_SCALE;
const int WINDOW_CENTER_X = (int)(WIDTH / 2);
const int WINDOW_CENTER_Y = (int)(HEIGHT / 2);