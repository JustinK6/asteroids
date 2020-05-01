//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#ifndef FINALPROJECT_BULLET_H
#define FINALPROJECT_BULLET_H


#include <utility>
namespace asteroids {
  class Bullet {
  public:
    std::pair<double, double> GetPosition();

    void UpdatePosition(double x_val, double y_val);

  private:
    double x_pos_;
    double y_pos_;
  };
}



#endif //FINALPROJECT_BULLET_H
