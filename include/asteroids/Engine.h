//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include <vector>
#include "Ship.h"
#include "Asteroid.h"

namespace asteroids {
  class Engine {
  public:
    Engine();

    int GetScore();
    Ship& GetShip();
    std::vector<Asteroid> GetAsteroids();
    std::vector<Bullet> GetBullets();

    void UpdateShip();
    void UpdateShipPosition(double x_pos, double y_pos);

    void FireBullet();
    void UpdateBullets(double max_x, double max_y);
  private:
    int score;

    Ship player_ship_;
    std::vector<Bullet> bullets;
    std::vector<Asteroid> asteroids_;
  };
}

#endif //FINALPROJECT_ENGINE_H
