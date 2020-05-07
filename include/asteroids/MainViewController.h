#pragma once

#include <poScene/ImageView.h>
#include "cinder/app/KeyEvent.h"
#include "poScene/ViewController.h"
#include "poScene/ShapeView.h"
#include "poScene/TextView.h"
#include "Engine.h"
#include "GameView.h"
#include "GameOverView.h"
#include "MenuView.h"

namespace asteroids
{
  class MainViewController;
  typedef std::shared_ptr<MainViewController> MainViewControllerRef;

  // Represents the main view controller that controls the different views of the program
  class MainViewController
    : public po::scene::ViewController {
  public:
    // Creates the view controller
    static MainViewControllerRef create();

    // Loads views initially and sets up views
    void viewDidLoad() override;

    // Updates the view controller
    void update() override ;

  private:
    // The view showing the menu screen
    MenuViewRef menu_view_;

    // The view showing the game screen
    GameViewRef game_view_;

    // The view showing the game over screen
    GameOverViewRef game_over_view_;

    // Represents the view currently being shown by the view contoller
    int state_;

    // Represents the score of the game
    int score_;

    // Updates the state of the view controller
    void UpdateProgramState();
  };
}
