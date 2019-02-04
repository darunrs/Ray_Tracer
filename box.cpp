#include <limits>
#include "box.h"

// Return whether the ray intersects this box.
bool Box::Intersection(const Ray& ray) const
{
    // TODO;
    ivec2 comp1, comp2;
    vec3 invdir = 1 / ray.direction; //To prevent issues with dividing by 0
    
    double txlo = (lo[0] - ray.endpoint[0]) * invdir;
    double txhi = (hi[0] - ray.endpoint[0]) * invdir;
    comp1 = {txlo, txhi};
    if (txlo > txhi) {
    	comp1 = {txhi, txlo};
    } 

    double tylo = (lo[1] - ray.endpoint[1]) * invdir;
    double tyhi = (hi[1] - ray.endpoint[1]) * invdir;
    comp2 = {tylo, tyhi};
    if (tylo > tyhi) {
    	comp2 = {tyhi, tylo};
    }

    if (comp1[0] > comp2[1] || comp1[1] < comp2[0]) {
    	return false;
    }
    comp1[0] = std::max(comp1[0], comp2[0]);
    comp1[1] = std::min(comp1[1], comp2[1]);

    double tzlo = (lo[2] - ray.endpoint[2]) * invdir;
    double tzhi = (hi[2] - ray.endpoint[2]) * invdir;
    comp2 = {tzlo, tzhi};
	if (tzlo > tzhi) {
    	comp2 = {tzhi, tzlo};
    }

    if (comp1[0] > comp2[1] || comp1[1] < comp2[0]) {
    	return false;
    }
    return true;
}

// Compute the smallest box that contains both *this and bb.
Box Box::Union(const Box& bb) const
{
    Box box;
    TODO;
    return box;
}

// Enlarge this box (if necessary) so that pt also lies inside it.
void Box::Include_Point(const vec3& pt)
{
    TODO;
}

// Create a box to which points can be correctly added using Include_Point.
void Box::Make_Empty()
{
    lo.fill(std::numeric_limits<double>::infinity());
    hi=-lo;
}
