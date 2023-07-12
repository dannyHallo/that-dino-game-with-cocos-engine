#include "Obstructs.h"
#include "Noise.h"

USING_NS_CC;

Obstructs::Obstructs(const cocos2d::Vec2 screenSize, cocos2d::Vector<cocos2d::SpriteFrame *> plantFrames,
                     cocos2d::Vector<cocos2d::SpriteFrame *> bigPlantFrames, cocos2d::LayerColor *background)
    : cScreenSize(screenSize), mPlantFrames(plantFrames), mBigPlantFrames(bigPlantFrames), mBackground(background) {}

void Obstructs::update(const float dt) {
  // TODO: make it more random
  static long long accumN = 0;
  accumN += static_cast<long long>(dt * 8275077);
  accumN %= 3333;

  Vec2 noise = Noise::ldsNoise2d(accumN);

  if (noise.x > cGenerationThreshold) {
    addObstruct(noise.y);
  }

  recalculatePosition(dt);
}

void Obstructs::recalculatePosition(float dt) {
  for (auto &obstruct : mObstructs) {
    obstruct->setPosition(obstruct->getPosition() - Vec2(mDinoMoveSpeed, 0) * dt * cTimeMul);
  }

  if (mObstructs.size() != 0 && mObstructs[0]->getPosition().x < 0) {
    mObstructs[0]->removeFromParent();
    mObstructs.pop_front();
  }
}

void Obstructs::addObstruct(const float randomFac) {
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
