#include "../include/Vector3.hpp"
#include <iostream>

void testCrossProduct() {
  Vector3 a = Vector3(1,0,0);
  Vector3 b = Vector3(0,1,0);
  std::cout << a.cross(b) << std::endl;
}

int main() {
  testCrossProduct();
}
