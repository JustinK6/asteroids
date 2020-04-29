// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "asteroids_app.h"

#include <cinder/app/App.h>


namespace asteroidsapp {

using cinder::app::KeyEvent;

AsteroidsApp::AsteroidsApp() { }

void AsteroidsApp::setup() {
  setWindowSize( 800, 600 );
  main_view_controller_	= asteroids::ViewController::create();
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

void AsteroidsApp::keyDown(KeyEvent event) { }

}  // namespace asteroidsapp
