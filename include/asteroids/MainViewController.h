#pragma once

#include <poScene/ImageView.h>
#include "cinder/app/KeyEvent.h"
#include "poScene/ViewController.h"
#include "poScene/ShapeView.h"
#include "poScene/TextView.h"
#include "Engine.h"
#include "GameView.h"

namespace asteroids
{
  class MainViewController;
  typedef std::shared_ptr<MainViewController> MainViewControllerRef;

  class MainViewController
    : public po::scene::ViewController {
  public:
    static MainViewControllerRef create();

    void viewDidLoad() override;

    bool isRunning();

  private:
    po::scene::ShapeViewRef game_background_;

    GameViewRef game_view_;
  };
}
