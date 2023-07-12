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

#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

static cocos2d::Size screenResolutionSize = cocos2d::Size(2560, 1440);

// prepares the OpenGL context for rendering
void AppDelegate::initGLContextAttrs() {
  // set OpenGL context attributions,now can only set six attributions:
  // red,green,blue,alpha,depth,stencil
  GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
  GLView::setGLContextAttrs(glContextAttrs);
}

// get called when the program is ready to run
bool AppDelegate::applicationDidFinishLaunching() {
  initOpenGL();
  initDirector();
  initMultiResolution();
  createAndRunScene();
  return true;
}

// get called when application goes to background
void AppDelegate::applicationDidEnterBackground() { Director::getInstance()->stopAnimation(); }

// get called when application returns to foreground
void AppDelegate::applicationWillEnterForeground() { Director::getInstance()->startAnimation(); }

void AppDelegate::initMultiResolution() {
  auto director = Director::getInstance();
  auto glview   = director->getOpenGLView();

  glview->setDesignResolutionSize(screenResolutionSize.width, screenResolutionSize.height,
                                  ResolutionPolicy::FIXED_WIDTH);

  std::vector<std::string> searchPaths;
  float scaleFactor = 1.0f;
  Size frameSize    = glview->getFrameSize();

  searchPaths.push_back("res/HDR");

  director->setContentScaleFactor(scaleFactor);
  FileUtils::getInstance()->setSearchPaths(searchPaths);
}

void AppDelegate::initOpenGL() {
  auto director = Director::getInstance();
  auto glview   = director->getOpenGLView();

  // create a fullscreen window
  if (!glview) {
    glview = GLViewImpl::createWithFullScreen("Cocos2dx-SpriteSheetTutorial");
    director->setOpenGLView(glview);
  }
}

void AppDelegate::initDirector() {
  auto director = Director::getInstance();
  // fix the FPS value
  director->setAnimationInterval(1.0f / 60);
  // display FPS
  director->setDisplayStats(true);
}

void AppDelegate::createAndRunScene() {
  auto scene = HelloWorld::createScene();
  Director::getInstance()->runWithScene(scene);
}
