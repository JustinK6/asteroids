//
// Created by ORaNgCHiKeN on 4/21/2020.
//

#include "asteroids/MainViewController.h"

#include "cinder/app/App.h"

using namespace po::scene;

namespace asteroids
{
  const int kMenuState = 0;
  const int kGameRunning = 1;
  const int kGameOver = 2;

  MainViewControllerRef MainViewController::create() {
    return MainViewControllerRef(new MainViewController());
  }

  void MainViewController::viewDidLoad() {
    state_ = kMenuState;

    menu_view_ = MenuView::create();
    game_view_ = GameView::create();
    game_over_view_ = GameOverView::create();
  }

  void MainViewController::update() {
    getView()->removeAllSubviews();
    UpdateProgramState();

    switch (state_) {
      case kMenuState:
        getView()->addSubview(menu_view_);
        break;

      case kGameRunning:
        game_over_view_->SetScoreText(game_view_->GetScoreText());
        getView()->addSubview(game_view_);
        break;

      case kGameOver:
        getView()->addSubview(game_over_view_);
        break;

      default:
        break;
    }
  }

  void MainViewController::UpdateProgramState() {
    if (state_ == kMenuState && !menu_view_->IsRunning()) {
      game_view_->Reset();
      state_ = kGameRunning;

      return;
    }

    if (state_ == kGameRunning && !game_view_->IsRunning()) {
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
