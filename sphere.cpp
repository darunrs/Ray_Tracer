#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    // TODO
    vec3 v = ray.endpoint - center;
    float a = dot(ray.direction, ray.direction);
    float b = 2 * dot(ray.direction, v);
    float c = dot(v, v) - (radius * radius);

    float d = (b*b) - (4 * a * c);

    if (d < 0) { //No intersections
    	return {0,0,0};
    } 

    float t1 = (-b - sqrt(d)) / (2 * a); //First t (t upon entry) except when d = 0
    float t2 = (-b + sqrt(d)) / (2 * a); //Second t (t upon exit) except when d = 0

    if (t1 < 0) {
        if (t2 > 0) {
            t1 = t2;
        } else {
            return {0,0,0};
        }
    }

    Hit hit;
    if (d > 0) { //Two intersections, one entry, one exit
    	hit.object = this;
    	hit.dist = t1;
    	hit.part = part;
    	return hit;
    } else if (d == 0) { // One intersection, no entry
    	hit.object = this;
    	hit.dist = t1;
    	hit.part = part;
    	return hit;
    }

    return {0,0,0};
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    //TODO; compute the normal direction
    normal = center - point;
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
