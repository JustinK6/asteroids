//
// Created by ORaNgCHiKeN on 5/5/2020.
//

#ifndef FINALPROJECT_MENUVIEW_H
#define FINALPROJECT_MENUVIEW_H

#include <memory>
#include <poScene/ViewController.h>
#include <poScene/TextView.h>
#include <cinder/Text.h>
#include <poScene/ImageView.h>

namespace asteroids {
  class MenuView;
  typedef std::shared_ptr<MenuView> MenuViewRef;

  // Represents the view showing the menu screen
  class MenuView
    : public po::scene::View {
  public:
    // Creates the menu view
    static MenuViewRef create();
    virtual ~MenuView();

    // Sets up the menu view
    void setup();

    // Resets the menu view
    void Reset();

    // Checks to see if the view is running/completed
    bool IsRunning();

  private:
    // Represents the state of the view
    bool running_;

    // Represents the menu image
    ci::gl::TextureRef menu_image_;
    po::scene::ImageViewRef menu_;

    // Checks for key events
    void KeyDown(ci::app::KeyEvent KeyEvent);
  };
}


#endif //FINALPROJECT_GAMEOVERVIEW_H
