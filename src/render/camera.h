#pragma once

#include "scene.h"
#include "../image/image.h"
#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <functional>

class Camera {

    public:
        Camera(
                const glm::vec3& origin,
                const glm::vec3& lookAt,
                const glm::vec3& up
              );

        void render(std::shared_ptr<Scene> scene, std::shared_ptr<Image> image, std::function<void(int)> onScanlineRendered);

        void setSamplesPerPixel(int samples);

    private:
        glm::vec3 m_Origin;
        glm::vec3 m_LookAt;
        glm::vec3 m_Up;
        int m_SamplesPP;

        Ray getRay(int i, int j, glm::vec3 pixel00, glm::vec3 deltaU, glm::vec3 deltaV) const;  

};
