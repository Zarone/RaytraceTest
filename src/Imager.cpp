#include "../include/Imager.hpp"
#include "../include/Material.hpp"
#include "../include/Sphere.hpp"
#include "../include/Light.hpp"
#include <algorithm>

void makeImage(uint8_t* pixels, int width, int height) {

  // make sphere
  Material mat1 = Material(1, 1, 1);
  Vector3 pos1 = Vector3(0, 0, 0);
  Sphere sphere1 = Sphere(10, &mat1, &pos1);

  // red light
  Vector3 lightPos = Vector3(50, 30, 30);
  Light light = Light(1, &lightPos);
  
  // blue light
  Vector3 lightPos2 = Vector3(0, -50, 0);
  Light light2 = Light(1, &lightPos2);

  // camera info
  Vector3 cameraPos = Vector3(100, 0, 0);

  // math setup
  Vector3 basis_w = Vector3(1, 0, 0);
  Vector3 up = Vector3(0, 0, 1);
  Vector3 basis_u = up.cross(basis_w);
  basis_u = basis_u.divide_by(basis_u.magnitude());
  Vector3 basis_v = basis_w.cross(basis_u);

  const int l = -3;
  const int r = -l;
  const int t = 3;
  const int b = -t;

  const float focus_length = 20;

  Vector3 ww = basis_w.multiply_by(-focus_length);
  for (int i = 0; i < width*height*4; i+=4) {
    int x = (i/4)%width;
    int y = (i/4)/width;
    float u = l + (r-l)*(x+0.5)/width;
    float v = t + (b-t)*(y+0.5)/height;

    Vector3 uu = basis_u.multiply_by(u);
    Vector3 vv = basis_v.multiply_by(v);

    Vector3 rayDirection = ww.add(uu).add(vv);
    float hitTime;
    bool collission = sphere1.collissionCheck(rayDirection, cameraPos, &hitTime);
    
    if (collission) {
      Vector3 hitPoint = (cameraPos + rayDirection.multiply_by(hitTime));
      Vector3 n = (hitPoint - *sphere1.center);
      n = n.divide_by(sphere1.radius);

      Vector3 l = lightPos - hitPoint;
      l = l.divide_by(l.magnitude());

      Vector3 l2 = lightPos2 - hitPoint;
      l2 = l2.divide_by(l2.magnitude());


      Vector3 v = cameraPos - hitPoint;
      v = v.divide_by(v.magnitude());

      Vector3 specH = v + l;
      specH = specH.divide_by(specH.magnitude());

      Vector3 specH2 = v + l2;
      specH2 = specH2.divide_by(specH2.magnitude());

      pixels[i] = (int) 40*sphere1.mat->diffuse * light.intensity * std::max(0.0f, n.dotProduct(l))
        + (int) 100 * sphere1.mat->specular * light.intensity * pow(std::max(0.0f, n.dotProduct(specH)), 100);
      pixels[i+2] = (int) 100*sphere1.mat->diffuse * light2.intensity * std::max(0.0f, n.dotProduct(l2))
        + (int) 100 * sphere1.mat->specular * light2.intensity * pow(std::max(0.0f, n.dotProduct(specH2)), 100);
    }
  }
}
