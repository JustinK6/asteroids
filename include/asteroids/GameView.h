//
// Created by ORaNgCHiKeN on 5/5/2020.
//

#ifndef FINALPROJECT_GAMEVIEW_H
#define FINALPROJECT_GAMEVIEW_H

#include <poScene/View.h>
#include <cinder/Text.h>
#include <poScene/TextView.h>
#include <poScene/ImageView.h>
#include "Engine.h"

namespace asteroids {
  class GameView;
  typedef std::shared_ptr<GameView> GameViewRef;

  // Represents a view displaying all game elements
  class GameView
    : public po::scene::View {
  public:
    // Creates a new GameView
    static GameViewRef create();
    virtual ~GameView();

    // Sets up the game view
    void setup();

    // Resets the game view
    void Reset();

    // Updates the game view
    void update() override;

    // Checks to see if the view is running/completed
    std::pair<bool, int> IsRunning();
  private:
    // The game view containing game elements
    po::scene::ViewRef game_view_;

    // The game engine controlling the game entities
    Engine game_engine_;

    // Represents the score text showing the score of the player
    ci::TextBox score_text_;
    po::scene::TextViewRef score_text_box_;

    // Represents the health image showing the health of the player
    ci::gl::TextureRef health_image_;
    po::scene::ImageViewRef health_;

    // Represents the shield image showing the shield state of player
    ci::gl::TextureRef shield_image_;
    po::scene::ImageViewRef shield_;

    // Represents the ship image showing the ship of the player
    ci::gl::TextureRef ship_image_;
    po::scene::ImageViewRef ship_shape_;

    // Represents the bullet image showing the bullets in the game
    ci::gl::TextureRef bullet_image_;
    std::vector<po::scene::ImageViewRef> bullets_;

    // Represents the asteroid image showing the asteroids in the game
    ci::gl::TextureRef asteroid_image_;
    std::vector<po::scene::ImageViewRef> asteroids_;

    // Updates the state and position of the ship view
    void UpdateShip();

    // Updates the state and position of the bullet views
    void UpdateBulletViews();

    // Updates the state and position of the asteroid views
    void UpdateAsteroidViews();

    // Updates the state of the health bar view
    void UpdateHealthView();

    // Updates the state of the shield view
    void UpdateShieldView();

    // Checks for key events
    void KeyDown(ci::app::KeyEvent KeyEvent);
    void KeyUp(ci::app::KeyEvent KeyEvent);

    // Sets up all views
    void SetUpViews();

    // Sets up UI views
    void SetUpUI();

    // Sets up view showing the ship
    void SetUpShip();

    // Sets up view showing the score
    void SetUpScoreText();

    // Loads initial textures for image views
    void LoadTextures();

    // Gets the score text to display using the game engine score
    std::string GetScoreText();
  };

}

#endif //FINALPROJECT_GAMEVIEW_H
