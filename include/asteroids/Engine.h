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
    Ship GetShip();
    std::vector<Asteroid> GetAsteroids();

    void UpdateShip();
    void UpdateShipMovement(int val);
    void UpdateShipRotation(double rad);

  private:
    int score;

    Ship player_ship_;
    std::vector<Asteroid> asteroids_;
  };
}

#endif //FINALPROJECT_ENGINE_H
