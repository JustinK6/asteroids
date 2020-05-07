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

  // Represents a view that shows the game over screen
  class GameOverView
    : public po::scene::View {
  public:
    // Creates the view
    static GameOverViewRef create();
    virtual ~GameOverView();

    // Sets up the view and subviews
    void setup();

    // Resets the views
    void Reset();

    // Checks to see if view is running/completed
    bool IsRunning();

    // Sets the score to display on the screen
    void SetScore(int score);

  private:
    // The score to display on the game over screen
    int score_;

    // Represents the state of the overall view
    bool running_;

    // Represents the score text
    ci::TextBox score_text_;
    po::scene::TextViewRef score_text_box_;

    // Represents the game over image
    ci::gl::TextureRef game_over_image_;
    po::scene::ImageViewRef game_over_;

    // Checks for key events
    void KeyDown(ci::app::KeyEvent KeyEvent);

    // Generates the score text with score_
    std::string GetScoreText();
  };
}


#endif //FINALPROJECT_GAMEOVERVIEW_H
