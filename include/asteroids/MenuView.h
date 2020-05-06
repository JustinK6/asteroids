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

  class MenuView
    : public po::scene::View {
  public:
    static MenuViewRef create();
    virtual ~MenuView();

    void setup();
    void Reset();

    bool IsRunning();

  private:
    bool running_;

    ci::gl::TextureRef menu_image_;
    po::scene::ImageViewRef menu_;

    void KeyDown(ci::app::KeyEvent KeyEvent);
  };
}


#endif //FINALPROJECT_GAMEOVERVIEW_H
