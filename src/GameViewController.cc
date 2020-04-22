//
// Created by ORaNgCHiKeN on 4/21/2020.
//

#include "GameViewController.h"

using namespace po::scene;

namespace asteroids {
  GameViewControllerRef GameViewController::create()
  {
    return GameViewControllerRef( new GameViewController() );
  }


}
