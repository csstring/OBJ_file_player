#pragma once
#include "Common.h"

struct MtlStruct
{
  float _Ns = 1;
  math::Vec3 _Ka = math::Vec3(0.0f);
  math::Vec3 _Kd = math::Vec3(0.0f);
  math::Vec3 _Ks = math::Vec3(0.0f);
  float _Ni = 1;
  float _d = 1;
  uint8 _illum = 2;
};
