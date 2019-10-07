#include "geometry.h"


vec3 geometry::calculateNormal(const vec3 &p1, const vec3 &p2, const vec3 &p3) {
	vec3 v1 = p2 - p1;
	vec3 v2 = p3 - p1;
	return normalize(cross(v1, v2));
}
