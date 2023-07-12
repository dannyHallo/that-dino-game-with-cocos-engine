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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#ifndef CC_DLL
#define CC_DLL
#endif // !CC_DLL

#include "Dino.h"
#include "cocos2d.h"

#include <memory>

class HelloWorld : public cocos2d::Layer {
  std::unique_ptr<Dino> dino;

public:
  HelloWorld() {}
  ~HelloWorld() = default;

  // factory method
  static cocos2d::Scene *createScene();

  // initializes the HelloWorld scene, creates game objects and animations
  virtual bool init();
  virtual void update(float dt) override;

  // a selector callback
  void menuCloseCallback(cocos2d::Ref *pSender);

  // CREATE_FUNC is a macro that creates a static method HelloWorld::create(). This method creates a new HelloWorld
  // object, initialises the memory management and calls init().
  CREATE_FUNC(HelloWorld);

private:
  // cocos2d::Vector has the limitation that the objects added to it must have cocos2d::Ref as a base class, it helps to
  // manage memory
  cocos2d::Vector<cocos2d::SpriteFrame *> getAnimation(const char *format, int count);

  void addKeyboardListeners();
  void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
  void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
};

#endif // __HELLOWORLD_SCENE_H__
