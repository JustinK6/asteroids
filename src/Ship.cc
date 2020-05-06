//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#include "asteroids/Ship.h"

const int kMaxHealth = 4;

asteroids::Ship::Ship(double x_start, double y_start) {
  x_pos_ = x_start;
  y_pos_ = y_start;

  acceleration_ = 0;
  angular_change_ = 0;
  health_ = kMaxHealth;

  vel_x_ = 0;
  vel_y_ = 0;
}

std::pair<double, double> asteroids::Ship::GetPosition() {
  return std::make_pair(x_pos_, y_pos_);
}

double asteroids::Ship::GetRotation() {
  return angle_;
}

int asteroids::Ship::GetHealth() {
  return health_;
}

void asteroids::Ship::SetPosition(double x_val, double y_val) {
  x_pos_ = x_val;
  y_pos_ = y_val;
}

void asteroids::Ship::Accelerate(double val) {
  acceleration_ = val;
}

void asteroids::Ship::SetRotation(double rad) {
  angular_change_ = rad;
}

void asteroids::Ship::UpdateShip() {
  angle_ += angular_change_;

  if (acceleration_ > 0) {
    vel_x_ += acceleration_ * cos(angle_);
    vel_y_ += acceleration_ * sin(angle_);
  } else {
    vel_x_ += -vel_x_ / 40.0;
    vel_y_ += -vel_y_ / 40.0;
  }

  x_pos_ += vel_x_;
  y_pos_ += vel_y_;
}

void asteroids::Ship::UpdateHealth() {
  health_--;
}

void asteroids::Ship::SetHealth(int health) {
  health_ = health;
}
