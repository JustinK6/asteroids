//
// Created by ORaNgCHiKeN on 5/5/2020.
//

#ifndef FINALPROJECT_ENDVIEWCONTROLLER_H
#define FINALPROJECT_ENDVIEWCONTROLLER_H

#include <memory>
#include <poScene/ViewController.h>
#include <poScene/TextView.h>
#include <cinder/Text.h>
#include <poScene/ImageView.h>

namespace asteroids {
  class EndViewController;
  typedef std::shared_ptr<EndViewController> EndViewControllerRef;

  class EndViewController
    : public po::scene::ViewController {
  public:
    static EndViewControllerRef create();

    void viewDidLoad() override;

    void update() override;

    void SetScore(int score);

    bool isRunning();

  private:
    int score_;

    ci::TextBox score_text_;
    po::scene::TextViewRef score_text_box_;

    ci::gl::TextureRef game_over_image_;
    po::scene::ImageViewRef game_over_;

    std::string GetScoreText();
  };
}


#endif //FINALPROJECT_ENDVIEWCONTROLLER_H
