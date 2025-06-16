#include "scene.h"
#include "scene_object.h"

#include "../logger/logger.h"
#include <glm/ext/vector_float3.hpp>

#include "../util/random.h"

Scene::Scene() : m_Objects() {

}

Scene::~Scene() {

}

void Scene::add(std::shared_ptr<SceneObject> object) {
    m_Objects.push_back(object);
}

const std::vector<std::shared_ptr<SceneObject>>& Scene::getObjects() const {
    return m_Objects;
}


glm::vec3 Scene::cast(const Ray& ray, int depth) const {
    if (depth <= 0) {
        return glm::vec3(0.0f);
    }

    Interval interval(0.001f, std::numeric_limits<float>::infinity());  // skip self-intersection
    HitInfo closestHit;

    for (auto& so : m_Objects) {
        HitInfo hi = so->hit(ray, interval);
        if (hi.hit) {
            interval.max = hi.t;  // shrink interval
            closestHit = hi;
        }
    }

    if (closestHit.hit) {
        glm::vec3 direction = closestHit.normal + gentracer::randvechemi(closestHit.normal);
        Ray bounced(closestHit.point, direction);
        return 0.5f * cast(bounced, depth - 1);
    }

    glm::vec3 unitDirection = glm::normalize(ray.getDirection());
    float a = 0.5f * (unitDirection.y + 1.0f);
    return (1.0f - a) * glm::vec3(1.0f) + a * glm::vec3(0.2f, 0.4f, 1.0f);
}
