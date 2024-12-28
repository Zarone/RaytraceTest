#include "../include/Sphere.hpp"
#include <iostream>

Sphere::Sphere(float radius, Material* mat, Vector3* center): radius(radius), mat(mat), center(center) {}

bool Sphere::collissionCheck(Vector3 dir, Vector3 origin, float* hitTime) {
  // check discriminant
  Vector3 originMinusCenter = origin - *this->center;

  float discriminant = pow(dir.dotProduct(originMinusCenter), 2) 
     - (
    dir.magnitudeSquared() * (
      originMinusCenter.magnitudeSquared()-pow(this->radius, 2)
    )
  );
  if (discriminant < 0) return false;
  else {
    float sqrtDiscriminant = sqrt(discriminant);
    float tPos = (-(dir.dotProduct(originMinusCenter)) + sqrtDiscriminant)
      /dir.magnitudeSquared();
    float tNeg = (-(dir.dotProduct(originMinusCenter)) - sqrtDiscriminant)
      /dir.magnitudeSquared();


    if (tPos < 0) return false;
    else if (tNeg < 0) {
      *hitTime = tPos;
      return true;
    } else {
      *hitTime = tNeg;
      return true;
    }

  }

}
