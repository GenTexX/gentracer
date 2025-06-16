#pragma once


#include <glm/ext/vector_float3.hpp>
#include <random>

namespace gentracer {

    // Returns a random float in the range [0, 1).
    float rand(); 

    // Returns a random float in the range [min, max).
    float rand(float min, float max); 

    // Returns a random 3D vector where each component is in [0, 1).
    glm::vec3 randvec();

    // Returns a random 3D vector where each component is in [min, max).
    glm::vec3 randvec(float min, float max);

    // Returns a random unit vector (direction) uniformly distributed over the unit sphere.
    // This is useful for sampling random directions in all directions (e.g. diffuse reflection).
    glm::vec3 randuvec();

    // Returns a random unit vector within the hemisphere oriented around the given normal.
    // Ensures all sampled directions are on the same side of the surface.
    glm::vec3 randvechemi(const glm::vec3& normal);
}
