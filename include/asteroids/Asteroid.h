//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#ifndef FINALPROJECT_ASTEROID_H
#define FINALPROJECT_ASTEROID_H

#include <utility>

namespace asteroids {
  class Asteroid {
  public:
    std::pair<double, double> GetPosition();
    void UpdatePosition(double x_val, double y_val);

  private:
    double x_pos_;
    double y_pos_;
    double radius;
  };

}

#endif //FINALPROJECT_ASTEROID_H
