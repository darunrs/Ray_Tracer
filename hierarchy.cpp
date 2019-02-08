#include <algorithm>
#include "hierarchy.h"

// Reorder the entries vector so that adjacent entries tend to be nearby.
// You may want to implement box.cpp first.
void Hierarchy::Reorder_Entries()
{
    if(!entries.size()) return;
    // TODO;
    //Find the element closest to the origin
    double minDist = 99999999999.0;
    int index = 0;
    for (size_t i = 0; i < entries.size(); i++) {
    	vec3 point = entries[i].hi - entries[i].lo;
    	double dist = point.magnitude();
    	if (dist < minDist) {
    		minDist = dist;
    		index = i;
    	}
    }
    Entry temp = entries[0];
    entries[0] = entries[index];
    entries[index] = temp;

    //Perform ordering
    for (size_t i = 0; i < entries.size(); i++) {
	    for (size_t j = i + 1; j < entries.size(); j++) {
	    	vec3 point = (entries[i].hi - entries[i].lo) - (entries[j].hi - entries[j].lo);
	    	double dist = point.magnitude();
	    	if (dist < minDist) {
	    		minDist = dist;
	    		index = i;
	    	}
	    }
	    Entry temp = entries[i];
	    entries[i] = entries[index];
	    entries[index] = temp;
	    minDist = 99999999999.0;
    	index = 0;
    }
}

// Populate tree from entries.
void Hierarchy::Build_Tree()
{
    if(!entries.size()) return;
    // TODO;
    //Get number of parents for leaf level
    int parents = 1;
    while(parents < entries.size()) {
    	parents *= 2;
    }
    parents = parents / 2;

    //Fill vector with leaf elements
    for (int i = 0; i < entries.size(); i++) {
    	tree.push_back(entries[i].box);
    }

    //Construct tree
    while(parents != 0) {
	    for (int i = parents; i > 0; i--) {
	    	if ((2 * i) <= tree.size()) {
	    		Box b = tree[(2*i) - 1];
	    		b.Union(tree[(2*i) - 2]);
	    		tree.push_front(b);
	    	} else {
	    		if (((2 * i) - 1) == tree.size()) {
	    			tree.push_front(tree[tree.size()-1]);
	    		} else {
	    			Box b;
		    		b.lo = {-99999, -99999, -99999};
		    		b.hi = {-99999, -99999, -99999}
		    		tree.push_front(b);
	    		}
	    	}
	    }
    	parents = parents / 2;
    }
}

// Return a list of candidates (indices into the entries list) whose
// bounding boxes intersect the ray.
void Hierarchy::Intersection_Candidates(const Ray& ray, std::vector<int>& candidates) const
{
    // TODO;
    int i = 0;
    while(i < (tree.size() - entries.size())) {
		if (tree[(2*i) + 1].Intersection(ray)) {
			i = (2*i) + 1;
		} else if (tree[(2*i) + 2].Intersection(ray)) { //If ray intersects right child
    		i = (2*i) + 2;
    	} else {
    		candidates.clear();
    		return;
    	}
    }
    i = (tree.size() - i) - 1;
    candidates = {i};
    return;
}

/*
// TODO;
    int i = 0;
    int end = 2;
    while(i < (tree.size() - entries.size())) {
    	bool one = true;
    	for (int j = 1; j <= end) {
    		if (tree[(2*i) + j].Intersection(ray)) {
    			if (one) {
    				i = (2*i) + j;
    			} else {
    				end * 2;
    			}
    		}
    	}
    	 else if (tree[(2*i) + 2].Intersection(ray)) { //If ray intersects right child
    		i = (2*i) + 1;
    	} else {
    		return;
    	}
    }
*/