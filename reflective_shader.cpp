#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    //TODO; determine the color

    //Determine reflection ray
    Ray reflection;
    reflection.endpoint = intersection_point;
    reflection.direction = ray.direction - (2 * dot(ray.direction, normal) * normal);

    //Set color
    vec3 refColor = world.Cast_Ray(reflection, recursion_depth + 1);
    vec3 currColor = shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);
    color = ((1 - reflectivity) * currColor) + (reflectivity * refColor);
    return color;
}
