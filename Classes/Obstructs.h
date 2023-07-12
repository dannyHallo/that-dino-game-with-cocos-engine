#pragma once

#ifndef CC_DLL
#define CC_DLL
#endif // !CC_DLL

#include "cocos2d.h"

#include <deque>

class Obstructs {
  const cocos2d::Vec2 cScreenSize;
  std::deque<cocos2d::Sprite *> mObstructs;
  cocos2d::LayerColor *const mBackground;
  const cocos2d::Vector<cocos2d::SpriteFrame *> mPlantFrames; 
  const cocos2d::Vector<cocos2d::SpriteFrame *> mBigPlantFrames;

  cocos2d::Sprite *mSprite;

  const float cGenerationThreshold = 0.982f;
  float mDinoMoveSpeed             = 7.f;
  const float cTimeMul             = 100.f;

public:
  Obstructs(const cocos2d::Vec2 screenSize, cocos2d::Vector<cocos2d::SpriteFrame *> plantFrames,
            cocos2d::Vector<cocos2d::SpriteFrame *> bigPlantFrames, cocos2d::LayerColor *background);

  ~Obstructs() = default;

  void update(const float dt);

private:
  void recalculatePosition(float dt);
  void addObstruct(const float randomFac);
};
