/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "Noise.h"

USING_NS_CC;

Scene *HelloWorld::createScene() {
  auto scene = Scene::create();
  auto layer = HelloWorld::create();
  scene->addChild(layer);
  return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in "
         "HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
  if (!Layer::init()) {
    return false;
  }

  // add listeners
  addKeyboardListeners();

  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("dinogame.plist");

  Vec2 origin      = Director::getInstance()->getVisibleOrigin();
  Vec2 visibleSize = Director::getInstance()->getVisibleSize();

  // create background
  Color4B backgroundColour = Color4B(100, 100, 100, 255);
  LayerColor *background   = LayerColor::create(backgroundColour, visibleSize.x, visibleSize.y);
  background->setPosition(origin);
  this->addChild(background);

  // create dino
  auto runningFrames   = getAnimation("rdino%01d.png", 2);
  auto crouchingFrames = getAnimation("cdino%01d.png", 2);
  auto plantFrames     = getAnimation("plant%01d.png", 6);
  auto bigPlantFrames  = getAnimation("bplant%01d.png", 3);
  auto groundSprite    = Sprite::create("ground.png");

  environment = std::make_unique<Environment>(visibleSize, plantFrames, bigPlantFrames, groundSprite, background);
  dino        = std::make_unique<Dino>(visibleSize, runningFrames, crouchingFrames, background);

  scheduleUpdate(); // this is required to call update() method every frame!
  return true;
}

void HelloWorld::update(float dt) {
  dino->update(dt);
  environment->update(dt);
}

void HelloWorld::menuCloseCallback(Ref *pSender) {
  // Close the cocos2d-x game scene and quit the application
  Director::getInstance()->end();
}

Vector<SpriteFrame *> HelloWorld::getAnimation(const char *format, int count) {
  auto spritecache = SpriteFrameCache::getInstance();
  Vector<SpriteFrame *> animFrames;
  char str[100];
  for (int i = 1; i <= count; i++) {
    sprintf(str, format, i);
    animFrames.pushBack(spritecache->getSpriteFrameByName(str));
  }
  return animFrames;
}

void HelloWorld::addKeyboardListeners() {
  // creating a keyboard event listener
  auto listener           = EventListenerKeyboard::create();
  listener->onKeyPressed  = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
  listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

  _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// Implementation of the keyboard event callback function prototype
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
  // press esc to quit
  if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
    Director::getInstance()->end();
  }

  // press space to jump
  if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
    dino->handleInput(Dino::Input::JUMP);
  }

  // press down arrow to crouch
  if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
    dino->handleInput(Dino::Input::CROUCH);
  }
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
  // release space to cancel jump
  if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
    dino->handleInput(Dino::Input::CANCEL_JUMP);
  }

  // release down arrow to cancel crouch
  if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
    dino->handleInput(Dino::Input::CANCEL_CROUCH);
  }
}