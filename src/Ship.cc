//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#include "asteroids/Ship.h"

asteroids::Ship::Ship(double x_start, double y_start) {
  x_pos_ = x_start;
  y_pos_ = y_start;

  movement_change_ = 0;
  angular_change_ = 0;
}

std::pair<double, double> asteroids::Ship::GetPosition() {
  return std::make_pair(x_pos_, y_pos_);
}

double asteroids::Ship::GetRotation() {
  return angle_;
}

std::vector<asteroids::Bullet> asteroids::Ship::GetBullets() {
  return std::vector<Bullet>();
}

void asteroids::Ship::SetPosition(double x_val, double y_val) {
  x_pos_ = x_val;
  y_pos_ = y_val;
}

void asteroids::Ship::SetMovement(double val) {
  movement_change_ = val;
}

void asteroids::Ship::SetRotation(double rad) {
  angular_change_ = rad;
}

void asteroids::Ship::UpdateShip() {
  angle_ += angular_change_;
  x_pos_ += movement_change_ * cos(angle_);
  y_pos_ += movement_change_ * sin(angle_);
}