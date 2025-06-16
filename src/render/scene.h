#pragma once

#include <memory>
#include <vector>

#include "scene_object.h"

class Scene {

    public:
        Scene();
        ~Scene();

        void add(std::shared_ptr<SceneObject> object);

        const std::vector<std::shared_ptr<SceneObject>>& getObjects() const;


        glm::vec3 cast(const Ray& ray, int depth = 1) const; 


    private:
        std::vector<std::shared_ptr<SceneObject>> m_Objects;

};
