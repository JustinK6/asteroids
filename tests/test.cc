// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <asteroids/Ship.h>
#include <asteroids/Asteroid.h>

TEST_CASE("Test Ship Movement", "[ship-movement]") {
  asteroids::Ship ship(400, 400);
  ship.Accelerate(5);
  ship.UpdateShip();

  // Make sure ship position was updated
  REQUIRE(ship.GetPosition().first != 400);
}

TEST_CASE("Test Asteroid Movement", "[asteroid-movement]") {
  asteroids::Asteroid asteroid(400, 400, 0, 1);
  asteroid.UpdatePosition(800, 800);

  // Make sure asteroid movement was updated
  REQUIRE(asteroid.GetPosition().first != 400);
}