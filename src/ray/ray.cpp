#include "ray.h"

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction) : m_Origin(origin), m_Direction(direction) { }

Ray::~Ray() {}

glm::vec3 Ray::at(float t) const {
    return m_Origin + t * m_Direction;
}

const glm::vec3& Ray::getOrigin() const {
    return m_Origin;
}

const glm::vec3& Ray::getDirection() const {
    return m_Direction;
}
