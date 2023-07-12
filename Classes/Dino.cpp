#include "Dino.h"

USING_NS_CC;

Dino::Dino(const cocos2d::Vec2 screenSize, cocos2d::Vector<cocos2d::SpriteFrame *> runningFrames,
           cocos2d::Vector<cocos2d::SpriteFrame *> crouchingFrames, cocos2d::LayerColor *background)
    : cScreenSize(screenSize), cStartingPos(screenSize.x / 6.f, screenSize.y / 3.f), mRunningFrames(runningFrames),
      mCrouchingFrames(crouchingFrames), mPosition(cStartingPos), mBackground(background) {
  // let the dino run forever
  mSprite = cocos2d::Sprite::createWithSpriteFrame(mRunningFrames.front());
  mSprite->setPosition(mPosition);
  mBackground->addChild(mSprite);
  auto animation =
      Animation::createWithSpriteFrames(mRunningFrames, 0.1f); // 0.1f is the delay (in seconds) between frames
  mSprite->runAction(RepeatForever::create(Animate::create(animation)));
}

void Dino::handleInput(const Input input) {
  switch (input) {
  case JUMP:
    if (!mIsJumping) {
      mVelocity    = Vec2(0, cJumpVelocity);
      mIsJumping   = true;
      mJumpGravity = cJumpGravityPressed;
    }
    break;
  case CANCEL_JUMP:
    mJumpGravity = cJumpGravityUnpressed;
    break;
  }
}

void Dino::update(float dt) {
  recalculatePosition(dt);
  drawSprite();
}

void Dino::recalculatePosition(float dt) {
  if (mIsJumping) {
    mVelocity += Vec2(0, mJumpGravity) * dt * cMul;
    mPosition += mVelocity * dt * cMul;
  }

  if (mPosition.y <= cStartingPos.y) {
    mPosition.y = cStartingPos.y;
    mVelocity   = Vec2::ZERO;
    mIsJumping  = false;
  }
}

void Dino::drawSprite() {
  auto movement = MoveTo::create(0.f, mPosition);
  mSprite->runAction(movement);
}