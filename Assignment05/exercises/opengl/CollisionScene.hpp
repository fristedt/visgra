#ifndef COLLISIONSCENE_HPP_INCLUDE_ONCE
#define COLLISIONSCENE_HPP_INCLUDE_ONCE

#include "OpenGL.hpp"
#include <vector>
#include "Collision.hpp"

namespace ogl
{
class CollisionGeometry;
class CollisionScene
{
public:
  OPENGL_EXPORTS void addGeometry(std::shared_ptr<CollisionGeometry> geometry)
  {
    mGeometries.push_back(geometry);
  }

  /// Computes the closest intersection of a ray and any object in scene.
  OPENGL_EXPORTS bool
    closestIntersection(const Ray &ray, RayIntersection& intersection,
    float maxLambda = std::numeric_limits<float>::infinity()) const; 

private:
  std::vector<std::shared_ptr<CollisionGeometry>> mGeometries;
};
}

#endif //COLLISIONSCENE_HPP_INCLUDE_ONCE