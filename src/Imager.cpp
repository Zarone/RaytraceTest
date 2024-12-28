#include "../include/Imager.hpp"
#include "../include/Material.hpp"
#include "../include/Sphere.hpp"
#include "../include/Light.hpp"

Scene myScene(int width, int height) {
  Scene newScene = Scene(width, height);

  // make sphere
  Material mat1 = Material(1, 1, 1);
  Vector3 pos1 = Vector3(0, 0, 0);
  Sphere sphere1 = Sphere(10, mat1, pos1);

  newScene.addObject(std::make_shared<Sphere>(sphere1));

  // red light
  Vector3 lightPos = Vector3(50, 30, 30);
  Vector3 intensity = Vector3(1, 0, 0);
  Light light = Light(intensity, lightPos);
  newScene.addLight(light);
  
  // blue light
  Vector3 lightPos2 = Vector3(0, -50, 0);
  Vector3 intensity2 = Vector3(0, 0, 1);
  Light light2 = Light(intensity2, lightPos2);
  newScene.addLight(light2);

  // camera info
  Vector3 cameraPos = Vector3(100, 0, 0);
  newScene.setCamera(cameraPos, 20);

  return newScene;
}
