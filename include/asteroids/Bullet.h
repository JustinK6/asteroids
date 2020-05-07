//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#ifndef FINALPROJECT_BULLET_H
#define FINALPROJECT_BULLET_H


#include <utility>
namespace asteroids {
  // Represents a bullet in the game
  class Bullet {
  public:
    // Creates a new bullet at the given x,y and direction
    Bullet(double x_pos, double y_pos, double dir);

    // Gets the position of the bullet
    std::pair<double, double> GetPosition();

    // Gets the total distance travelled by the bullet
    double GetDistTravelled();

    // Updates the position of the bullet
    void UpdatePosition();

  private:
    // The x position of the bullet
    double x_pos_;

    // The y position of the bullet
    double y_pos_;

    // The direction of the bullet
    double dir_;

    // The distance travelled by the bullet
    double dist_travelled_;
  };
}



#endif //FINALPROJECT_BULLET_H
