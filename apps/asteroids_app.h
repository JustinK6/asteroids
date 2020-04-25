// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <poScene/Scene.h>
#include <asteroids/GameViewController.h>

using namespace ci;
using namespace ci::app;
using namespace po::scene;

namespace asteroidsapp {

class AsteroidsApp : public cinder::app::App {
 public:
  AsteroidsApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

  po::scene::SceneRef mScene;
  asteroids::GameViewControllerRef mViewController;
};

}  // namespace asteroidsapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
