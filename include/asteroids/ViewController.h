#pragma once

#include "cinder/app/KeyEvent.h"
#include "poScene/ViewController.h"
#include "poScene/ShapeView.h"
#include "poScene/TextView.h"
#include "Engine.h"

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

    void update() override;

  private:
    po::scene::ViewRef game_view_;
    po::scene::ShapeViewRef game_background_;

    po::scene::ViewRef ui_view_;
    po::scene::ShapeViewRef ui_background_;

    Engine game_engine_;

    ci::gl::TextureRef ship_image_;
    po::scene::ShapeViewRef ship_shape_;

    void UpdateShip();

    void KeyDown(ci::app::KeyEvent KeyEvent);
    void KeyUp(ci::app::KeyEvent KeyEvent);
    void SetUpViews();
  };
}
