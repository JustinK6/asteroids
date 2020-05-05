//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#ifndef FINALPROJECT_BULLET_H
#define FINALPROJECT_BULLET_H


#include <utility>
namespace asteroids {
  class Bullet {
  public:
    Bullet(double x_pos, double y_pos, double dir);

    std::pair<double, double> GetPosition();
    double GetDistTravelled();

    void UpdatePosition();

  private:
    double x_pos_;
    double y_pos_;
    double dir_;
    double dist_travelled_;
  };
}



#endif //FINALPROJECT_BULLET_H
