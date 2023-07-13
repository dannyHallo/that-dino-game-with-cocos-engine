#include "Environment.h"
#include "Noise.h"

USING_NS_CC;

Environment::Environment(const cocos2d::Vec2 screenSize, cocos2d::Vector<cocos2d::SpriteFrame *> plantFrames,
                         cocos2d::Vector<cocos2d::SpriteFrame *> bigPlantFrames, cocos2d::Sprite *groundSprite,
                         cocos2d::LayerColor *background)
    : cScreenSize(screenSize), mPlantFrames(plantFrames), mBigPlantFrames(bigPlantFrames),
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
    mBackground->addChild(sprite);
  }
}

void Environment::update(const float dt) {
  recalculatePosition(dt);

  manageGround();
  manageObstacles(dt);
}

void Environment::manageGround() {
  if (mGrounds.empty()) return; // impossible condition

  if (mGrounds.back()->getPosition().x <= cScreenSize.x - mGroundSpriteFrame->getOriginalSizeInPixels().width) {
    Sprite *sprite = Sprite::createWithSpriteFrame(mGroundSpriteFrame);

    sprite->setAnchorPoint(Vec2(0, 0));
    sprite->setPosition(cScreenSize.x, cScreenSize.y / 3.f);

    mBackground->addChild(sprite);
    mGrounds.push_back(sprite);

    log("added ground");
  }

  if (mGrounds.front()->getPosition().x < -mGroundSpriteFrame->getOriginalSizeInPixels().width) {
    mGrounds.front()->removeFromParent();
    mGrounds.pop_front();
    log("removed ground");
  }
}

void Environment::manageObstacles(const float dt) {
  // dt is used as a seed for the noise only
  static long long accumN = 0;
  accumN += static_cast<long long>(dt * 8275077);
  accumN %= 3333;

  Vec2 noise = Noise::ldsNoise2d(accumN);

  if (noise.x > cGenerationThreshold) {
    // check its distance to the last one
    if (mObstructs.size() != 0) {
      const auto &lastObstruct = mObstructs.back();
      float minimumDistance    = cScreenSize.x * cMinimumObstructGenDistanceRatio;
      if (lastObstruct->getPosition().x < cScreenSize.x - minimumDistance) {
        addObstruct(noise.y);
      }
    }
    // add it directly
    else {
      addObstruct(noise.y);
    }
  }

  if (mObstructs.empty()) return;

  if (mObstructs.front()->getPosition().x < 0) {
    mObstructs.front()->removeFromParent();
    mObstructs.pop_front();
  }
}

void Environment::recalculatePosition(float dt) {
  for (auto &obstruct : mObstructs) {
    obstruct->setPosition(obstruct->getPosition() - Vec2(mDinoMoveSpeed, 0) * dt * cTimeMul);
  }

  for (auto &ground : mGrounds) {
    ground->setPosition(ground->getPosition() - Vec2(mDinoMoveSpeed, 0) * dt * cTimeMul);
  }
}

void Environment::addObstruct(const float randomFac) {
  int selectionSize = mPlantFrames.size() + mBigPlantFrames.size();
  int selection     = std::floor(randomFac * selectionSize);

  if (selection == selectionSize) selection = selectionSize - 1;

  Sprite *sprite;

  if (selection < mPlantFrames.size())
    sprite = Sprite::createWithSpriteFrame(mPlantFrames.at(selection));
  else
    sprite = Sprite::createWithSpriteFrame(mBigPlantFrames.at(selection - mPlantFrames.size()));

  // the anchor is the bottom right corner
  sprite->setAnchorPoint(Vec2(1, 0));
  sprite->setPosition(cScreenSize.x + sprite->getContentSize().width, cScreenSize.y / 3.f);

  //   sprite->getTexture()->setAliasTexParameters();
  //   sprite->setScale(2.f);

  mBackground->addChild(sprite);
  mObstructs.push_back(sprite);
}
