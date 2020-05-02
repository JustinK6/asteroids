//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#include "asteroids/Ship.h"

asteroids::Ship::Ship(double x_start, double y_start) {
  x_pos_ = x_start;
  y_pos_ = y_start;
}

std::pair<double, double> asteroids::Ship::GetPosition() {
  return std::make_pair(x_pos_, y_pos_);
}

void asteroids::Ship::UpdatePosition(double x_val, double y_val) {
  x_pos_ += x_val;
  y_pos_ += y_val;
}

std::vector<asteroids::Bullet> asteroids::Ship::GetBullets() {
  return std::vector<Bullet>();
}
