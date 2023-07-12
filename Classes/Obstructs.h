#pragma once

#ifndef CC_DLL
#define CC_DLL
#endif // !CC_DLL

#include "cocos2d.h"

class Obstructs {
  const cocos2d::Vec2 cScreenSize;
  cocos2d::Vector<cocos2d::Sprite *> mObstructs;

public:
  Obstructs(const cocos2d::Vec2 screenSize, cocos2d::LayerColor *background);

  ~Obstructs() = default;

  void update(float dt);

  void addObstruct();

  void removeObstruct();

  void removeAllObstructs();

  inline cocos2d::Vector<cocos2d::Sprite *> getObstructs() const { return mObstructs; }

  
};
