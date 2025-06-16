#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>

class Ray {

    public:
        Ray(const glm::vec3& origin, const glm::vec3& direction);
        ~Ray();

        glm::vec3 at(float t) const;

        const glm::vec3& getOrigin() const;
        const glm::vec3& getDirection() const;

    private:
        glm::vec3 m_Origin;
        glm::vec3 m_Direction;


};
