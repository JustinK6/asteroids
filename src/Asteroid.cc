//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#include <cmath>
#include "asteroids/Asteroid.h"

// The speed of an asteroid
const double kAsteroidSpeed = 2.5;

// Creates a new asteroid with the specified properties.
// @param x_val The x position of the asteroid
// @param y_val The y position of the asteroid
// @param dir The direction the asteroid is to travel in
// @param scale The scale of the asteroid
asteroids::Asteroid::Asteroid(double x_val, double y_val, double dir, double scale) {
  x_pos_ = x_val;
  y_pos_ = y_val;
  dir_ = dir;
  scale_ = scale;
}

// Gets the position of the asteroid.
// @return A pair representing x,y coordinates of asteroid in the game
std::pair<double, double> asteroids::Asteroid::GetPosition() {
  return std::make_pair(x_pos_, y_pos_);
}

// Updates the position of an asteroid.
// @param max_x The x boundary the asteroid is able to travel up to
// @param max_y The y boundary the asteroid is able to travel up to
void asteroids::Asteroid::UpdatePosition(double max_x, double max_y) {
  // Update asteroid position
  x_pos_ += kAsteroidSpeed * cos(dir_);
  y_pos_ += kAsteroidSpeed * sin(dir_);

  // Check if asteroid is out of bounds
  // Check x position
  if (x_pos_ > max_x) {
    x_pos_ = 0;
  } else if (x_pos_ < 0) {
    x_pos_ = max_x;
  }

  // Check y position
  if (y_pos_ > max_y) {
    y_pos_ = 0;
  } else if (y_pos_ < 0) {
    y_pos_ = max_y;
  }
}

// Gets the scale of the asteroid.
// @return the scale of the asteroid
double asteroids::Asteroid::GetScale() {
  return scale_;
}
