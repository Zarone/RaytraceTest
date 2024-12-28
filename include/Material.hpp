#pragma once

#include <iostream>

class Material
{
public:
  float diffuse;
  float specular;
  float ambient;
  Material(float diffuse, float specular, float ambient);
  friend std::ostream& operator<<(std::ostream& os, const Material& obj) {
    os << obj.diffuse << ", " << obj.specular << ", " << obj.ambient << std::endl;
    return os;
  }
};
