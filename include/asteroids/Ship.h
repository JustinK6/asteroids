//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#ifndef FINALPROJECT_SHIP_H
#define FINALPROJECT_SHIP_H

#include <utility>
#include <vector>
#include "Bullet.h"

namespace asteroids {
  class Ship {
  public:
    Ship(double x_start, double y_start);

    std::pair<double, double> GetPosition();
    int GetHealth();
    double GetRotation();

    void SetPosition(double x_val, double y_val);
    void Accelerate(double val);
    void SetRotation(double rotating);
    void UpdateHealth();
    void SetHealth(int health);

    void UpdateShip();

  private:
    int health_;

    double acceleration_;
    double vel_x_;
    double vel_y_;

    double angular_change_;

    double x_pos_;
    double y_pos_;
    double angle_;
  };
}

#endif //FINALPROJECT_SHIP_H
