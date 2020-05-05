//
// Created by ORaNgCHiKeN on 5/5/2020.
//

#include "asteroids/EndViewController.h"

namespace asteroids {
  const int kScoreFontSize = 32;

  EndViewControllerRef EndViewController::create() {
    return EndViewControllerRef(new EndViewController());
  }

  void EndViewController::viewDidLoad() {
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

    score_text_.setText(GetScoreText());
    score_text_box_ = po::scene::TextView::create();
    score_text_box_->setPosition(ci::app::getWindowWidth() / 2 - score_text_box_->getWidth(),
      ci::app::getWindowHeight() / 2 - score_text_box_->getHeight() / 2)
      .setSuperviewShouldIgnoreInBounds( true );
    score_text_box_->setCiTextBox(score_text_);

    getView()->addSubview(game_over_);
    getView()->addSubview(score_text_box_);
  }

  void EndViewController::update() {

  }

  bool EndViewController::isRunning() {
    return false;
  }

  std::string EndViewController::GetScoreText() {
    std::stringstream ss;
    ss << "Score: ";
    ss << score_;

    return ss.str();
  }

  void EndViewController::SetScore(int score) {
    score_ = score;
  }
}
