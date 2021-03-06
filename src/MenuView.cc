//
// Created by ORaNgCHiKeN on 5/6/2020.
//

#include "asteroids/MenuView.h"

namespace asteroids {
  const int kScoreFontSize = 32;

  // Creates a menu view.
  MenuViewRef MenuView::create() {
    MenuViewRef ref = std::shared_ptr<MenuView>(new MenuView());
    ref->setup();
    return ref;
  }

  MenuView::~MenuView() {}

  // Resets the menu view.
  void MenuView::Reset() {
    running_ = true;
  }

  //Sets up the view.
  void MenuView::setup() {
    // Connect to key events
    ci::app::getWindow()->getSignalKeyDown().connect(std::bind(&MenuView::KeyDown,
      this, std::placeholders::_1));
    running_ = true;

    // Set up menu image view
    menu_image_ = ci::gl::Texture::create(ci::loadImage(
      ci::app::loadAsset("titlescreen.png")));
    menu_image_->setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);

    menu_ = po::scene::ImageView::create(menu_image_);
    menu_->setScale(1);
    menu_->setPosition(ci::app::getWindowWidth() / 2 - menu_->getScaledWidth() / 2,
                            ci::app::getWindowHeight() / 2 - menu_->getScaledHeight() / 2);

    addSubview(menu_);
  }

  // Checks to see if menu view is running/finished.
  // @return True if running, false if finished
  bool MenuView::IsRunning() {
    return running_;
  }

  // Checks for key events.
  void MenuView::KeyDown(ci::app::KeyEvent KeyEvent) {
    if (KeyEvent.getChar() == 'S' || KeyEvent.getChar() == 's') {
      running_ = false;
    }
  }
}