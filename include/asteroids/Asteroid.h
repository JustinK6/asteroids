//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#ifndef FINALPROJECT_ASTEROID_H
#define FINALPROJECT_ASTEROID_H

#include <utility>

namespace asteroids {
  class Asteroid {
  public:
    Asteroid(double x_val, double y_val, double dir, double scale);

    std::pair<double, double> GetPosition();
    void UpdatePosition(double max_x, double max_y);

    double GetScale();

  private:
    double x_pos_;
    double y_pos_;
    double dir_;

    double scale_;
  };

}

#endif //FINALPROJECT_ASTEROID_H
