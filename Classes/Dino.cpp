#include "Dino.h"

USING_NS_CC;

Dino::Dino(const cocos2d::Vec2 screenSize, cocos2d::Vector<cocos2d::SpriteFrame *> runningFrames,
           cocos2d::Vector<cocos2d::SpriteFrame *> crouchingFrames, cocos2d::SpriteFrame *deadFrame,
           cocos2d::LayerColor *background)
    : cScreenSize(screenSize), cStartingPos(screenSize.x / 6.f, screenSize.y / 3.f), mRunningFrames(runningFrames),
      mCrouchingFrames(crouchingFrames), mPosition(cStartingPos), mDeadFrame(deadFrame), mBackground(background) {
  // let the dino run forever
  mSprite = cocos2d::Sprite::createWithSpriteFrame(mRunningFrames.front());
  mSprite->setPosition(mPosition);
  mSprite->setAnchorPoint(Vec2(0.5f, 0.f));

  mBackground->addChild(mSprite, 3);
  auto animation =
      Animation::createWithSpriteFrames(mRunningFrames, 0.1f); // 0.1f is the delay (in seconds) between frames
  mSprite->runAction(RepeatForever::create(Animate::create(animation)));
}

void Dino::handleInput(const Input input) {
  switch (input) {
  case Dino::Input::JUMP:
    if (!mIsJumping) {
      mVelocity    = Vec2(0, cJumpVelocity);
      mIsJumping   = true;
      mJumpGravity = cJumpGravityPressed;
    }
    break;

  case Dino::Input::CANCEL_JUMP:
    mJumpGravity = cJumpGravityUnpressed;
    break;

  case Dino::Input::CROUCH:
    if (!mIsCrouching) {
      mIsCrouching = true;
      mSprite->stopAllActions();
      auto animation =
          Animation::createWithSpriteFrames(mCrouchingFrames, 0.1f); // 0.1f is the delay (in seconds) between frames
      mSprite->runAction(RepeatForever::create(Animate::create(animation)));
      mJumpGravity = cJumpGravityCrouched;
    }
    break;

  case Dino::Input::CANCEL_CROUCH:
    if (mIsCrouching) {
      mIsCrouching = false;
      mSprite->stopAllActions();
      auto animation =
          Animation::createWithSpriteFrames(mRunningFrames, 0.1f); // 0.1f is the delay (in seconds) between frames
      mSprite->runAction(RepeatForever::create(Animate::create(animation)));
      mJumpGravity = cJumpGravityUnpressed;
    }
    break;

  case Dino::Input::DEAD:
    mSprite->stopAllActions();
    mSprite->setSpriteFrame(mDeadFrame);
    break;
  }
}

void Dino::update(const float dt) {
  recalculatePosition(dt);
  drawSprite();
}

void Dino::recalculatePosition(float dt) {
  if (mIsJumping) {
    mVelocity += Vec2(0, mJumpGravity) * dt * cTimeMul;
    mPosition += mVelocity * dt * cTimeMul;
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
