#pragma once

#include "./Material.hpp"
#include "./Vector3.hpp"

class Object
{
public:
  Material mat;
  virtual bool collissionCheck(Vector3 dir, Vector3 origin, float* hitTime) = 0;
  virtual Vector3 getNormal(Vector3 point) = 0;
  Object(Material mat);
  virtual ~Object() = 0;
  friend std::ostream& operator<<(std::ostream& os, const Object& obj) {
    os << "Material: " << obj.mat << std::endl;
    return os;
  }
};
