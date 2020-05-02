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
    void UpdatePosition(double x_val, double y_val);
    std::vector<Bullet> GetBullets();

  private:
    int health_;
    double x_pos_;
    double y_pos_;

    std::vector<Bullet> bullets;
  };
}

#endif //FINALPROJECT_SHIP_H
