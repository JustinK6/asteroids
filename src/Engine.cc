//
// Created by ORaNgCHiKeN on 4/29/2020.
//

#include <cinder/CinderMath.h>
#include "asteroids/Engine.h"

// Initial starting x position of ship.
const int kInitialStartingX = 400;

// Initial starting y position of ship.
const int kInitialStartingY = 400;

// Maximum number of bullets allowed to be fired at a time.
const int kMaxBullets = 3;

// Maximum health of a ship.
const int kMaxHealth = 4;

// Maximum distance a bullet can travel.
const int kMaxBulletRange = 500;

// Time between each asteroid spawn.
const std::chrono::seconds kAsteroidTimer = std::chrono::seconds(2);

// Shield time.
const std::chrono::seconds kShieldTimer = std::chrono::seconds(3);

// Max number of asteroids.
const int kMaxAsteroids = 10;

// Scale of large asteroid.
const double kLargeAsteroidScale = 1;

// Scale of small asteroid.
const double kSmallAsteroidScale = 0.5;

// Width of a bullet.
double bullet_width;

// Height of a bullet.
double bullet_height;

// Width of an asteroid.
double asteroid_width;

// Height of an asteroid.
double asteroid_height;

// Width of a ship.
double ship_width;

// Height of a ship.
double ship_height;

// Potential asteroid spawn locations.
std::vector<std::pair<double, double>> asteroid_spawns = {
  std::make_pair(0, 200),
  std::make_pair(800, 200),
  std::make_pair(0, 400),
  std::make_pair(800, 400)
};

// Index to cycle between asteroid spawn locations.
int asteroid_index;

// Count of asteroids on screen (+1 for each large, +0.5 for each small).
double asteroid_count;

// Count of bullets on screen.
double bullet_count;

// Creates and sets up a new engine.
asteroids::Engine::Engine()
  : player_ship_(kInitialStartingX, kInitialStartingY) {
  asteroid_last_spawn_ = std::chrono::system_clock::now();
  asteroid_index = 0;
  asteroid_count = 0;

  bullet_count = 0;
  bullet_fired_ = false;

  score = 0;

  shield_on_ = false;
  shield_activated_ = std::chrono::system_clock::now();
}

// Resets the engine.
void asteroids::Engine::Reset() {
  player_ship_.SetPosition(kInitialStartingX, kInitialStartingY);
  player_ship_.SetHealth(kMaxHealth);

  asteroid_last_spawn_ = std::chrono::system_clock::now();
  asteroid_index = 0;
  asteroid_count = 0;

  bullet_count = 0;
  bullet_fired_ = false;

  score = 0;

  shield_on_ = false;
  shield_activated_ = std::chrono::system_clock::now();

  asteroids_.clear();
  bullets_.clear();
}

// Gets the score of the player in the game.
// @return The score of the player
int asteroids::Engine::GetScore() {
  return score;
}

// Gets the ship in the game.
// @return The ship in the game
asteroids::Ship& asteroids::Engine::GetShip() {
  return player_ship_;
}

// Gets the bullets in the game.
// @return The bullets in the game
std::vector<asteroids::Bullet> asteroids::Engine::GetBullets() {
  return bullets_;
}

// Gets the asteroids in the game.
// @return The asteroids in the game
std::vector<asteroids::Asteroid> asteroids::Engine::GetAsteroids() {
  return asteroids_;
}

// Initializes the entity dimensions for collision detection uses.
// @param ship_w The width of the ship
// @param ship_h The height of the ship
// @param bullet_w The width of the bullet
// @param bullet_h The height of the bullet
// @param asteroid_w The width of an asteroid
// @param asteroid_h The height of an asteroid
void asteroids::Engine::InitializeEntityDimensions(double ship_w, double ship_h, double bullet_w,
  double bullet_h, double asteroid_w, double asteroid_h) {
  ship_width = ship_w;
  ship_height = ship_h;
  bullet_width = bullet_w;
  bullet_height = bullet_h;
  asteroid_width = asteroid_w;
  asteroid_height = asteroid_h;
}

// Updates te position of the ship.
// @param x_val The x position to move the ship to
// @param y_val The y position to move the ship to
void asteroids::Engine::UpdateShipPosition(double x_val, double y_val) {
  player_ship_.SetPosition(x_val, y_val);
}

// Updates the state of the ship.
void asteroids::Engine::UpdateShip() {
  player_ship_.UpdateShip();
}

// Attempts to fire a bullet.
void asteroids::Engine::FireBullet() {
  // Checks to see if number bullets less than max bullets and bullet loaded
  if (bullet_count < kMaxBullets && !bullet_fired_) {
    double x_pos = player_ship_.GetPosition().first;
    double y_pos = player_ship_.GetPosition().second;
    double dir = player_ship_.GetRotation();

    bullets_.emplace_back(x_pos, y_pos, dir);
    bullet_count++;
    bullet_fired_ = true;
  }
}

// Loads a bullet to enable firing.
void asteroids::Engine::LoadBullet() {
  bullet_fired_ = false;
}

// Updates the state of the bullets.
// @param max_x The maximum x coordinate a bullet can travel to
// @param max_y The maximum y coordinate a bullet can travel to
void asteroids::Engine::UpdateBullets(double max_x, double max_y) {
  for (int i = 0; i < bullets_.size(); i++) {
    bullets_[i].UpdatePosition();

    // Check if bullet has gone over max range
    if (bullets_[i].GetDistTravelled() > kMaxBulletRange) {
      bullets_.erase(bullets_.begin() + i);
      bullet_count--;
      return;
    }

    // Check if bullet has gone out of bounds
    double x_pos = bullets_[i].GetPosition().first;
    double y_pos = bullets_[i].GetPosition().second;

    if (x_pos > max_x || x_pos < 0 || y_pos > max_y || y_pos < 0) {
      bullets_.erase(bullets_.begin() + i);
      bullet_count--;
      return;
    }
  }
}

// Updates the state of the asteroids.
// @param max_x The maximum x coordinate an asteroid can travel to
// @param max_y The maximum y coordinate an asteroid can travel to
void asteroids::Engine::UpdateAsteroids(double max_x, double max_y) {
  // Check if enough time has passed to add another asteroid
  if (std::chrono::system_clock::now() - asteroid_last_spawn_ > kAsteroidTimer
    && asteroid_count < kMaxAsteroids) {
    double x_val = asteroid_spawns[asteroid_index].first;
    double y_val = asteroid_spawns[asteroid_index].second;

    // Updates asteroid index to spawn asteroid at different location
    asteroid_index++;
    if (asteroid_index > 3) {
      asteroid_index = 0;
    }

    // Creates a new asteroid with a random direction
    asteroids_.emplace_back(Asteroid(x_val, y_val,
      ((double) rand() / (RAND_MAX) * 2 * M_PI), kLargeAsteroidScale));
    asteroid_count += 1;

    // Updates asteroid timer
    asteroid_last_spawn_ = std::chrono::system_clock::now();
  }

  // Updates positions of all asteroids
  for (int i = 0; i < asteroids_.size(); i++) {
    asteroids_[i].UpdatePosition(max_x, max_y);
  }
}

// Splits an asteroid.
// @param asteroid The asteroid to split
void asteroids::Engine::SplitAsteroid(Asteroid asteroid) {
  // Gets the position of the asteroid to split
  double asteroid_x = asteroid.GetPosition().first;
  double asteroid_y = asteroid.GetPosition().second;

  // Creates two new smaller asteroids (half size) at the position with random directions
  asteroids_.emplace_back(Asteroid(asteroid_x, asteroid_y,
    ((double) rand() / (RAND_MAX) * 2 * M_PI), kSmallAsteroidScale));
  asteroids_.emplace_back(Asteroid(asteroid_x, asteroid_y,
    ((double) rand() / (RAND_MAX) * 2 * M_PI), kSmallAsteroidScale));
}

// Updates the state of the shield.
void asteroids::Engine::UpdateShields() {
  if (shield_on_ && std::chrono::system_clock::now() - shield_activated_ > kShieldTimer) {
    shield_on_ = false;
  }
}

// Checks if the ship is shielded.
// @return True if the ship is shielded, false if not
bool asteroids::Engine::isShielded() {
  return shield_on_;
}

// Checks for entity collisions.
void asteroids::Engine::CheckCollisions() {
  CheckBulletCollisions();
  CheckShipCollisions();
}

// Checks for bullet-asteroid collisions.
void asteroids::Engine::CheckBulletCollisions() {
  // Check bullets to asteroids
  for (int i = 0; i < bullets_.size(); i++) {
    double bullet_x = bullets_[i].GetPosition().first;
    double bullet_y = bullets_[i].GetPosition().second;

    // Top left and bottom right corners of bullet
    double bullet_tl_x = bullet_x - bullet_width / 2.0;
    double bullet_tl_y = bullet_y - bullet_height / 2.0;
    double bullet_br_x = bullet_x + bullet_width / 2.0;
    double bullet_br_y = bullet_y + bullet_height / 2.0;

    for (int j = 0; j < asteroids_.size(); j++) {
      double asteroid_x = asteroids_[j].GetPosition().first;
      double asteroid_y = asteroids_[j].GetPosition().second;

      // Top left and bottom right corners of asteroid
      double asteroid_tl_x = asteroid_x - asteroid_width / (2.0 / asteroids_[j].GetScale());
      double asteroid_tl_y = asteroid_y - asteroid_height / (2.0 / asteroids_[j].GetScale());
      double asteroid_br_x = asteroid_x + asteroid_width / (2.0 / asteroids_[j].GetScale());
      double asteroid_br_y = asteroid_y + asteroid_height / (2.0 / asteroids_[j].GetScale());

      // Checks for intersection
      if (Intersects(bullet_tl_x, bullet_tl_y, bullet_br_x, bullet_br_y,
          asteroid_tl_x, asteroid_tl_y, asteroid_br_x, asteroid_br_y)) {
        bullets_.erase(bullets_.begin() + i);
        bullet_count--;

        // Split large asteroids into 2 smaller
        if (asteroids_[j].GetScale() > 0.6) {
          SplitAsteroid(asteroids_[j]);
        } else {
          asteroid_count -= 0.5;
        }
        asteroids_.erase(asteroids_.begin() + j);

        score++;
        break;
      }
    }
  }
}

// Checks for ship-asteroid collisions.
void asteroids::Engine::CheckShipCollisions() {
  double ship_x = player_ship_.GetPosition().first;
  double ship_y = player_ship_.GetPosition().second;

  // Top left and bottom right corners of ship
  double ship_tl_x = ship_x - ship_width / 2.0;
  double ship_tl_y = ship_y - ship_height / 2.0;
  double ship_br_x = ship_x + ship_width / 2.0;
  double ship_br_y = ship_y + ship_height / 2.0;

  for (int j = 0; j < asteroids_.size(); j++) {
    double asteroid_x = asteroids_[j].GetPosition().first;
    double asteroid_y = asteroids_[j].GetPosition().second;

    // Top left and bottom right corners of asteroid
    double asteroid_tl_x = asteroid_x - asteroid_width / (2.0 / asteroids_[j].GetScale());
    double asteroid_tl_y = asteroid_y - asteroid_height / (2.0 / asteroids_[j].GetScale());
    double asteroid_br_x = asteroid_x + asteroid_width / (2.0 / asteroids_[j].GetScale());
    double asteroid_br_y = asteroid_y + asteroid_height / (2.0 / asteroids_[j].GetScale());

    // Checks for intersection
    if (Intersects(ship_tl_x, ship_tl_y, ship_br_x, ship_br_y,
                   asteroid_tl_x, asteroid_tl_y, asteroid_br_x, asteroid_br_y)) {
      if (!shield_on_) {
        // Decreases player health and activates temporary shield
        player_ship_.UpdateHealth();
        shield_on_ = true;
        shield_activated_ = std::chrono::system_clock::now();
      }

      // Splits asteroid if large, remove if small
      if (asteroids_[j].GetScale() > 0.6) {
        SplitAsteroid(asteroids_[j]);
      } else {
        asteroid_count -= 0.5;
      }
      asteroids_.erase(asteroids_.begin() + j);
    }
  }
}

// Checks to see if two entities intersect.
// @param tl_x1 The x coordinate of top left corner of first entity
// @param tl_y1 THe y coordinate of top left corner of first entity
// @param br_x1 The x coordinate of bottom right corner of first entity
// @param br_y1 The y coordinate of bottom right corner of first entity
// @param tl_x2 The x coordinate of top left corner of second entity
// @param tl_y2 The y coordinate of top left corner of second entity
// @param br_x2 The x coordinate of bottom right corner of second entity
// @param br_y2 The y coordinate of bottom right corner of second entity
// @return True if the entities intersect, false if not
bool asteroids::Engine::Intersects(double tl_x1, double tl_y1, double br_x1, double br_y1,
  double tl_x2, double tl_y2, double br_x2, double br_y2) {
  // If one rectangle is on left side of other
  if (tl_x1 >= br_x2 || tl_x2 >= br_x1) {
    return false;
  }

  // If one rectangle is above other
  if (tl_y1 >= br_y2 || tl_y2 >= br_y1) {
    return false;
  }

  return true;
}
