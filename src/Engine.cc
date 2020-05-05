//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#include "asteroids/Engine.h"

int kInitialStartingX = 400;
int kInitialStartingY = 400;

int kMaxBullets = 3;
int kMaxBulletRange = 500;

asteroids::Engine::Engine()
  : player_ship_(kInitialStartingX, kInitialStartingY) {

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
  return std::vector<Asteroid>();
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
