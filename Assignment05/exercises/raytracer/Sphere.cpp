#include "Sphere.hpp"
#include "Ray.hpp"
#include <memory>

namespace rt {

    bool Sphere::closestIntersectionModel(const Ray &ray, double maxLambda, RayIntersection& intersection) const {
        //Programming TASK 1: implement this method
        //Your code should compute the intersection between a ray and a unit sphere, with radius = 1, centered at origin (0,0,0);

        //If you detect an intersection, the return type should look similar to this:
        //if(rayIntersectsSphere)
        //{
        //  intersection = RayIntersection(ray,shared_from_this(),lambda,ray.pointOnRay(lambda),uvw);
        //  return true;
        //}
        const Vec3d& p_r = ray.origin();
        const Vec3d& t_r = ray.direction();

        double disc = pow(dot(t_r, p_r), 2) - (dot(p_r, p_r) - 1);
        if (disc < 0) {
            return false;
        }
        double leftTerm = -dot(t_r, p_r);
        double rightTerm = sqrt(disc);
        double lambda1 = leftTerm - rightTerm;
        double lambda2 = leftTerm + rightTerm;

        double lambda = lambda1 < 0 ? lambda2 : lambda1;

        // Only intersections in [0,1] range are valid.
        if (lambda<0.0 || lambda>maxLambda) {
            return false;
        }

        Vec3d nullVector(0, 0, 0);
        intersection = RayIntersection(ray, shared_from_this(), lambda, ray.pointOnRay(lambda), nullVector);
        return true;
        //}

        // Hints :
        // As explained in Lecture 7 - Raytracing
        // 1. Ray origin p_r : ray.origin()
        //    Ray direction t_r : ray.direction()
        // 2. Solving the quadratic equation results in two solutions if the discriminant is positive
        //    i.e. if t_r . p_r - (p_r . p_r - 1) > 0 (Since t_r is a unit vector t_r . t_r = |t_r|^2 = 1)
        // 3. Solving for lambda we have the values  lambda1 = -(t_r . p_r) - sqrt(t_r . p_r - (p_r . p_r - 1)) and
        //    lambda2 = -(t_r . p_r) + sqrt(t_r . p_r - (p_r . p_r - 1)) 
        // 4. If lambda1 < 0, then the intersection lies inside the sphere. choose lambda2.
        // 5. lambda must be less than maxLambda, otherwise return false
        // 6. compute intersection point using ray.pointOnRay(lambda)
    }

    BoundingBox Sphere::computeBoundingBox() const {
        BoundingBox box;
        box.setMin(Vec3d(-1, -1, -1));
        box.setMax(Vec3d(1, 1, 1));
        return box;
    }

} //namespace rt
