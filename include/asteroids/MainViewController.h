#pragma once

#include "cinder/app/KeyEvent.h"
#include "poScene/ViewController.h"
#include "poScene/ShapeView.h"
#include "poScene/TextView.h"

namespace asteroids
{
  class MainViewController;
  typedef std::shared_ptr<MainViewController> MainViewControllerRef;

  class MainViewController
    : public po::scene::ViewController
  {
  public:
    static MainViewControllerRef create();

    void viewDidLoad() override;

  protected:
    void update();

  private:
    po::scene::ShapeViewRef main_background_;

    po::scene::ViewRef game_view_;
    po::scene::ShapeViewRef game_view_background_;

    po::scene::ViewRef ui_view_;
    po::scene::ShapeViewRef ui_view_background_;
  };
}
