//
// Created by ORaNgCHiKeN on 4/21/2020.
//

#include "asteroids/MainViewController.h"

#include "cinder/app/App.h"

using namespace po::scene;

namespace asteroids
{
  const int kTextFontSize = 32;

  const int kMaxHealth = 4;

  ci::Color boundsColor( 1.0f, 1.0f, 1.0f );

  ViewControllerRef MainViewController::create() {
    return ViewControllerRef(new MainViewController() );
  }

  void MainViewController::viewDidLoad() {
    // Connect to key events
    ci::app::getWindow()->getSignalKeyDown().connect(std::bind( &MainViewController::KeyDown,
      this, std::placeholders::_1));
    ci::app::getWindow()->getSignalKeyUp().connect(std::bind( &MainViewController::KeyUp,
      this, std::placeholders::_1));

    LoadTextures();
    SetUpViews();
    SetUpUI();
    SetUpShip();
    SetUpScoreText();

    // Add dimensions of entities to game engine
    game_engine_.InitializeEntityDimensions(ship_shape_->getWidth(), ship_shape_->getHeight(),
      bullet_image_->getWidth(), bullet_image_->getHeight(),
      asteroid_image_->getWidth(), asteroid_image_->getHeight());

    // Add views to main view controller
    getView()->addSubview(game_view_);
    getView()->addSubview(ui_background_);
    getView()->addSubview(score_text_box_);
    getView()->addSubview(health_);
    getView()->addSubview(shield_);

    // Setup Scene (this class is the root node)
    getView()->setName("Scene (Scene Root View)")
      .setPosition(ci::vec2(0, 0))
      .setDrawBounds(false)
      .setBoundsColor(boundsColor);
  }

  void MainViewController::update() {
    // Remove all subviews to update
    game_view_->removeAllSubviews();
    game_view_->addSubview(game_background_);

    // Update the location of the ship
    UpdateShip();

    // Update locations of bullets
    game_engine_.UpdateBullets(ci::app::getWindowWidth(), 3 * ci::app::getWindowHeight() / 4);
    UpdateBulletViews();

    // Update locations of asteroids
    game_engine_.UpdateAsteroids(ci::app::getWindowWidth(), 3 * ci::app::getWindowHeight() / 4);
    UpdateAsteroidViews();

    // Update Shields
    game_engine_.UpdateShields();
    UpdateShieldView();

    // Process collisions
    game_engine_.CheckCollisions();

    // Update health bar
    UpdateHealthView();

    // Update score text
    score_text_.setText(GetScoreText());
    score_text_box_->setCiTextBox(score_text_);
  }

  void MainViewController::UpdateShip() {
    Ship ship = game_engine_.GetShip();

    // Checking for going off the edge of the screen
    double ship_x = ship.GetPosition().first;
    double ship_y = ship.GetPosition().second;

    // Check x position
    if (ship_x > ci::app::getWindowWidth()) {
      game_engine_.UpdateShipPosition(0, ship_y);
    } else if (ship_x < 0) {
      game_engine_.UpdateShipPosition(ci::app::getWindowWidth(), ship_y);
    }

    // Check y position
    if (ship_y > 3 * ci::app::getWindowHeight() / 4) {
      game_engine_.UpdateShipPosition(ship_x, 0);
    } else if (ship_y < 0) {
      game_engine_.UpdateShipPosition(ship_x, 3 * ci::app::getWindowHeight() / 4);
    }

    // Updates the location of the ship
    game_engine_.UpdateShip();
    ship = game_engine_.GetShip();

    // Sets the new retrieved position of the ship in the view
    ship_shape_->setPosition(ship.GetPosition().first, ship.GetPosition().second);
    ship_shape_->setRotation(ship.GetRotation());
    ship_shape_->setOffset(-ship_shape_->getWidth() / 2.0, -ship_shape_->getHeight() / 2.0);

    game_view_->addSubview(ship_shape_);
  }

  void MainViewController::UpdateBulletViews() {
    bullets_.clear();

    for (int i = 0; i < game_engine_.GetBullets().size(); i++) {
      Bullet temp = game_engine_.GetBullets()[i];

      double bullet_x = temp.GetPosition().first;
      double bullet_y = temp.GetPosition().second;

      ImageViewRef bullet = ImageView::create(bullet_image_);
      bullet->setOffset(-bullet->getScaledWidth() / 2, -bullet->getScaledHeight() / 2);
      bullet->setPosition(bullet_x, bullet_y);

      bullets_.push_back(bullet);
    }

    for (int i = 0; i < bullets_.size(); i++) {
      game_view_->addSubview(bullets_[i]);
    }
  }

  void MainViewController::UpdateAsteroidViews() {
    asteroids_.clear();

    for (int i = 0; i < game_engine_.GetAsteroids().size(); i++) {
      Asteroid temp = game_engine_.GetAsteroids()[i];

      double asteroid_x = temp.GetPosition().first;
      double asteroid_y = temp.GetPosition().second;

      ImageViewRef asteroid = ImageView::create(asteroid_image_);
      asteroid->setPosition(asteroid_x, asteroid_y);
      asteroid->setScale(temp.GetScale());
      asteroid->setOffset(-asteroid->getScaledWidth() / 2, -asteroid->getScaledHeight() / 2);

      asteroids_.push_back(asteroid);
    }

    for (int i = 0; i < asteroids_.size(); i++) {
      game_view_->addSubview(asteroids_[i]);
    }
  }

  void MainViewController::UpdateHealthView() {
    int health = game_engine_.GetShip().GetHealth();

    // Heart sprite from: https://closeluca.itch.io/heart
    if (health > kMaxHealth - 1) {
      health_image_ = ci::gl::Texture::create(ci::loadImage(
        ci::app::loadAsset("fourhearts.png")));
    } else if (health > kMaxHealth - 2) {
      health_image_ = ci::gl::Texture::create(ci::loadImage(
        ci::app::loadAsset("threehearts.png")));
    } else if (health > kMaxHealth - 3) {
      health_image_ = ci::gl::Texture::create(ci::loadImage(
        ci::app::loadAsset("twohearts.png")));
    } else if (health > kMaxHealth - 4) {
      health_image_ = ci::gl::Texture::create(ci::loadImage(
        ci::app::loadAsset("oneheart.png")));
    } else {
      health_image_ = ci::gl::Texture::create(ci::loadImage(
        ci::app::loadAsset("nohearts.png")));
    }

    health_image_->setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
    health_->setTexture(health_image_);
  }

  void MainViewController::UpdateShieldView() {
    // Shield icon from: https://icons8.com/icons/set/shield
    if (game_engine_.isShielded()) {
      shield_image_ = ci::gl::Texture::create(ci::loadImage(
        ci::app::loadAsset("shieldactive.png")));
    } else {
      shield_image_ = ci::gl::Texture::create(ci::loadImage(
        ci::app::loadAsset("shieldinactive.png")));
    }

    shield_image_->setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
    shield_->setTexture(shield_image_);
  }

  //Gets the score in a string format
  std::string MainViewController::GetScoreText() {
    std::stringstream ss;
    ss << "Score: ";
    ss << game_engine_.GetScore();

    return ss.str();
  }

  void MainViewController::KeyDown(ci::app::KeyEvent KeyEvent) {
    switch (KeyEvent.getChar()) {
      case 'W':
      case 'w':
        game_engine_.GetShip().SetMovement(5);
        break;

      case 'A':
      case 'a':
        game_engine_.GetShip().SetRotation(-0.1);
        break;

      case 'D':
      case 'd':
        game_engine_.GetShip().SetRotation(0.1);
        break;

      case 'F':
      case 'f':
        game_engine_.FireBullet();
        break;

      default:
        break;
    }
  }

  void MainViewController::KeyUp(ci::app::KeyEvent KeyEvent) {
    switch (KeyEvent.getChar()) {
      case 'W':
      case 'w':
        game_engine_.GetShip().SetMovement(0);
        break;

      case 'A':
      case 'a':
        game_engine_.GetShip().SetRotation(0);
        break;

      case 'D':
      case 'd':
        game_engine_.GetShip().SetRotation(0);
        break;

      default:
        break;
    }
  }

  void MainViewController::LoadTextures() {
    // Heart sprite from: https://closeluca.itch.io/heart
    health_image_ = ci::gl::Texture::create(ci::loadImage(
      ci::app::loadAsset("fourhearts.png")));
    health_image_->setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);

    // Shield icon from: https://icons8.com/icons/set/shield
    shield_image_ = ci::gl::Texture::create(ci::loadImage(
      ci::app::loadAsset("shieldactive.png")));
    shield_image_->setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);

    // Load bullet image texture
    bullet_image_ = ci::gl::Texture::create(ci::loadImage(
      ci::app::loadAsset("bullet.png")));
    bullet_image_->setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);

    // Load asteroid image texture
    asteroid_image_ = ci::gl::Texture::create(ci::loadImage(
      ci::app::loadAsset("asteroid.png")));
    asteroid_image_->setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
  }

  void MainViewController::SetUpViews() {
    // Game background view
    game_background_ = ShapeView::createRect(ci::app::getWindowWidth(), 3 * ci::app::getWindowHeight() / 4 );
    game_background_->setFillColor(ci::Color(ci::Color::black()))
      .setSuperviewShouldIgnoreInBounds( true );

    // Game view container
    game_view_ = View::create("Game View" );
    game_view_->setPosition(0, 0 )
      .setDrawBounds( false )
      .setBoundsColor( boundsColor )
      .setName( "Game View" );
    game_view_->addSubview(game_background_);

    // UI background view
    ui_background_ = ShapeView::createRect(ci::app::getWindowHeight(), ci::app::getWindowWidth() / 4 );
    ui_background_->setFillColor(ci::Color(ci::Color::black()))
      .setSuperviewShouldIgnoreInBounds( true );
    ui_background_->setDrawBounds(true);
    ui_background_->setBoundsColor(ci::Color(ci::Color::white()));
    ui_background_->setPosition(0, 3 * ci::app::getWindowHeight() / 4);
  }

  void MainViewController::SetUpUI() {
    health_ = ImageView::create(health_image_);
    health_->setScale(3);
    health_->setPosition(ci::app::getWindowWidth() / 8,
      7 * ci::app::getWindowHeight() / 8 - health_->getScaledHeight() / 2);

    shield_ = ImageView::create(shield_image_);
    shield_->setScale(3);
    shield_->setPosition(5 * ci::app::getWindowWidth() / 8,
                         7 * ci::app::getWindowHeight() / 8 - shield_->getScaledHeight() / 2);
  }

  void MainViewController::SetUpShip() {
    // Load image asset into texture
    ship_image_ = ci::gl::Texture::create(ci::loadImage(
      ci::app::loadAsset("ship.png")));
    ship_image_->setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);

    Ship ship = game_engine_.GetShip();
    ship_shape_ = ImageView::create(ship_image_);
    ship_shape_->setPosition(ship.GetPosition().first, ship.GetPosition().second);
    game_view_->addSubview(ship_shape_);
  }

  void MainViewController::SetUpScoreText() {
    // Set up score text view
    score_text_.size(200, ci::TextBox::GROW)
      .color(ci::Color(1, 1, 1))
      .alignment(ci::TextBox::Alignment::LEFT)
      .font(ci::Font( "Arial", kTextFontSize));

    // Set the score text, add textbox to view
    score_text_.setText(GetScoreText());
    score_text_box_ = TextView::create();
    score_text_box_->setPosition(0, 0)
    .setSuperviewShouldIgnoreInBounds( true );
    score_text_box_->setCiTextBox(score_text_);
  }
}
