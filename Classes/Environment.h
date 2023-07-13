#pragma once

#ifndef CC_DLL
#define CC_DLL
#endif // !CC_DLL

#include "cocos2d.h"

#include <deque>

class Environment {
  const cocos2d::Vec2 cScreenSize;
  std::deque<cocos2d::Sprite *> mPlants;
  std::deque<cocos2d::Sprite *> mBirds;
  std::deque<cocos2d::Sprite *> mGrounds;
  cocos2d::LayerColor *const mBackground;

  cocos2d::SpriteFrame *mGroundSpriteFrame;
  const cocos2d::Vector<cocos2d::SpriteFrame *> mPlantFrames;
  const cocos2d::Vector<cocos2d::SpriteFrame *> mBigPlantFrames;
  const cocos2d::Vector<cocos2d::SpriteFrame *> mBirdFrames;

  const float cPlantMinimumObstructGenDistanceRatio = 0.2f;
  const float cBirdMinimumObstructGenDistanceRatio  = 0.4f;
  const float cPlantGenerationThrehold              = 0.982f;
  const float cBirdGenerationThrehold               = 0.992f;
  float mDinoMoveSpeed                              = 7.f;
  const float cBirdSpeedMul                         = 1.5f;
  const float cTimeMul                              = 100.f;

  bool mIsDead = false;

public:
  enum ObstructType { PLANT, BIRD };

  Environment(const cocos2d::Vec2 screenSize, cocos2d::Vector<cocos2d::SpriteFrame *> plantFrames,
              cocos2d::Vector<cocos2d::SpriteFrame *> bigPlantFrames,
              cocos2d::Vector<cocos2d::SpriteFrame *> birdFrames, cocos2d::Sprite *groundSprite,
              cocos2d::LayerColor *background);

  ~Environment() = default;

  bool update(const float dt, const cocos2d::Rect dinoRect);

private:
  bool isGameOver() const { return mIsDead; }
  void manageObstacles(const float dt);
  void manageGround();
  void recalculatePosition(float dt);
  void addObstruct(const float randomFac, const ObstructType type);
  void checkCollision(const cocos2d::Rect dinoRect);
};
