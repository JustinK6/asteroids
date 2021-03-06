// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "asteroids_app.h"

#include <cinder/app/App.h>


namespace asteroidsapp {

using cinder::app::KeyEvent;

AsteroidsApp::AsteroidsApp() { }

void AsteroidsApp::setup() {
  main_view_controller_	= asteroids::MainViewController::create();
  main_scene_ = po::scene::Scene::create(main_view_controller_ );
}

void AsteroidsApp::update() {
  main_scene_->update();
}

void AsteroidsApp::draw() {
  // clear out the window with black
  gl::clear( Color( 0.0, 0.0f, 0.0 ) );
  main_scene_->draw();
}

}  // namespace asteroidsapp
