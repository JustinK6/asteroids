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
  // Game engine that keeps track of game entities in a game
  class Engine {
  public:
    // Creates a new Engine
    Engine();

    // Resets the engine
    void Reset();

    // Gets the score of the game
    int GetScore();

    // Gets the ship in the game
    Ship& GetShip();

    // Gets the asteroids in the game
    std::vector<Asteroid> GetAsteroids();

    // Gets the bullets in the game
    std::vector<Bullet> GetBullets();

    // Initializes entity dimensions for use in collision detection
    void InitializeEntityDimensions(double ship_w, double ship_h, double bullet_w,
      double bullet_h, double asteroid_w, double asteroid_h);

    // Updates the ship state in the game
    void UpdateShip();

    // Updates the ship position in the game
    void UpdateShipPosition(double x_pos, double y_pos);

    // Fires a bullet
    void FireBullet();

    // Loads a bullet so engine can fire another bullet
    void LoadBullet();

    // Updates bullet states
    void UpdateBullets(double max_x, double max_y);

    // Updates asteroid states
    void UpdateAsteroids(double max_x, double max_y);

    // Splits asteroid into smaller asteroids
    void SplitAsteroid(Asteroid asteroid);

    // Updates the shielded state
    void UpdateShields();

    // Checks to see if ship is shielded
    bool isShielded();

    // Checks for entity collisions and processes them
    void CheckCollisions();
  private:
    // The score of the game
    int score;

    // The player ship
    Ship player_ship_;

    // The bullets in the game
    std::vector<Bullet> bullets_;

    // The time stamp of the last asteroid spawn
    std::chrono::time_point<std::chrono::system_clock> asteroid_last_spawn_;

    // The asteroids in the game
    std::vector<Asteroid> asteroids_;

    // The time stamp the shield was last activated
    std::chrono::time_point<std::chrono::system_clock> shield_activated_;

    // Tracks if shield is on
    bool shield_on_;

    // Tracks if bullet has been fired/loaded
    bool bullet_fired_;

    // Checks for entity collision
    bool Intersects(double tl_x1, double tl_y1, double br_x1, double br_y1,
                    double tl_x2, double tl_y2, double br_x2, double br_y2);

    // Checks for bullet - asteroid collisions
    void CheckBulletCollisions();

    // Checks for ship - asteroid collisions
    void CheckShipCollisions();
  };
}

#endif //FINALPROJECT_ENGINE_H
