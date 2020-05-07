//
// Created by ORaNgCHiKeN on 4/21/2020.
//

#include "asteroids/MainViewController.h"

#include "cinder/app/App.h"

using namespace po::scene;

namespace asteroids
{
  // Menu state.
  const int kMenuState = 0;

  // Game state.
  const int kGameRunning = 1;

  // Game over sate.
  const int kGameOver = 2;

  // Creates the main view controller.
  MainViewControllerRef MainViewController::create() {
    return MainViewControllerRef(new MainViewController());
  }

  // Creates views initially.
  void MainViewController::viewDidLoad() {
    state_ = kMenuState;

    menu_view_ = MenuView::create();
    game_view_ = GameView::create();
    game_over_view_ = GameOverView::create();
  }

  // Updates the view controller.
  void MainViewController::update() {
    getView()->removeAllSubviews();
    UpdateProgramState();

    // Adds subview based on state_
    switch (state_) {
      case kMenuState:
        getView()->addSubview(menu_view_);
        break;

      case kGameRunning:
        getView()->addSubview(game_view_);
        break;

      case kGameOver:
        getView()->addSubview(game_over_view_);
        break;

      default:
        break;
    }
  }

  // Updates the program state.
  void MainViewController::UpdateProgramState() {
    if (state_ == kMenuState && !menu_view_->IsRunning()) {
      game_view_->Reset();
      state_ = kGameRunning;

      return;
    }

    if (state_ == kGameRunning && !game_view_->IsRunning().first) {
      score_ = game_view_->IsRunning().second;
      game_over_view_->SetScore(score_);
      game_over_view_->Reset();
      state_ = kGameOver;

      return;
    }

    if (state_ == kGameOver && !game_over_view_->IsRunning()) {
      menu_view_->Reset();
      state_ = kMenuState;

      return;
    }
  }
}
