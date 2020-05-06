#pragma once

#include <poScene/ImageView.h>
#include "cinder/app/KeyEvent.h"
#include "poScene/ViewController.h"
#include "poScene/ShapeView.h"
#include "poScene/TextView.h"
#include "Engine.h"
#include "GameView.h"
#include "GameOverView.h"
#include "MenuView.h"

namespace asteroids
{
  class MainViewController;
  typedef std::shared_ptr<MainViewController> MainViewControllerRef;

  class MainViewController
    : public po::scene::ViewController {
  public:
    static MainViewControllerRef create();

    void viewDidLoad() override;

    void update() override ;

  private:
    MenuViewRef menu_view_;
    GameViewRef game_view_;
    GameOverViewRef game_over_view_;

    int state_;
    int score_;

    void UpdateProgramState();
  };
}
