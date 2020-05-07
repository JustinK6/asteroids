//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#ifndef FINALPROJECT_SHIP_H
#define FINALPROJECT_SHIP_H

#include <utility>
#include <vector>
#include "Bullet.h"

namespace asteroids {
  // Represents a ship in the game
  class Ship {
  public:
    // Creates a ship at the specified location
    Ship(double x_start, double y_start);

    // Gets the position of the ship
    std::pair<double, double> GetPosition();

    // Gets the health of the ship
    int GetHealth();

    // Gets the rotation of the ship
    double GetRotation();

    // Sets the position of the ship
    void SetPosition(double x_val, double y_val);

    // Sets the acceleration of the ship
    void Accelerate(double val);

    // Sets the rotation of the ship
    void SetRotation(double rotating);

    // Updates the health of the ship
    void UpdateHealth();

    // Sets the health of the ship
    void SetHealth(int health);

    // Updates the state of the ship
    void UpdateShip();

  private:
    // The health of the ship
    int health_;

    // The acceleration of the ship
    double acceleration_;

    // The x velocity of the ship
    double vel_x_;

    // The y velocity of the ship
    double vel_y_;

    // The angular velocity of the ship
    double angular_change_;

    // The x position of the ship
    double x_pos_;

    // The y position of the ship
    double y_pos_;

    // The angle of the ship with respect to 0 radians
    double angle_;
  };
}

#endif //FINALPROJECT_SHIP_H
