// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "asteroids_app.h"

#include <cinder/app/App.h>


namespace asteroidsapp {

using cinder::app::KeyEvent;

AsteroidsApp::AsteroidsApp() { }

void AsteroidsApp::setup() {
  setWindowSize( 800, 600 );
  mViewController	= asteroids::GameViewController::create();
  mScene = po::scene::Scene::create( mViewController );
}

void AsteroidsApp::update() {
  mScene->update();
}

void AsteroidsApp::draw() {
  // clear out the window with black
  gl::clear( Color( 0.0, 0.0f, 0.0 ) );
  mScene->draw();
}

void AsteroidsApp::keyDown(KeyEvent event) { }

}  // namespace asteroidsapp
