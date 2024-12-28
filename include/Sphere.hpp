#pragma once

#include "Material.hpp"
#include "Vector3.hpp"

class Sphere
{
public:
  float radius;
  Material* mat;
  Vector3* center;
  Sphere(float radius, Material* mat, Vector3* center);
  bool collissionCheck(Vector3 dir, Vector3 origin, float* hitTime);
};
