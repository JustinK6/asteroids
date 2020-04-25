// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include "asteroids_app.h"


using cinder::app::App;
using cinder::app::RendererGl;


namespace asteroidsapp {

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;

void SetUp(App::Settings* settings) {
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("My CS 126 Application");
}

}  // namespace asteroidsapp


// This is a macro that runs the application.
CINDER_APP(asteroidsapp::AsteroidsApp,
           RendererGl(RendererGl::Options().msaa(asteroidsapp::kSamples)),
           asteroidsapp::SetUp)
