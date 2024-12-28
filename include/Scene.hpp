#pragma once

#include "./Light.hpp"
#include "./Object.hpp"

class Scene
{
private:
  std::vector<Light> lights;
  std::vector<std::shared_ptr<Object> > objects;
  int width;
  int height;
public:
  Vector3 cameraPosition;
  int l;
  int r;
  int t;
  int b;
  Vector3 up;
  float focalLength;
  Scene(int width, int height);
  void setCamera(Vector3 vec, float focalLength);
  void addLight(Light light);
  void addObject(std::shared_ptr<Object> obj);
  void makeImage(uint8_t* pixels);
  bool collissionCheckAll(
    const Vector3& rayDirection, 
    const Vector3& origin, 
    float* hitTime, 
    std::shared_ptr<Object>* hitObject
  );
};
