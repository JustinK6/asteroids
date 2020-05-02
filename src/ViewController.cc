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

  ci::Color boundsColor( 1.0f, 1.0f, 1.0f );

  ViewControllerRef ViewController::create() {
    return ViewControllerRef(new ViewController() );
  }

  void ViewController::viewDidLoad() {
    SetUpViews();

    // Connect to key events
    ci::app::getWindow()->getSignalKeyDown().connect(std::bind( &ViewController::KeyDown,
      this, std::placeholders::_1));

    ship_image_ = ci::gl::Texture::create(ci::loadImage(
      ci::app::loadAsset("ship.png")));
    ship_image_->setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);

    Ship ship = game_engine_.GetShip();
    ship_shape_ = ShapeView::createRect(kShipSize, kShipSize);
    ship_shape_->setPosition(ship.GetPosition().first, ship.GetPosition().second);
    ship_shape_->setTexture(ship_image_);
    game_view_->addSubview(ship_shape_);

    getView()->addSubview(game_view_);
    getView()->addSubview(ui_view_ );

    // Setup Scene (this class is the root node)
    getView()->setName("Scene (Scene Root View)")
      .setPosition(ci::vec2(0, 0))
      .setDrawBounds(false)
      .setBoundsColor(boundsColor);
  }

  void ViewController::update() {
    // Update the location of the ship
    Ship ship = game_engine_.GetShip();
    ship_shape_->setPosition(ship.GetPosition().first, ship.GetPosition().second);
  }

  void ViewController::KeyDown(ci::app::KeyEvent KeyEvent) {

  }

  void ViewController::SetUpViews() {
    // Scene BG
    game_background_ = ShapeView::createRect(ci::app::getWindowWidth(), 3 * ci::app::getWindowHeight() / 4 );
    game_background_->setFillColor(ci::Color(ci::Color::black() ) )
      .setSuperviewShouldIgnoreInBounds( true );

    // Node Container
    game_view_ = View::create("Game View" );
    game_view_->setPosition(0, 0 )
      .setDrawBounds( false )
      .setBoundsColor( boundsColor )
      .setName( "Game View" );
    game_view_->addSubview(game_background_);

    ui_background_ = ShapeView::createRect(ci::app::getWindowHeight(), ci::app::getWindowWidth() / 4 );
    ui_background_->setFillColor(ci::Color(ci::CM_HSV, ui_hue, saturation, brightness ) )
      .setSuperviewShouldIgnoreInBounds( true );

    // Node Container
    ui_view_ = View::create("Game UI" );
    ui_view_->setPosition(0, 3 * ci::app::getWindowHeight() / 4 )
      .setDrawBounds( false )
      .setBoundsColor( boundsColor )
      .setName( "Game UI" );
    ui_view_->addSubview(ui_background_);
  }
}
