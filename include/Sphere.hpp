#pragma once

#include "Material.hpp"
#include "Object.hpp"
#include "Vector3.hpp"

class Sphere : public Object
{
public:
  float radius;
  Vector3 center;

  Sphere(float radius, Material mat, const Vector3& center);

  Sphere(const Sphere& other);

  bool collissionCheck(Vector3 dir, Vector3 origin, float* hitTime);
  Vector3 getNormal(Vector3 point);

  ~Sphere() {}
};
