#pragma once

#include "cinder/app/KeyEvent.h"
#include "poScene/ViewController.h"
#include "poScene/ShapeView.h"
#include "poScene/TextView.h"

namespace asteroids
{
  class GameViewController;
  typedef std::shared_ptr<GameViewController> GameViewControllerRef;

  class GameViewController
    : public po::scene::ViewController
  {
  public:
    static GameViewControllerRef create();

    void viewDidLoad() override;

  protected:
    void update();

  private:
    ci::TextBox mInfoText;
    po::scene::TextViewRef mWindowTextBox;

    po::scene::ShapeViewRef mBG;
    po::scene::TextViewRef mTextView;

    po::scene::ViewRef mContainerView;
    po::scene::ShapeViewRef mContainerViewBG;
    po::scene::TextViewRef mContainerTextView;


    void nodeMouseOver( po::scene::MouseEvent& event );
    po::scene::ViewRef mSelectedView;

    std::string getViewInfo( po::scene::ViewRef );

  };
}
