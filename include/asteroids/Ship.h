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
    double GetRotation();

    std::vector<Bullet> GetBullets();

    void SetMovement(double val);
    void SetRotation(double rotating);
    void UpdateShip();
  private:
    int health_;

    double movement_change_;
    double angular_change_;

    double x_pos_;
    double y_pos_;
    double angle_;

    std::vector<Bullet> bullets;
  };
}

#endif //FINALPROJECT_SHIP_H
