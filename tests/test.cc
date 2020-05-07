// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <asteroids/Ship.h>
#include <asteroids/Asteroid.h>
#include <asteroids/Engine.h>

TEST_CASE("Test Ship Movement", "[ship-movement]") {
  asteroids::Ship ship(400, 400);
  ship.Accelerate(5);
  ship.UpdateShip();

  // Make sure ship position was updated
  REQUIRE(ship.GetPosition().first != 400);
}

TEST_CASE("Test Bullet Movement", "[bullet-movement]") {
  asteroids::Bullet bullet(400, 400, 0);
  bullet.UpdatePosition();

  // Make sure bullet position was updated
  REQUIRE(bullet.GetPosition().first != 400);
}

TEST_CASE("Test Asteroid Movement", "[asteroid-movement]") {
  asteroids::Asteroid asteroid(400, 400, 0, 1);
  asteroid.UpdatePosition(800, 800);

  // Make sure asteroid movement was updated
  REQUIRE(asteroid.GetPosition().first != 400);
}

TEST_CASE("Test Ship Bounds", "[ship-bounds]") {
  asteroids::Ship ship(799, 400);
  ship.Accelerate(5);
  ship.UpdateShip();

  // Make sure ship doesn't go over bounds
  REQUIRE(ship.GetPosition().first < 400);
}

TEST_CASE("Test Asteroid Bounds", "[asteroid-bounds]") {
  asteroids::Asteroid asteroid(799, 400, 0, 1);
  asteroid.UpdatePosition(800, 800);

  // Make sure asteroid doesn't go over bounds
  REQUIRE(asteroid.GetPosition().first < 400);
}

TEST_CASE("Test Asteroid-Bullet Collision", "[asteroid-bullet-collision") {
  asteroids::Engine game_engine;
  game_engine.GetAsteroids().emplace_back(asteroids::Asteroid(400, 400, 0, 1));
  game_engine.FireBullet();

  // Make sure bullet gets deleted due to collision
  REQUIRE(game_engine.GetBullets().size() == 0);
}

TEST_CASE("Test Asteroid-Ship Collision", "[asteroid-ship-collision") {
  asteroids::Engine game_engine;
  game_engine.GetAsteroids().emplace_back(asteroids::Asteroid(400, 400, 0, 1));

  // Make sure ship health decreases due to collision
  REQUIRE(game_engine.GetShip().GetHealth() == 3);
}
