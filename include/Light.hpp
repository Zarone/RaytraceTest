#pragma once

#include "Vector3.hpp"

class Light 
{
private:
  Vector3* pos;
public:
  float intensity;
  Light(float intensity, Vector3* pos): intensity(intensity), pos(pos) {};
};
