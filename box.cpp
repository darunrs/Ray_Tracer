#include <limits>
#include "box.h"

// Return whether the ray intersects this box.
bool Box::Intersection(const Ray& ray) const
{
    // TODO;
    double tmin, tmax;
    vec3 invdir;
    for (size_t i = 0; i < 3; i++) {
        invdir[i] = 1 / ray.direction[i]; //To prevent issues with dividing by 0
    }
    double txlo = (lo[0] - ray.endpoint[0]) * invdir[0];
    double txhi = (hi[0] - ray.endpoint[0]) * invdir[0];
    if (txlo > txhi) {
    	std::swap(txhi, txlo);
    } 

    double tylo = (lo[1] - ray.endpoint[1]) * invdir[1];
    double tyhi = (hi[1] - ray.endpoint[1]) * invdir[1];
    if (tylo > tyhi) {	
    	std::swap(tyhi, tylo);
    }

    if (txlo > tyhi || txhi < tylo) {
    	return false;
    }
    tmin = std::max(txlo, tylo);
    tmax = std::min(txhi, tyhi);

    double tzlo = (lo[2] - ray.endpoint[2]) * invdir[2];
    double tzhi = (hi[2] - ray.endpoint[2]) * invdir[2];
    if (tzlo > tzhi) {
    	std::swap(tzhi, tzlo);
    }

    if (tmin > tzhi || tmax < tzlo) {
    	return false;
    }
    return true;
}

// Compute the smallest box that contains both *this and bb.
Box Box::Union(const Box& bb) const
{
    Box box;
    // TODO;
    box.lo[0] = std::min(lo[0], bb.lo[0]);
    box.lo[1] = std::min(lo[1], bb.lo[1]);
    box.lo[2] = std::min(lo[2], bb.lo[2]);

    box.hi[0] = std::max(lo[0], bb.lo[0]);
    box.hi[1] = std::max(lo[1], bb.lo[1]);
    box.hi[2] = std::max(lo[2], bb.lo[2]);
    return box;
}

// Enlarge this box (if necessary) so that pt also lies inside it.
void Box::Include_Point(const vec3& pt)
{
    // TODO;
    if (pt[0] < lo[0]) {
    	lo[0] = pt[0];
    } 
    if (pt[0] > hi[0]) {
    	hi[0] = pt[0];
    }

    if (pt[1] < lo[1]) {
    	lo[1] = pt[1];
    } 
    if (pt[1] > hi[1]) {
    	hi[1] = pt[1];
    }

    if (pt[2] < lo[2]) {
    	lo[2] = pt[2];
    } 
    if (pt[2] > hi[2]) {
    	hi[2] = pt[2];
    }
}

// Create a box to which points can be correctly added using Include_Point.
void Box::Make_Empty()
{
    lo.fill(std::numeric_limits<double>::infinity());
    hi=-lo;
}
