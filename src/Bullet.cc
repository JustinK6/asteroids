//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#include <cmath>
#include "asteroids/Bullet.h"

int kBulletSpeed = 10;

asteroids::Bullet::Bullet(double x_pos, double y_pos, double dir) {
  x_pos_ = x_pos;
  y_pos_ = y_pos;
  dir_ = dir;

  dist_travelled_ = 0;
}

std::pair<double, double> asteroids::Bullet::GetPosition() {
  return std::make_pair(x_pos_, y_pos_);
}

double asteroids::Bullet::GetDistTravelled() {
  return dist_travelled_;
}

void asteroids::Bullet::UpdatePosition() {
  x_pos_ += kBulletSpeed * cos(dir_);
  y_pos_ += kBulletSpeed * sin(dir_);

  dist_travelled_ += kBulletSpeed;
}