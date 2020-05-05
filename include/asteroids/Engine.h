//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include <vector>
#include <chrono>
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

    void InitializeEntityDimensions(double ship_w, double ship_h, double bullet_w,
      double bullet_h, double asteroid_w, double asteroid_h);

    void UpdateShip();
    void UpdateShipPosition(double x_pos, double y_pos);

    void FireBullet();
    void UpdateBullets(double max_x, double max_y);

    void UpdateAsteroids(double max_x, double max_y);
    void SplitAsteroid(Asteroid asteroid);

    void UpdateShields();
    bool isShielded();

    void CheckCollisions();
  private:
    int score;

    Ship player_ship_;
    std::vector<Bullet> bullets_;

    std::chrono::time_point<std::chrono::system_clock> asteroid_last_spawn_;
    std::vector<Asteroid> asteroids_;

    std::chrono::time_point<std::chrono::system_clock> shield_activated_;
    bool shield_on_;

    bool Intersects(double tl_x1, double tl_y1, double br_x1, double br_y1,
                    double tl_x2, double tl_y2, double br_x2, double br_y2);
    void CheckBulletCollisions();
    void CheckShipCollisions();
  };
}

#endif //FINALPROJECT_ENGINE_H
