//
// Created by ORaNgCHiKeN on 5/5/2020.
//

#include "asteroids/GameOverView.h"

namespace asteroids {
  const int kScoreFontSize = 32;

  GameOverViewRef GameOverView::create() {
    GameOverViewRef ref = std::shared_ptr<GameOverView>(new GameOverView());
    ref->setup();
    return ref;
  }

  GameOverView::~GameOverView() {}

  void GameOverView::Reset() {
    running_ = true;
  }

  void GameOverView::setup() {
    // Connect to key events
    ci::app::getWindow()->getSignalKeyDown().connect(std::bind( &GameOverView::KeyDown,
      this, std::placeholders::_1));
    running_ = true;

    // Set up game over text image
    game_over_image_ = ci::gl::Texture::create(ci::loadImage(
      ci::app::loadAsset("gameovertext.png")));
    game_over_image_->setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);

    game_over_ = po::scene::ImageView::create(game_over_image_);
    game_over_->setScale(0.5);
    game_over_->setPosition(ci::app::getWindowWidth() / 2 - game_over_->getScaledWidth() / 2,
      ci::app::getWindowHeight() / 4 - game_over_->getScaledHeight() / 2);

    // Set up score text
    score_text_.size(ci::TextBox::GROW, ci::TextBox::GROW)
      .color(ci::Color(0, 1, 0))
      .alignment(ci::TextBox::Alignment::LEFT)
      .font(ci::Font( "Arial", kScoreFontSize));

    score_text_.setText(score_);
    score_text_box_ = po::scene::TextView::create();
    score_text_box_->setPosition(ci::app::getWindowWidth() / 2 - 100,
      ci::app::getWindowHeight() / 2 - score_text_box_->getHeight() / 2)
      .setSuperviewShouldIgnoreInBounds( true );
    score_text_box_->setCiTextBox(score_text_);

    addSubview(game_over_);
    addSubview(score_text_box_);
  }

  bool GameOverView::IsRunning() {
    return running_;
  }

  void GameOverView::SetScoreText(std::string text) {
    score_ = text;
  }

  void GameOverView::KeyDown(ci::app::KeyEvent KeyEvent) {
    if (KeyEvent.getChar() == 'R' || KeyEvent.getChar() == 'r') {
      running_ = false;
    }
  }
}
