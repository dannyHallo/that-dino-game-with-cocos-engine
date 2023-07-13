#include "NumberDisplay.h"

USING_NS_CC;

NumberDisplay::NumberDisplay(const cocos2d::Vec2 screenSize, cocos2d::Vector<cocos2d::SpriteFrame *> numberFrames,
                             cocos2d::LayerColor *background)
    : cScreenSize(screenSize), mBackground(background), mNumberFrames(numberFrames),
      cDigitsCenter(cScreenSize.x / 2.f, cScreenSize.y * 5.f / 6.f),
      cDigitWidth(mNumberFrames.at(0)->getRect().size.width), cDigitHeight(mNumberFrames.at(0)->getRect().size.height) {
  for (int i = 0; i < cFixedDigitCount; i++) {
    auto sprite = cocos2d::Sprite::createWithSpriteFrame(mNumberFrames.at(0));
    sprite->setPosition(cDigitsCenter.x + cDigitWidth * (i - ((cFixedDigitCount - 1) / 2)), cDigitsCenter.y);
    mDigits.pushBack(sprite);
    mBackground->addChild(sprite, 3);
  }
}

void NumberDisplay::displayNumber(const int number) {
  const int usingDigitCount = std::to_string(number).length();

  for (int i = 0; i < cFixedDigitCount; i++) {
    Sprite *digit = mDigits.at(i);

    // use zero for unused digits
    if (cFixedDigitCount - i > usingDigitCount) {
      digit->setSpriteFrame(mNumberFrames.at(0));
    }
    // use the actual digit
    else {
      digit->setSpriteFrame(
          mNumberFrames.at(std::to_string(number).at(i - (cFixedDigitCount - usingDigitCount)) - '0'));
    }
  }
}