#include "Environment.h"
#include "Noise.h"

USING_NS_CC;

Environment::Environment(const cocos2d::Vec2 screenSize, cocos2d::Vector<cocos2d::SpriteFrame *> plantFrames,
                         cocos2d::Vector<cocos2d::SpriteFrame *> bigPlantFrames,
                         cocos2d::Vector<cocos2d::SpriteFrame *> birdFrames, cocos2d::Sprite *groundSprite,
                         cocos2d::LayerColor *background)
    : cScreenSize(screenSize), mPlantFrames(plantFrames), mBigPlantFrames(bigPlantFrames), mBirdFrames(birdFrames),
      mGroundSpriteFrame(groundSprite->getSpriteFrame()), mBackground(background) {
  // Texture2D::TexParams texRepeat{backend::SamplerFilter::NEAREST, backend::SamplerFilter::NEAREST,
  //                                backend::SamplerAddressMode::CLAMP_TO_EDGE, backend::SamplerAddressMode::REPEAT};
  // groundSprite->getTexture()->setTexParameters(texRepeat);

  for (float flooringXPos = 0; flooringXPos < cScreenSize.x;
       flooringXPos += mGroundSpriteFrame->getOriginalSizeInPixels().width) {
    Sprite *sprite = Sprite::createWithSpriteFrame(mGroundSpriteFrame);
    // the anchor is the bottom left corner
    sprite->setAnchorPoint(Vec2(0, 0));
    sprite->setPosition(flooringXPos, cScreenSize.y / 3.f);
    mGrounds.push_back(sprite);
    mBackground->addChild(sprite, 1);
  }
}

bool Environment::update(const float dt, const cocos2d::Rect dinoRect) {
  recalculatePosition(dt);

  manageGround();
  manageObstacles(dt);

  checkCollision(dinoRect);

  return isGameOver();
}

void Environment::checkCollision(const cocos2d::Rect dinoRect) {
  // make the collision rect smaller (20% from each side)
  Rect collisionRect{
      dinoRect.origin.x + dinoRect.size.width * 0.2f,
      dinoRect.origin.y + dinoRect.size.height * 0.2f,
      dinoRect.size.width * 0.6f,
      dinoRect.size.height * 0.6f,
  };
  for (auto &obstruct : mPlants) {
    if (obstruct->getBoundingBox().intersectsRect(collisionRect)) {
      mIsDead = true;
      return;
    }
  }

  for (auto &obstruct : mBirds) {
    if (obstruct->getBoundingBox().intersectsRect(collisionRect)) {
      mIsDead = true;
      return;
    }
  }
}

void Environment::manageGround() {
  if (mGrounds.empty()) return; // impossible condition

  if (mGrounds.back()->getPosition().x <= cScreenSize.x - mGroundSpriteFrame->getOriginalSizeInPixels().width) {
    Sprite *sprite = Sprite::createWithSpriteFrame(mGroundSpriteFrame);

    sprite->setAnchorPoint(Vec2(0, 0));
    sprite->setPosition(cScreenSize.x, cScreenSize.y / 3.f);

    mBackground->addChild(sprite, 1);
    mGrounds.push_back(sprite);
  }

  if (mGrounds.front()->getPosition().x < -mGroundSpriteFrame->getOriginalSizeInPixels().width) {
    mGrounds.front()->removeFromParent();
    mGrounds.pop_front();
  }
}

void Environment::manageObstacles(const float dt) {
  // dt is used as a seed for the noise only
  static long long accumN = 0;
  accumN += static_cast<long long>(dt * 8275077);
  accumN %= 3333;

  Vec2 noise = Noise::ldsNoise2d(accumN);

  if (noise.x > cPlantGenerationThrehold) {
    // check its distance to the last one
    if (mPlants.size() != 0) {
      const auto &lastObstruct = mPlants.back();
      float minimumDistance    = cScreenSize.x * cPlantMinimumObstructGenDistanceRatio;
      float distanceToLastBird = cScreenSize.x - lastObstruct->getPosition().x;
      if (distanceToLastBird > minimumDistance) {
        addObstruct(noise.y, ObstructType::PLANT);
      }
    }
    // add it directly
    else {
      addObstruct(noise.y, ObstructType::PLANT);
    }
  }

  if (noise.y > cBirdGenerationThrehold) {
    // check its distance to the last one
    if (mBirds.size() != 0) {
      const auto &lastObstruct = mBirds.back();
      float minimumDistance    = cScreenSize.x * cBirdMinimumObstructGenDistanceRatio;
      float distanceToLastBird = cScreenSize.x - lastObstruct->getPosition().x;
      if (distanceToLastBird > minimumDistance) {
        addObstruct(noise.x, ObstructType::BIRD);
      }
    }
    // add it directly
    else {
      addObstruct(noise.x, ObstructType::BIRD);
    }
  }

  if (!mPlants.empty()) {
    if (mPlants.front()->getPosition().x < 0) {
      mPlants.front()->removeFromParent();
      mPlants.pop_front();
    }
  }

  if (!mBirds.empty()) {
    if (mBirds.front()->getPosition().x < 0) {
      mBirds.front()->removeFromParent();
      mBirds.pop_front();
    }
  }
}

void Environment::recalculatePosition(float dt) {
  for (auto &obstruct : mPlants) {
    obstruct->setPosition(obstruct->getPosition() - Vec2(mDinoMoveSpeed, 0) * dt * cTimeMul);
  }

  for (auto &obstruct : mBirds) {
    obstruct->setPosition(obstruct->getPosition() - Vec2(mDinoMoveSpeed, 0) * dt * cTimeMul * cBirdSpeedMul);
  }

  for (auto &ground : mGrounds) {
    ground->setPosition(ground->getPosition() - Vec2(mDinoMoveSpeed, 0) * dt * cTimeMul);
  }
}

void Environment::addObstruct(const float randomFac, const ObstructType type) {
  int selectionSize;
  if (type == ObstructType::PLANT) {
    selectionSize = mPlantFrames.size() + mBigPlantFrames.size();
  } else {
    selectionSize = mBirdFrames.size();
  }
  assert(selectionSize != 0 && "selection size cannot be zero");

  int selection = std::floor(randomFac * selectionSize);
  if (selection == selectionSize) selection = selectionSize - 1;

  Sprite *sprite;

  if (type == ObstructType::PLANT) {
    if (selection < mPlantFrames.size())
      sprite = Sprite::createWithSpriteFrame(mPlantFrames.at(selection));
    else
      sprite = Sprite::createWithSpriteFrame(mBigPlantFrames.at(selection - mPlantFrames.size()));
  } else {
    sprite = Sprite::createWithSpriteFrame(mBirdFrames.front());
    auto animation =
        Animation::createWithSpriteFrames(mBirdFrames, 0.1f); // 0.1f is the delay (in seconds) between frames
    sprite->runAction(RepeatForever::create(Animate::create(animation)));
  }

  // the anchor is the bottom right corner
  sprite->setAnchorPoint(Vec2(1, 0));

  float yOffset = type == ObstructType::PLANT ? 0 : sprite->getContentSize().height * 0.8f;
  sprite->setPosition(cScreenSize.x + sprite->getContentSize().width, cScreenSize.y / 3.f + yOffset);

  //   sprite->getTexture()->setAliasTexParameters();
  //   sprite->setScale(2.f);

  mBackground->addChild(sprite, 2);

  if (type == ObstructType::PLANT)
    mPlants.push_back(sprite);
  else
    mBirds.push_back(sprite);
}
