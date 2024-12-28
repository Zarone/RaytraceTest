#include "../include/Vector3.hpp"

Vector3 Vector3::cross (const Vector3& vec) {
  return Vector3(
    this->y*vec.z - this->z*vec.y, 
    vec.x*this->z - this->x*vec.z, 
    this->x*vec.y - this->y*vec.x
  );
}

Vector3 Vector3::divide_by(float num) {
  return Vector3(this->x/num, this->y/num, this->z/num);
}

float Vector3::magnitude() {
  return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

float Vector3::magnitudeSquared() {
  return pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2);
}

float Vector3::dotProduct(const Vector3& vec) {
  return this->x * vec.x + this->y * vec.y + this->z * vec.z;
}

Vector3 Vector3::multiply_by(float num) {
  return Vector3(this->x*num, this->y*num, this->z*num);
}

Vector3 Vector3::add(const Vector3& vec) {
  return Vector3(this->x+vec.x, this->y+vec.y, this->z+vec.z);
}

