#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    //TODO; determine the color
    color = color_ambient * ambient_intensity;
    Ray lightRay;

    for(unsigned i = 0; i < world.lights.size(); i++) {
    	//Compute light direction
    	lightRay.direction = (world.lights[i].position - intersection_point).normalized(); //Points from object to light
    	double lightDist = lightRay.direction.magnitude();
    	lightRay.endpoint = world.lights[i].position;

    	//Check if object is in shadow
    	if(world.enable_shadows) {
    		ray ShadowRay;
    		shadowRay.direction = lightRay.direction;
    		shadowRay.endpoint = intersection_point;
    		Hit shadowCheck = Closest_Intersection(lightRay);
    		if ((shadowCheck.t * lightRay).magnitude() <= lightDist + 0.01) { //If there is an object in the way
    			continue; //Don't add diffuse and specular
    		}
    	}

    	//Calculate diffuse 
    	double angle = max(dot(normal, lightRay.direction), 0);
    	color += (color_diffuse * world.lights[i].Emitted_Light(lightRay.direction) * angle);

    	//Calculate specular
    	vec3 reflection = lightRay.direction - (2 * dot(lightRay.direction, normal) * normal); //Calculate reflection vector
    	angle = max(dot(ray, reflection), 0);
    	color += (color_specular * world.lights[i].Emitted_Light(lightRay.direction) * pow(angle, specular_power));
    }
    return color;
}
