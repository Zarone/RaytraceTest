#include "../include/Scene.hpp"
#include "../include/Light.hpp"
#include "../include/Object.hpp"
#include <vector>

Scene::Scene(int width, int height) : 
  cameraPosition(Vector3(0,0,0)), 
  lights(std::vector<Light>()),
  objects(std::vector<std::shared_ptr<Object> >()),
  width(width),
  height(height),
  up(Vector3(0,0,1)),
  l(-3),
  r(3),
  t(3),
  b(-3)
{
}

bool Scene::collissionCheckAll(
  const Vector3& rayDirection, 
  const Vector3& origin, 
  float* hitTime, 
  std::shared_ptr<Object>* hitObject
) {
  size_t length = this->objects.size();
  float minTime = MAXFLOAT;
  bool hit = false;

  for (size_t i = 0; i < length; ++i) {
    float time;
    if (this->objects.at(i)->collissionCheck(rayDirection, origin, &time)) {
      if (time < minTime) {
        hit = true;
        minTime = time;
        if (hitTime) *hitTime = time;
        if (hitObject) *hitObject = this->objects.at(i);
      }
    }
  }

  return hit;
}

void Scene::makeImage(uint8_t* pixels) {

  // math setup
  Vector3 basis_w = Vector3(1, 0, 0);

  Vector3 basis_u = up.cross(basis_w);
  basis_u = basis_u.divide_by(basis_u.magnitude());

  Vector3 basis_v = basis_w.cross(basis_u);

  Vector3 ww = basis_w.multiply_by(-focalLength);
  for (int i = 0; i < width*height*4; i+=4) {
    // pixel coordinates
    int x = (i/4)%width;
    int y = (i/4)/width;

    // coordinates on lens
    float u = l + (r-l)*(x+0.5)/width;
    float v = t + (b-t)*(y+0.5)/height;

    Vector3 uu = basis_u.multiply_by(u);
    Vector3 vv = basis_v.multiply_by(v);

    Vector3 rayDirection = ww.add(uu).add(vv);

    float hitTime;
    std::shared_ptr<Object> hitObject;
    bool collission = this->collissionCheckAll(rayDirection, cameraPosition, &hitTime, &hitObject);

    if (collission) {
      Vector3 hitPoint = (cameraPosition + rayDirection.multiply_by(hitTime));

      Vector3 n = hitObject->getNormal(hitPoint);

      // for each light
      for (size_t j = 0; j < this->lights.size(); ++j) {

        Light* thisLight = &this->lights.at(j);

        Vector3 l = thisLight->getPos() - hitPoint;
        l = l.divide_by(l.magnitude());

        Vector3 v = cameraPosition - hitPoint;
        v = v.divide_by(v.magnitude());

        Vector3 specH = v + l;
        specH = specH.divide_by(specH.magnitude());

        float magnitude = (
          hitObject->mat.diffuse * std::max(0.0f, n.dotProduct(l))
          + hitObject->mat.specular  * pow(std::max(0.0f, n.dotProduct(specH)), 100)
        );

        pixels[i] += (int) 100 * thisLight->getIntensity().x * magnitude;
        pixels[i+1] += (int) 100 * thisLight->getIntensity().y * magnitude;
        pixels[i+2] += (int) 100 * thisLight->getIntensity().z * magnitude;
      }

    }
  }
}

void Scene::setCamera(Vector3 vec, float focalLength) {
  this->cameraPosition = vec;
  this->focalLength = focalLength;
}

void Scene::addLight(Light light) {
  this->lights.push_back(light);
}

void Scene::addObject(std::shared_ptr<Object> obj) {
  this->objects.push_back(obj);
}

