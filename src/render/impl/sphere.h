#pragma once

#include "../scene_object.h"
#include <glm/ext/vector_float3.hpp>
#include <string>

class Sphere : public SceneObject {

    public:
        Sphere(const glm::vec3& position, float radius, const glm::vec3& color);
        virtual ~Sphere();

        HitInfo hit(const Ray &ray, Interval& ray_t) const override;
        glm::vec3 color(const Ray &ray, const HitInfo& hitInfo) const override;

        std::string info() override;

    private:
        glm::vec3 m_Position;
        float m_Radius;
        glm::vec3 m_Color;

};
