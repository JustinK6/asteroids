#pragma once

#include "cinder/app/KeyEvent.h"
#include "poScene/ViewController.h"
#include "poScene/ShapeView.h"
#include "poScene/TextView.h"

namespace asteroids
{
  class ViewController;
  typedef std::shared_ptr<ViewController> ViewControllerRef;

  class ViewController
    : public po::scene::ViewController
  {
  public:
    static ViewControllerRef create();

    void viewDidLoad() override;

  private:
    po::scene::ViewRef game_view_;
    po::scene::ShapeViewRef game_background_;

    po::scene::ViewRef ui_view_;
    po::scene::ShapeViewRef ui_background_;
  };
}
