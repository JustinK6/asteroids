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

  float kWindowWidth = 800;
  float kWindowHeight = 800;

  ci::Color boundsColor( 1.0f, 1.0f, 1.0f );

  ViewControllerRef ViewController::create()
  {
    return ViewControllerRef(new ViewController() );
  }

  void ViewController::viewDidLoad()
  {
    // Scene BG
    game_background_ = ShapeView::createRect(kWindowWidth, 3 * kWindowHeight / 4 );
    game_background_->setFillColor(ci::Color(ci::Color::black() ) )
      .setSuperviewShouldIgnoreInBounds( true );

    // Node Container
    game_view_ = View::create("Game View" );
    game_view_->setPosition(0, 0 )
      .setDrawBounds( true )
      .setBoundsColor( boundsColor )
      .setName( "Game View" );
    game_view_->addSubview(game_background_);

    ui_background_ = ShapeView::createRect(kWindowWidth, kWindowHeight / 4 );
    ui_background_->setFillColor(ci::Color(ci::CM_HSV, ui_hue, saturation, brightness ) )
      .setSuperviewShouldIgnoreInBounds( true );

    // Node Container
    ui_view_ = View::create("Game UI" );
    ui_view_->setPosition(0, 3 * kWindowHeight / 4 )
      .setDrawBounds( true )
      .setBoundsColor( boundsColor )
      .setName( "Game UI" );
    ui_view_->addSubview(ui_background_);

    getView()->addSubview(game_view_);
    getView()->addSubview(ui_view_ );

    // Setup Scene (this class is the root node)
    getView()->setName( "Scene (Scene Root View)" )
      .setPosition( ci::vec2( 0, 0 ) )
      .setDrawBounds( true )
      .setBoundsColor( boundsColor );
  }
}
