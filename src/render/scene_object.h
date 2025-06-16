#pragma once

#include <glm/glm.hpp>
#include <string>

#include "../ray/ray.h"
#include "../util/interval.h"

struct HitInfo {
    bool hit = false;
    glm::vec3 point;
    float t;
    glm::vec3 normal;
    bool frontFace;
};

class SceneObject {

    public:
        virtual HitInfo hit(const Ray& ray, Interval& ray_t) const = 0;
        virtual glm::vec3 color(const Ray& ray, const HitInfo& hitInfo) const = 0;

        virtual std::string info() = 0;

    protected:
        SceneObject() {}
        virtual ~SceneObject() {}

    private:


};
