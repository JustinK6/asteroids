//
// Created by ORaNgCHiKeN on 4/21/2020.
//

#include "asteroids/MainViewController.h"

#include "cinder/app/App.h"

using namespace po::scene;

namespace asteroids
{

  MainViewControllerRef MainViewController::create() {
    return MainViewControllerRef(new MainViewController());
  }

  void MainViewController::viewDidLoad() {
    // Game background view
    game_background_ = ShapeView::createRect(ci::app::getWindowWidth(), 3 * ci::app::getWindowHeight() / 4 );
    game_background_->setFillColor(ci::Color(ci::Color::black()))
      .setSuperviewShouldIgnoreInBounds( true );

    game_view_ = GameView::create();

    getView()->addSubview(game_background_);

    getView()->addSubview(game_view_);
  }

  bool MainViewController::isRunning() {
    return true;
  }
}
