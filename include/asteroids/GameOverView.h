//
// Created by ORaNgCHiKeN on 5/5/2020.
//

#ifndef FINALPROJECT_GAMEOVERVIEW_H
#define FINALPROJECT_GAMEOVERVIEW_H

#include <memory>
#include <poScene/ViewController.h>
#include <poScene/TextView.h>
#include <cinder/Text.h>
#include <poScene/ImageView.h>

namespace asteroids {
  class GameOverView;
  typedef std::shared_ptr<GameOverView> GameOverViewRef;

  class GameOverView
    : public po::scene::View {
  public:
    static GameOverViewRef create();
    virtual ~GameOverView();

    void setup();
    void Reset();

    bool IsRunning();
    void SetScoreText(std::string score);

  private:
    std::string score_;

    bool running_;

    ci::TextBox score_text_;
    po::scene::TextViewRef score_text_box_;

    ci::gl::TextureRef game_over_image_;
    po::scene::ImageViewRef game_over_;

    void KeyDown(ci::app::KeyEvent KeyEvent);
  };
}


#endif //FINALPROJECT_GAMEOVERVIEW_H
