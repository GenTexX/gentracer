#include "sphere.h"
#include <cmath>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>

#include <sstream>
#include <iomanip>

Sphere::Sphere(const glm::vec3& position, float radius, const glm::vec3& color) 
    : m_Position(position), m_Radius(radius), m_Color(color)
{ 

}

Sphere::~Sphere() {

}

HitInfo Sphere::hit(const Ray& ray, Interval& ray_t) const {
    glm::vec3 oc = m_Position - ray.getOrigin();

    auto a = glm::dot(ray.getDirection(), ray.getDirection());
    auto b = -2.0f * glm::dot(ray.getDirection(), oc);
    auto c = glm::dot(oc, oc) - m_Radius * m_Radius;
    auto discriminant = b*b - 4.0f * a * c;

    HitInfo result{};
    result.hit = discriminant >= 0.0f;

    if (result.hit) {
        float t = (-b - std::sqrt(discriminant)) / (2.0f * a);
        result.hit = ray_t.surrounds(t);
        result.point = ray.at(t);
        result.t = t;
        result.normal = glm::normalize(result.point - m_Position);
        result.frontFace = glm::dot(ray.getDirection(), result.normal) < 0.0f;
        result.normal = result.frontFace ? result.normal : result.normal * -1.0f;
    }

    return result;
}

glm::vec3 Sphere::color(const Ray &ray, const HitInfo& hitInfo) const {
    if (!hitInfo.hit)
        return glm::vec3(0.0f);

    const glm::vec3& n = hitInfo.normal;
    return 0.5f * glm::vec3(n.x + 1.0f, n.y + 1.0f, n.z + 1.0f);
}

std::string Sphere::info() {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "Sphere(";
    ss << "position=(" << m_Position.x << ", " << m_Position.y << ", " << m_Position.z << "), ";
    ss << "radius=" << m_Radius << ", ";
    ss << "color=(" << m_Color.r << ", " << m_Color.g << ", " << m_Color.b << ")";
    ss << ")";
    return ss.str();
}
