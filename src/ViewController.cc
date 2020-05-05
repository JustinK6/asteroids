//
// Created by ORaNgCHiKeN on 4/21/2020.
//

#include "asteroids/ViewController.h"

#include "cinder/app/App.h"

using namespace po::scene;

namespace asteroids
{
  float ui_hue = 0.4f;
  float brightness = 0.65f;
  float saturation = 0.5f;

  double kShipSize = 75;
  double kBulletSize = 10;

  ci::Color boundsColor( 1.0f, 1.0f, 1.0f );

  ViewControllerRef ViewController::create() {
    return ViewControllerRef(new ViewController() );
  }

  void ViewController::viewDidLoad() {
    // Connect to key events
    ci::app::getWindow()->getSignalKeyDown().connect(std::bind( &ViewController::KeyDown,
      this, std::placeholders::_1));
    ci::app::getWindow()->getSignalKeyUp().connect(std::bind( &ViewController::KeyUp,
      this, std::placeholders::_1));

    SetUpViews();
    SetUpShip();

    // Load bullet image texture
    bullet_image_ = ci::gl::Texture::create(ci::loadImage(
      ci::app::loadAsset("bullet.png")));
    bullet_image_->setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);

    // Load asteroid image texture
    asteroid_image_ = ci::gl::Texture::create(ci::loadImage(
      ci::app::loadAsset("asteroid.png")));
    asteroid_image_->setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);

    // Add views to main view controller
    getView()->addSubview(game_view_);
    getView()->addSubview(ui_view_ );

    // Setup Scene (this class is the root node)
    getView()->setName("Scene (Scene Root View)")
      .setPosition(ci::vec2(0, 0))
      .setDrawBounds(false)
      .setBoundsColor(boundsColor);
  }

  void ViewController::update() {
    // Remove all subviews to update
    game_view_->removeAllSubviews();

    // Update the location of the ship
    UpdateShip();

    // Update locations of bullets
    game_engine_.UpdateBullets(ci::app::getWindowWidth(), 3 * ci::app::getWindowHeight() / 4);
    UpdateBulletViews();

    // Update locations of asteroids
    game_engine_.UpdateAsteroids(ci::app::getWindowWidth(), 3 * ci::app::getWindowHeight() / 4);
    UpdateAsteroidViews();
  }

  void ViewController::UpdateShip() {
    Ship ship = game_engine_.GetShip();

    // Checking for going off the edge of the screen
    double ship_x = ship.GetPosition().first;
    double ship_y = ship.GetPosition().second;

    // Check x position
    if (ship_x > ci::app::getWindowWidth()) {
      game_engine_.UpdateShipPosition(0, ship_y);
    } else if (ship_x < 0) {
      game_engine_.UpdateShipPosition(ci::app::getWindowWidth(), ship_y);
    }

    // Check y position
    if (ship_y > 3 * ci::app::getWindowHeight() / 4) {
      game_engine_.UpdateShipPosition(ship_x, 0);
    } else if (ship_y < 0) {
      game_engine_.UpdateShipPosition(ship_x, 3 * ci::app::getWindowHeight() / 4);
    }

    // Updates the location of the ship
    game_engine_.UpdateShip();
    ship = game_engine_.GetShip();

    // Sets the new retrieved position of the ship in the view
    ship_shape_->setPosition(ship.GetPosition().first, ship.GetPosition().second);
    ship_shape_->setRotation(ship.GetRotation());
    ship_shape_->setOffset(-kShipSize / 6.0, -kShipSize / 6.0);

    game_view_->addSubview(ship_shape_);
  }

  void ViewController::UpdateBulletViews() {
    bullets_.clear();

    for (int i = 0; i < game_engine_.GetBullets().size(); i++) {
      Bullet temp = game_engine_.GetBullets()[i];

      double bullet_x = temp.GetPosition().first;
      double bullet_y = temp.GetPosition().second;

      ShapeViewRef bullet = ShapeView::createRect(kBulletSize, kBulletSize);
      bullet->setPosition(bullet_x, bullet_y);
      bullet->setTexture(bullet_image_);

      bullets_.push_back(bullet);
    }

    for (int i = 0; i < bullets_.size(); i++) {
      game_view_->addSubview(bullets_[i]);
    }
  }

  void ViewController::UpdateAsteroidViews() {
    asteroids_.clear();

    for (int i = 0; i < game_engine_.GetAsteroids().size(); i++) {
      Asteroid temp = game_engine_.GetAsteroids()[i];

      double asteroid_x = temp.GetPosition().first;
      double asteroid_y = temp.GetPosition().second;

      ShapeViewRef asteroid = ShapeView::createRect(temp.GetDiameter(), temp.GetDiameter());
      asteroid->setPosition(asteroid_x, asteroid_y);
      asteroid->setTexture(asteroid_image_);

      asteroids_.push_back(asteroid);
    }

    for (int i = 0; i < asteroids_.size(); i++) {
      game_view_->addSubview(asteroids_[i]);
    }
  }

  void ViewController::KeyDown(ci::app::KeyEvent KeyEvent) {
    switch (KeyEvent.getChar()) {
      case 'W':
      case 'w':
        game_engine_.GetShip().SetMovement(5);
        break;

      case 'A':
      case 'a':
        game_engine_.GetShip().SetRotation(-0.1);
        break;

      case 'D':
      case 'd':
        game_engine_.GetShip().SetRotation(0.1);
        break;

      case 'F':
      case 'f':
        game_engine_.FireBullet();
        break;

      default:
        break;
    }
  }

  void ViewController::KeyUp(ci::app::KeyEvent KeyEvent) {
    switch (KeyEvent.getChar()) {
      case 'W':
      case 'w':
        game_engine_.GetShip().SetMovement(0);
        break;

      case 'A':
      case 'a':
        game_engine_.GetShip().SetRotation(0);
        break;

      case 'D':
      case 'd':
        game_engine_.GetShip().SetRotation(0);
        break;

      default:
        break;
    }
  }

  void ViewController::SetUpViews() {
    // Game background view
    game_background_ = ShapeView::createRect(ci::app::getWindowWidth(), 3 * ci::app::getWindowHeight() / 4 );
    game_background_->setFillColor(ci::Color(ci::Color::black() ) )
      .setSuperviewShouldIgnoreInBounds( true );

    // Game view container
    game_view_ = View::create("Game View" );
    game_view_->setPosition(0, 0 )
      .setDrawBounds( false )
      .setBoundsColor( boundsColor )
      .setName( "Game View" );
    game_view_->addSubview(game_background_);

    // UI background view
    ui_background_ = ShapeView::createRect(ci::app::getWindowHeight(), ci::app::getWindowWidth() / 4 );
    ui_background_->setFillColor(ci::Color(ci::CM_HSV, ui_hue, saturation, brightness ) )
      .setSuperviewShouldIgnoreInBounds( true );

    // UI view container
    ui_view_ = View::create("Game UI" );
    ui_view_->setPosition(0, 3 * ci::app::getWindowHeight() / 4 )
      .setDrawBounds( false )
      .setBoundsColor( boundsColor )
      .setName( "Game UI" );
    ui_view_->addSubview(ui_background_);
  }

  void ViewController::SetUpShip() {
    ship_image_ = ci::gl::Texture::create(ci::loadImage(
      ci::app::loadAsset("ship.png")));
    ship_image_->setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);

    Ship ship = game_engine_.GetShip();
    ship_shape_ = ShapeView::createRect(kShipSize, kShipSize);
    ship_shape_->setPosition(ship.GetPosition().first, ship.GetPosition().second);
    ship_shape_->setTexture(ship_image_);
    game_view_->addSubview(ship_shape_);
  }
}
