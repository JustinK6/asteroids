//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#ifndef FINALPROJECT_ASTEROID_H
#define FINALPROJECT_ASTEROID_H

#include <utility>

namespace asteroids {
  // Represents an asteroid in the game
  class Asteroid {
  public:
    // Creates an asteroid at the given x,y position with direction dir, scale scale.
    Asteroid(double x_val, double y_val, double dir, double scale);

    // Gets the position of the asteroid
    std::pair<double, double> GetPosition();

    // Updates the position of the asteroid
    void UpdatePosition(double max_x, double max_y);

    // Gets the scale of the asteroid
    double GetScale();

  private:
    // The x position of the asteroid
    double x_pos_;

    // The y position of the asteroid
    double y_pos_;

    // The direction of the asteroid
    double dir_;

    // The scale of the asteroid
    double scale_;
  };

}

#endif //FINALPROJECT_ASTEROID_H
