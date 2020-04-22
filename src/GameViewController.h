//
// Created by ORaNgCHiKeN on 4/21/2020.
//

#ifndef FINALPROJECT_GAMEVIEWCONTROLLER_H
#define FINALPROJECT_GAMEVIEWCONTROLLER_H

#include <memory>
#include <poScene/ViewController.h>
#include <cinder/Text.h>

namespace asteroids {
  class GameViewController;
  typedef std::shared_ptr<GameViewController> GameViewControllerRef;

  class GameViewController : public po::scene::ViewController {
  public:
    static GameViewControllerRef create();

    void viewDidLoad() override;

  protected:
    void update();

  private:
    ci::TextBox test_text_;
  };
}


#endif //FINALPROJECT_GAMEVIEWCONTROLLER_H
