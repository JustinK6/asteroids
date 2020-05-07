//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#include "asteroids/Ship.h"

// Max health of a ship.
const int kMaxHealth = 4;

// Creates a new ship with the specified properties.
// @param x_start The x coordinate to start at
// @param y_start The y coordinate to start at
asteroids::Ship::Ship(double x_start, double y_start) {
  x_pos_ = x_start;
  y_pos_ = y_start;

  acceleration_ = 0;
  angular_change_ = 0;
  health_ = kMaxHealth;

  vel_x_ = 0;
  vel_y_ = 0;
}

// Gets the position of the ship.
// @return The x,y coordinates of the ship as a pair
std::pair<double, double> asteroids::Ship::GetPosition() {
  return std::make_pair(x_pos_, y_pos_);
}

// Gets the rotation of the ship.
// @return The rotation of the ship
double asteroids::Ship::GetRotation() {
  return angle_;
}

// Gets the health of the ship.
// @return The health of the ship
int asteroids::Ship::GetHealth() {
  return health_;
}

// Sets the position of the ship.
// @param x_val The x position to move the ship to
// @param y_val The y position to move the ship to
void asteroids::Ship::SetPosition(double x_val, double y_val) {
  x_pos_ = x_val;
  y_pos_ = y_val;
}

// Sets the acceleration of the ship.
// @param val The value to set te acceleration to
void asteroids::Ship::Accelerate(double val) {
  acceleration_ = val;
}

// Sets the angular velocity of the ship.
// @param rad The value to set the angular velocity to
void asteroids::Ship::SetRotation(double rad) {
  angular_change_ = rad;
}

// Updates the state of the ship.
void asteroids::Ship::UpdateShip() {
  // Update angle of speed based on angular velocity
  angle_ += angular_change_;

  // Changes velocity of ship based on acceleration
  if (acceleration_ > 0) {
    vel_x_ += acceleration_ * cos(angle_);
    vel_y_ += acceleration_ * sin(angle_);
  } else {
    vel_x_ += -vel_x_ / 40.0;
    vel_y_ += -vel_y_ / 40.0;
  }

  // Update position of ship based on velocity
  x_pos_ += vel_x_;
  y_pos_ += vel_y_;
}

// Updates the health of the ship.
void asteroids::Ship::UpdateHealth() {
  health_--;
}

// Sets the health of the ship.
// @param health The value to set the health to
void asteroids::Ship::SetHealth(int health) {
  health_ = health;
}
