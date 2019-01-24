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
    color = color_ambient * world.ambient_color * world.ambient_intensity;
    vec3 lightDir;

    for(unsigned i = 0; i < world.lights.size(); i++) {
    	//Compute light direction
    	lightDir = (world.lights[i]->position - intersection_point); //Points from object to light
    	double lightDist = lightDir.magnitude();

    	//Check if object is in shadow
    	if(world.enable_shadows) {
    		Ray shadowRay;
    		shadowRay.direction = lightDir.normalized();
    		shadowRay.endpoint = intersection_point;
    		Hit shadowCheck = world.Closest_Intersection(shadowRay);
    		if ((shadowCheck.dist * shadowRay.direction).magnitude() <= (lightDist + 0.01)) { //If there is an object in the way
    			continue; //Don't add diffuse and specular
    		}
    	}

    	//Calculate diffuse 
    	double angle = std::max(dot(normal, lightDir.normalized()), 0.0);
        vec3 lightColor = world.lights[i]->Emitted_Light(lightDir);
    	color += (color_diffuse * lightColor * angle);

    	//Calculate specular
    	vec3 reflection = lightDir - (2 * dot(lightDir.normalized(), normal) * normal); //Calculate reflection vector
    	angle = std::max(dot(ray.direction, reflection.normalized()), 0.0);
    	color += (color_specular * lightColor * pow(angle, specular_power));
    }
    return color;
}
