#pragma once

#include <cmath>
#include <iostream>

class Vector3
{
private:
  float x;
  float y;
  float z;
public:
  Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

  Vector3 cross(const Vector3& vec);

  Vector3 divide_by(float num);

  Vector3 multiply_by(float num);

  Vector3 add(const Vector3& vec);

  float dotProduct(const Vector3& vec);

  float magnitude();

  float magnitudeSquared();

  friend std::ostream& operator<<(std::ostream& os, const Vector3& obj) {
    os << obj.x << ", " << obj.y << ", " << obj.z << std::endl;
    return os;
  }

  Vector3 operator+(const Vector3& vec) {
    return this->add(vec);
  }

  Vector3 operator-(const Vector3& vec) {
    return this->add(Vector3(-vec.x, -vec.y, -vec.z));
  }
};
