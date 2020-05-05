#pragma once

#include <poScene/ImageView.h>
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

    po::scene::ShapeViewRef ui_background_;

    Engine game_engine_;

    ci::TextBox score_text_;
    po::scene::TextViewRef score_text_box_;

    ci::gl::TextureRef health_image_;
    po::scene::ImageViewRef health_;

    ci::gl::TextureRef ship_image_;
    po::scene::ImageViewRef ship_shape_;

    ci::gl::TextureRef bullet_image_;
    std::vector<po::scene::ImageViewRef> bullets_;

    ci::gl::TextureRef asteroid_image_;
    std::vector<po::scene::ImageViewRef> asteroids_;

    void UpdateShip();
    void UpdateBulletViews();
    void UpdateAsteroidViews();

    std::string GetScoreText();

    void KeyDown(ci::app::KeyEvent KeyEvent);
    void KeyUp(ci::app::KeyEvent KeyEvent);

    void SetUpViews();
    void SetUpUI();
    void SetUpShip();
    void SetUpScoreText();
  };
}
