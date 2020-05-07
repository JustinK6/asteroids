//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#include <cmath>
#include "asteroids/Bullet.h"

// The speed of a bullet
int kBulletSpeed = 7;

// Creates a new bullet with the given properties.
// @param x_pos The x position of the bullet
// @param y_pos The y position of the bullet
// @param dir The direction the bullet is to travel in
asteroids::Bullet::Bullet(double x_pos, double y_pos, double dir) {
  x_pos_ = x_pos;
  y_pos_ = y_pos;
  dir_ = dir;

  dist_travelled_ = 0;
}

// Gets the position of the bullet.
// @return The bullet's x,y coordinate as a pair
std::pair<double, double> asteroids::Bullet::GetPosition() {
  return std::make_pair(x_pos_, y_pos_);
}

// Gets the distance travelled by the bullet.
// @return The distance travelled by the bullet
double asteroids::Bullet::GetDistTravelled() {
  return dist_travelled_;
}

// Updates the position of the bullet.
void asteroids::Bullet::UpdatePosition() {
  x_pos_ += kBulletSpeed * cos(dir_);
  y_pos_ += kBulletSpeed * sin(dir_);

  dist_travelled_ += kBulletSpeed;
}