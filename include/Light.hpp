#pragma once

#include "Vector3.hpp"

class Light 
{
private:
  Vector3 intensity;
  Vector3 pos;
public:
  Light(Vector3 intensity, Vector3 pos): intensity(intensity), pos(pos) {};
  Vector3 getPos() { return pos; }
  Vector3 getIntensity() { return intensity; }
};
