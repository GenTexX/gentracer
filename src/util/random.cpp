#include "random.h"
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>

namespace gentracer {

    
   float rand() {
        // Returns a random real in [0,1).
        thread_local std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        thread_local std::mt19937 generator(std::random_device{}());

        return dist(generator);
    }

    float rand(float min, float max) {
        // Returns a random real in [min,max).
        return min + (max-min) * rand();
    }

    glm::vec3 randvec() {
        return glm::vec3(rand(), rand(), rand());
    }
    
    glm::vec3 randvec(float min, float max) {
        return glm::vec3(rand(min, max), rand(min, max), rand(min, max));
    }

    glm::vec3 randuvec() {
        while (true) {
            glm::vec3 vec = randvec(-1.0f, 1.0f);
            if (glm::dot(vec, vec) >= 1e-5f) {
                return glm::normalize(vec);
            }
        }
    }

    glm::vec3 randvechemi(const glm::vec3& normal) {
        glm::vec3 onUnitSphere = randuvec();
        if (glm::dot(onUnitSphere, normal) > 0.0)
            return onUnitSphere;
        else
            return -onUnitSphere;
    }
}
