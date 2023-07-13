#pragma once

#ifndef CC_DLL
#define CC_DLL
#endif // !CC_DLL

#include "cocos2d.h"

class NumberDisplay {
  const cocos2d::Vec2 cScreenSize;
  cocos2d::LayerColor *const mBackground;
  cocos2d::Vector<cocos2d::SpriteFrame *> mNumberFrames;
  cocos2d::Vector<cocos2d::Sprite *> mDigits;

  const int cFixedDigitCount = 5;
  const cocos2d::Vec2 cDigitsCenter;
  const float cDigitWidth, cDigitHeight;

public:
  NumberDisplay(const cocos2d::Vec2 screenSize, cocos2d::Vector<cocos2d::SpriteFrame *> numberFrames,
                cocos2d::LayerColor *background);

  ~NumberDisplay() = default;

  void displayNumber(const int number);
};