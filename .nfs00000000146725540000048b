#include "plane.h"
#include "ray.h"
#include <cfloat>
#include <limits>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
Hit Plane::Intersection(const Ray& ray, int part) const
{
    // TODO
    if (dot(normal, ray.direction) == 0) { //Parallel or on top of plane
    	if (dot(normal, (ray.endpoint - x1)) == 0) {
    		return {0,0,0}; //On top of plane
    	}
    	return {0,0,0}; //Parallel to plane
    } else { //Intersects
    	Hit hit;
    	hit.object = this;
    	hit.part = part;
    	hit.dist = dot(normal, (x1 - ray.endpoint)) / dot(normal, ray.direction);
      if (hit.dist < 0) {
        return {0,0,0};
      }
    	return hit;
    }
    return {0,0,0};
}

vec3 Plane::Normal(const vec3& point, int part) const
{
    return normal;
}

// There is not a good answer for the bounding box of an infinite object.
// The safe thing to do is to return a box that contains everything.
Box Plane::Bounding_Box(int part) const
{
    Box b;
    b.hi.fill(std::numeric_limits<double>::max());
    b.lo=-b.hi;
    return b;
}
