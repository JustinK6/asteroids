//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#include <cinder/CinderMath.h>
#include "asteroids/Engine.h"

const int kInitialStartingX = 400;
const int kInitialStartingY = 400;

const int kMaxBullets = 3;

// Maximum distance a bullet can travel
const int kMaxBulletRange = 500;

// Time between each asteroid spawn
const std::chrono::seconds kAsteroidTimer = std::chrono::seconds(5);

// Max number of asteroids
const int kMaxAsteroids = 10;

// Scale of large asteroid
const double kLargeAsteroidScale = 1;

// Scale of small asteroid
const double kSmallAsteroidScale = 0.5;

// Potential asteroid spawn locations
std::vector<std::pair<double, double>> asteroid_spawns = {
  std::make_pair(0, 200),
  std::make_pair(800, 200),
  std::make_pair(0, 400),
  std::make_pair(800, 400)
};

// Index to cycle between asteroid spawn locations
int asteroid_index;

// Count of asteroids on screen (+1 for each large, +0.5 for each small)
double asteroid_count;

asteroids::Engine::Engine()
  : player_ship_(kInitialStartingX, kInitialStartingY) {
  asteroid_last_spawn_ = std::chrono::system_clock::now();
  asteroid_index = 0;
  asteroid_count = 0;
}

int asteroids::Engine::GetScore() {
  return 0;
}

asteroids::Ship& asteroids::Engine::GetShip() {
  return player_ship_;
}

std::vector<asteroids::Bullet> asteroids::Engine::GetBullets() {
  return bullets;
}

std::vector<asteroids::Asteroid> asteroids::Engine::GetAsteroids() {
  return asteroids_;
}

void asteroids::Engine::UpdateShipPosition(double x_val, double y_val) {
  player_ship_.SetPosition(x_val, y_val);
}

void asteroids::Engine::UpdateShip() {
  player_ship_.UpdateShip();
}

void asteroids::Engine::FireBullet() {
  if (bullets.size() < kMaxBullets) {
    double x_pos = player_ship_.GetPosition().first;
    double y_pos = player_ship_.GetPosition().second;
    double dir = player_ship_.GetRotation();

    bullets.emplace_back(x_pos, y_pos, dir);
  }
}

void asteroids::Engine::UpdateBullets(double max_x, double max_y) {
  for (int i = 0; i < bullets.size(); i++) {
    bullets[i].UpdatePosition();

    // Check if bullet has gone over max range
    if (bullets[i].GetDistTravelled() > kMaxBulletRange) {
      bullets.erase(bullets.begin() + i);
      return;
    }

    // Check if bullet has gone out of bounds
    double x_pos = bullets[i].GetPosition().first;
    double y_pos = bullets[i].GetPosition().second;

    if (x_pos > max_x || x_pos < 0 || y_pos > max_y || y_pos < 0) {
      bullets.erase(bullets.begin() + i);
      return;
    }
  }
}

void asteroids::Engine::UpdateAsteroids(double max_x, double max_y) {
  // Check if enough time has passed to add another asteroid
  if (std::chrono::system_clock::now() - asteroid_last_spawn_ > kAsteroidTimer
    && asteroid_count < kMaxAsteroids) {
    double x_val = asteroid_spawns[asteroid_index].first;
    double y_val = asteroid_spawns[asteroid_index].second;

    asteroid_index++;
    if (asteroid_index > 3) {
      asteroid_index = 0;
    }

    asteroids_.emplace_back(Asteroid(x_val, y_val,
      ((double) rand() / (RAND_MAX) * 2 * M_PI), kLargeAsteroidScale));
    asteroid_count += 1;

    asteroid_last_spawn_ = std::chrono::system_clock::now();
  }

  for (int i = 0; i < asteroids_.size(); i++) {
    asteroids_[i].UpdatePosition(max_x, max_y);
  }
}
