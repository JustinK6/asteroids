//
// Created by ORaNgCHiKeN on 5/5/2020.
//

#ifndef FINALPROJECT_GAMEVIEW_H
#define FINALPROJECT_GAMEVIEW_H

#include <poScene/View.h>
#include <cinder/Text.h>
#include <poScene/TextView.h>
#include <poScene/ImageView.h>
#include "Engine.h"

namespace asteroids {
  class GameView;
  typedef std::shared_ptr<GameView> GameViewRef;

  class GameView
    : public po::scene::View {
  public:
    static GameViewRef create();
    virtual ~GameView();

    void setup();
    void Reset();
    void update() override;

    std::string GetScoreText();
    bool IsRunning();
  private:
    po::scene::ViewRef game_view_;

    Engine game_engine_;

    ci::TextBox score_text_;
    po::scene::TextViewRef score_text_box_;

    ci::gl::TextureRef health_image_;
    po::scene::ImageViewRef health_;

    ci::gl::TextureRef shield_image_;
    po::scene::ImageViewRef shield_;

    ci::gl::TextureRef ship_image_;
    po::scene::ImageViewRef ship_shape_;

    ci::gl::TextureRef bullet_image_;
    std::vector<po::scene::ImageViewRef> bullets_;

    ci::gl::TextureRef asteroid_image_;
    std::vector<po::scene::ImageViewRef> asteroids_;

    void UpdateShip();
    void UpdateBulletViews();
    void UpdateAsteroidViews();
    void UpdateHealthView();
    void UpdateShieldView();

    void KeyDown(ci::app::KeyEvent KeyEvent);
    void KeyUp(ci::app::KeyEvent KeyEvent);

    void SetUpViews();
    void SetUpUI();
    void SetUpShip();
    void SetUpScoreText();
    void LoadTextures();
  };

}

#endif //FINALPROJECT_GAMEVIEW_H
