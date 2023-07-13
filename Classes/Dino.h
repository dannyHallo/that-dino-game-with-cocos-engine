#pragma once

#ifndef CC_DLL
#define CC_DLL
#endif // !CC_DLL

#include "cocos2d.h"

class Dino {
  const cocos2d::Vec2 cScreenSize;
  const cocos2d::Vec2 cStartingPos;

  const float cJumpVelocity = 15.f;
  const float cTimeMul      = 100.f;

  const float cJumpGravityPressed   = -0.6f;
  const float cJumpGravityUnpressed = -1.f;
  const float cJumpGravityCrouched  = -1.5f;
  float mJumpGravity                = cJumpGravityUnpressed;

  cocos2d::LayerColor *const mBackground;
  cocos2d::Vector<cocos2d::SpriteFrame *> mRunningFrames; // const?
  cocos2d::Vector<cocos2d::SpriteFrame *> mCrouchingFrames;
  cocos2d::Sprite *mSprite = nullptr;

  cocos2d::Vec2 mPosition;
  cocos2d::Vec2 mVelocity = cocos2d::Vec2::ZERO;

  bool mIsJumping   = false;
  bool mIsCrouching = false;

public:
  enum Input { JUMP, CROUCH, CANCEL_JUMP, CANCEL_CROUCH, NONE };

  Dino(const cocos2d::Vec2 screenSize, cocos2d::Vector<cocos2d::SpriteFrame *> runningFrames,
       cocos2d::Vector<cocos2d::SpriteFrame *> crouchingFrames, cocos2d::LayerColor *background);

  ~Dino() = default;

  inline bool isJumping() const { return mIsJumping; }
  inline bool isCrouching() const { return mIsCrouching; }

  void handleInput(const Input wantTo);

  // recalc position of dino, draw dino on screen and check for collisions
  void update(const float dt);

private:
  void drawSprite();
  void recalculatePosition(float dt);
  bool checkCollision(cocos2d::Vector<cocos2d::AABB *>);
};