#pragma once

#ifndef CC_DLL
#define CC_DLL
#endif // !CC_DLL

#include "cocos2d.h"

#include <deque>

class Environment {
  const cocos2d::Vec2 cScreenSize;
  std::deque<cocos2d::Sprite *> mObstructs;
  std::deque<cocos2d::Sprite *> mGrounds;
  cocos2d::LayerColor *const mBackground;

  cocos2d::SpriteFrame *mGroundSpriteFrame;
  const cocos2d::Vector<cocos2d::SpriteFrame *> mPlantFrames;
  const cocos2d::Vector<cocos2d::SpriteFrame *> mBigPlantFrames;

  cocos2d::Sprite *mSprite;

  const float cMinimumObstructGenDistanceRatio = 0.2f;
  const float cGenerationThreshold             = 0.982f;
  float mDinoMoveSpeed                         = 7.f;
  const float cTimeMul                         = 100.f;

public:
  Environment(const cocos2d::Vec2 screenSize, cocos2d::Vector<cocos2d::SpriteFrame *> plantFrames,
              cocos2d::Vector<cocos2d::SpriteFrame *> bigPlantFrames, cocos2d::Sprite *groundSprite,
              cocos2d::LayerColor *background);

  ~Environment() = default;

  void update(const float dt);

private:
  void manageObstacles(const float dt);
  void manageGround();
  void recalculatePosition(float dt);
  void addObstruct(const float randomFac);
};
