//
// Created by ORaNgCHiKeN on 4/21/2020.
//

#include "asteroids/MainViewController.h"

#include "cinder/app/App.h"

using namespace po::scene;

namespace asteroids
{
  float hueIncrement = 0.05f;
  float hue = 0.5f;
  float ContainerHue = hue + hueIncrement;
  float brightness = 0.65f;
  float saturation = 0.5f;

  int kWindowWidth = 800;
  int kWindowHeight = 600;

  ci::Color boundsColor( 1.0f, 1.0f, 1.0f );

  MainViewControllerRef MainViewController::create()
  {
    return MainViewControllerRef(new MainViewController() );
  }

  void MainViewController::viewDidLoad()
  {
    // Scene BG
    main_background_ = ShapeView::createRect(kWindowWidth / 100, kWindowHeight / 100 );
    main_background_->setFillColor(ci::Color(ci::CM_HSV, hue, saturation, brightness ) )
      .setSuperviewShouldIgnoreInBounds( true );
    getView()->addSubview(main_background_ );

    // Node Container
    game_view_ = View::create("View Container" );
    game_view_->setPosition(100, 150 )
      .setDrawBounds( true )
      .setBoundsColor( boundsColor )
      .setName( "View Container" );

    game_view_background_ = ShapeView::createRect(100, 3 );
    game_view_background_->setFillColor(ci::Color(ci::CM_HSV, ContainerHue, saturation, brightness ) )
      .setSuperviewShouldIgnoreInBounds( true );

    getView()->addSubview(game_view_ );

    // Setup Scene (this class is the root node)
    getView()->setName( "Scene (Scene Root View)" )
      .setPosition( ci::vec2( 0, 0 ) )
      .setDrawBounds( true )
      .setBoundsColor( boundsColor );
  }

  void MainViewController::update()
  {
    // Set the BGs
    main_background_->setPosition(getView()->getBounds().getUpperLeft() )
      .setScale( getView()->getSize() );

    game_view_background_->setPosition(game_view_->getBounds().getUpperLeft() )
      .setScale(game_view_->getSize() );
  }
}
