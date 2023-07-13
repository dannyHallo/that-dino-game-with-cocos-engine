#pragma once

#ifndef CC_DLL
#define CC_DLL
#endif // !CC_DLL

#include "cocos2d.h"

namespace Noise {
static const float invExp = 1 / static_cast<float>(exp2(24.));

// outputs 2 values between 0 and 1
static cocos2d::Vec2 ldsNoise2d(long long n) {
  cocos2d::Vec2 p = cocos2d::Vec2(static_cast<float>(12664746 * n), static_cast<float>(9560334 * n)) * invExp;

  float intPart, fracPart;
  fracPart = modff(p.x, &intPart);
  p.x      = fracPart;
  fracPart = modff(p.y, &intPart);
  p.y      = fracPart;

  return p;
}
} // namespace Noise