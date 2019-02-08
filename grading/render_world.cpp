#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
    Hit closest = {0,0,0};
    closest.dist = 9999999999999;
    //Hit hClosest = closest;
    //unsigned ind = -1;
    std::vector<int> c;
    hierarchy.Intersection_Candidates(ray, c);
    if (debug_pixel) {
        std::cout << "candidates: ";
        for (unsigned i = 0; i < c.size(); i++) {
            std::cout << c[i] << " ";
        }
        std::cout << std::endl;
        
        /*std::cout << "ray: " << ray.endpoint << std::endl;
        
        std::cout << "entry boxes: ";
        for (unsigned i = 0; i < hierarchy.entries.size(); i++) {
            std::cout << "entry " << i << ": " << hierarchy.entries[i].box.lo << ", hi: " << hierarchy.entries[i].box.hi << std::endl;
        }
        std::cout << std::endl;
        
        for (unsigned i = 0; i < hierarchy.tree.size(); i++) {
            std::cout << i << " lo: " << hierarchy.tree[i].lo << ", hi: " << hierarchy.tree[i].hi << std::endl;
            if (hierarchy.tree[i].Intersection(ray))
                std::cout << "box intersects" << std::endl;
        }*/
    }
    /*for (unsigned i = 0; i < objects.size(); i++) {
        Hit temp = objects[i]->Intersection(ray, -1);
        if (debug_pixel) {
    		    std::cout << "intersection with obj[" << i << "] part " << temp.part << "; dist = " << temp.dist << std::endl;
	      }
        if (temp.dist < closest.dist && temp.dist > small_t) {
            //ind = i;
            closest.object = objects[i];
            closest.part = temp.part;
            closest = temp;
        }
    }*/
    for (unsigned i = 0; i < c.size(); i++) {
        if (c[i] >= (int)hierarchy.entries.size())
            continue;
        Hit temp = hierarchy.entries[c[i]].obj->Intersection(ray, hierarchy.entries[c[i]].part);
        if (temp.dist < closest.dist && temp.dist > small_t) {
            //ind = c[i];
            closest = temp;
        }
    }
    /*if (debug_pixel) {
	    std::cout << "closest intersection: entries[" << ind << "]; part = " << closest.part << "; dist = " << closest.dist << std::endl;
         if (closest.object == hClosest.object) {
             std::cout << "same closest found" << std::endl;
         }
    }*/
    return closest;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    //TODO
    Ray ray;
    ray.endpoint = camera.position;
    ray.direction = (camera.World_Position(pixel_index) - camera.position).normalized();
    if (debug_pixel) {
        //std::cout << "debug pixel: " << pixel_index[0] << " " << pixel_index[1] << std::endl;
	//std::cout << "cast ray: end = ";
        /*for (int i = 0; i < 3; i++)
            std::cout << ray.endpoint[i] << " ";     
        std::cout << "; dir = ";
        for (int i = 0; i < 3; i++)
            std::cout << ray.direction[i] << " ";     
        std::cout << std::endl;*/
    }
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    // TODO

    if (recursion_depth > recursion_depth_limit) {
        vec3 none;
        return background_shader->Shade_Surface(ray, none, none, recursion_depth); //Return color
    }

    vec3 color;
    Hit hit;
    hit = Closest_Intersection(ray);
    if (hit.object) {
        vec3 intPt = ray.Point(hit.dist);
        if (debug_pixel) {
	    //std::cout << "call Shade_Surface with: location = " << intPt << "; normal = " << hit.object->Normal(intPt, hit.part) << std::endl;
        }
        color = hit.object->material_shader->Shade_Surface(ray, intPt, hit.object->Normal(intPt, hit.part), recursion_depth);
    } else {
        vec3 none;
        color = background_shader->Shade_Surface(ray, none, none, recursion_depth);
    }
    return color;
}

void Render_World::Initialize_Hierarchy()
{
    // TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.
    for (size_t i = 0; i < objects.size(); i++) {
        for (int j = 0; j < objects[i]->number_parts; j++) {
            Entry e;
            e.obj = objects[i];
            e.part = j;
            e.box = objects[i]->Bounding_Box(j);
            hierarchy.entries.push_back(e);
        }
    }
    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
