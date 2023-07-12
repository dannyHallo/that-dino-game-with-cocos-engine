#pragma once

#ifndef CC_DLL
#define CC_DLL
#endif // !CC_DLL

#include "cocos2d.h"

namespace Noise {
static const float invExp = 1 / exp2(24.);

static cocos2d::Vec2 ldsNoise2d(long long n) {
  cocos2d::Vec2 p = cocos2d::Vec2(12664746 * n, 9560334 * n) * invExp;
  float intPart, fracPart;
  fracPart = modff(p.x, &intPart);
  p.x      = fracPart;
  fracPart = modff(p.y, &intPart);
  p.y      = fracPart;
  return p;
}
} // namespace Noise