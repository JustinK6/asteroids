//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#ifndef FINALPROJECT_ASTEROID_H
#define FINALPROJECT_ASTEROID_H

#include <utility>

namespace asteroids {
  class Asteroid {
  public:
    Asteroid(double x_val, double y_val, double dir, double diam);

    std::pair<double, double> GetPosition();
    void UpdatePosition(double max_x, double max_y);

    double GetDiameter();

  private:
    double x_pos_;
    double y_pos_;
    double dir_;

    double diameter_;
  };

}

#endif //FINALPROJECT_ASTEROID_H
