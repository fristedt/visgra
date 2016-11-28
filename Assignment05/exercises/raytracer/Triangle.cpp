#include "Triangle.hpp"
#include "Ray.hpp"
#include "Plane.hpp"
#include <memory>

namespace rt {
    Triangle::Triangle(const Vec3d &v0, const Vec3d &v1, const Vec3d &v2,
        const Vec3d &uvw0, const Vec3d &uvw1, const Vec3d &uvw2) {
        mVertices[0] = v0;
        mVertices[1] = v1;
        mVertices[2] = v2;
        mUVW[0] = uvw0;
        mUVW[1] = uvw1;
        mUVW[2] = uvw2;
    }

    bool
        Triangle::closestIntersectionModel(const Ray &ray, double maxLambda, RayIntersection& intersection) const {
        //Programming TASK 1: implement this method
        //Your code should compute the intersection between a ray and a triangle.

        //If you detect an intersection, the return type should look similar to this:
        //if(rayIntersectsTriangle)
        //{
        //  intersection = RayIntersection(ray,shared_from_this(),lambda,ray.normal,uvw);
        //  return true;
        //} 

      // Hints :
      // As explained in Lecture 7 - Raytracing
      // 1. Ray origin p_r : ray.origin()
      //    Ray direction t_r : ray.direction()
      // 2. For a triangle we have t1 = v1 - v0, t2 = v2 - v0, n = cross(t1, t2)
      // 3. First you need to check if the ray : p = p_r + lambda * t_r intersects the Plane : (p - v0).n = 0
      //    solve for lambda. Let this value be lambda'
      //    If lambda' is within [0, maxLambda] the ray intersects the plane
      // 4. If the ray does not intersect the plane, return false. Otherwise, you need to check if the 
      //    point p = p_r + lambda' * t_r (Use ray.pointOnRay(lambda') for this)
      //    lies within the triangle (v0, v1, v2). Using barycentric coordinates is one way of solving this.
        const Vec3d& p_r = ray.origin();
        const Vec3d& t_r = ray.direction();

        Vec3d t1 = mVertices[1] - mVertices[0];
        Vec3d t2 = mVertices[2] - mVertices[0];
        Vec3d n = cross(t1, t2);

        // Solve linear equation for lambda
        // see also http://en.wikipedia.org/wiki/Line-plane_intersection
        double a = dot(mVertices[0] - p_r, n);
        double d = dot(t_r, n);

        // No intersection if ray is (almost) parallel to plane
        if (fabs(d) < Math::safetyEps())
            return false;

        double lambdaPrime = a / d;
        if (lambdaPrime < 0.0 || lambdaPrime > maxLambda)
            return false;

        Vec3d p = ray.pointOnRay(lambdaPrime);

        // Barry's centric coordinates
        double denom = (mVertices[1].y() - mVertices[2].y()) * (mVertices[0].x() - mVertices[2].x()) + (mVertices[2].x() - mVertices[1].x()) * (mVertices[0].y() - mVertices[2].y());
        double b1 = ((mVertices[1].y() - mVertices[2].y()) * (p.x() - mVertices[2].x()) + (mVertices[2].x() - mVertices[1].x()) * (p.y() - mVertices[2].y()))
            / denom;
        double b2 = ((mVertices[2].y() - mVertices[0].y()) * (p.x() - mVertices[2].x()) + (mVertices[0].x() - mVertices[2].x()) * (p.y() - mVertices[2].y()))
            / denom;
        double b3 = 1 - b1 - b2;

        if (b1 < 0 || b2 < 0 || b3 < 0)
            return false;

        Vec3d nullVector(0, 0, 0);
        intersection = RayIntersection(ray, shared_from_this(), lambdaPrime, p, nullVector);
        return true;
    }

    BoundingBox Triangle::computeBoundingBox() const {
        BoundingBox bbox;
        bbox.expandByPoint(mVertices[0]);
        bbox.expandByPoint(mVertices[1]);
        bbox.expandByPoint(mVertices[2]);
        return bbox;
    }

} //namespace rt
