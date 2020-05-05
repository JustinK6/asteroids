//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#include <cmath>
#include "asteroids/Asteroid.h"

const double kAsteroidSpeed = 2.5;

asteroids::Asteroid::Asteroid(double x_val, double y_val, double dir, double diam) {
  x_pos_ = x_val;
  y_pos_ = y_val;
  dir_ = dir;
  diameter_ = diam;
}

std::pair<double, double> asteroids::Asteroid::GetPosition() {
  return std::make_pair(x_pos_, y_pos_);
}

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

double asteroids::Asteroid::GetDiameter() {
  return diameter_;
}
