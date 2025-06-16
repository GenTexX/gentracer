#include "camera.h"
#include <chrono>
#include <functional>
#include <glm/ext/vector_float3.hpp>

#include "../logger/logger.h"

#include "../util/random.h"

Camera::Camera(
        const glm::vec3& origin,
        const glm::vec3& lookAt,
        const glm::vec3& up
        ) {

    m_Origin = origin;
    m_LookAt = lookAt;
    m_Up = up;
    m_SamplesPP = 10;
}

void Camera::setSamplesPerPixel(int samples) {

    m_SamplesPP = samples;

}

void Camera::render(std::shared_ptr<Scene> scene, std::shared_ptr<Image> image, std::function<void(int)> onScanlineRendered) {
    auto begin = std::chrono::system_clock::now();

    float imageWidth = image->getWidth();
    float imageHeight = image->getHeight();
    float aspectRatio = imageWidth / imageHeight;

    float focalLength = 1.0f;
    float viewportHeight = 2.0f;
    float viewportWidth = viewportHeight * aspectRatio;


    glm::vec3 w = glm::normalize(m_Origin - m_LookAt);  // backward
    glm::vec3 u = glm::normalize(glm::cross(m_Up, w));  // right
    glm::vec3 v = glm::cross(w, u);                     // real "up"

    glm::vec3 viewPortU = glm::vec3(viewportWidth, 0.0f, 0.0f);//viewportWidth * u;
    glm::vec3 viewPortV = glm::vec3(0.0f, -viewportHeight, 0.0f);//-viewportHeight * v;  // minus because image space Y is top-to-bottom

    LOG_TRACE("vpu: {}", viewPortU);
    LOG_TRACE("vpv: {}", viewPortV);
    
    glm::vec3 pixelDeltaU = viewPortU / float(imageWidth);
    glm::vec3 pixelDeltaV = viewPortV / float(imageHeight);

    glm::vec3 viewPortUpperLeft = m_Origin
        - focalLength * w
        - viewPortU / 2.0f
        - viewPortV / 2.0f;

    glm::vec3 pixel00Location = viewPortUpperLeft + 0.5f * (pixelDeltaU + pixelDeltaV);

    float pixelSampleScale = 1.0f / m_SamplesPP;
   
    auto worker = [&](int startY, int endY) {
        for (int j = startY; j < endY; ++j) {
            for (int i = 0; i < imageWidth; ++i) {
                glm::vec3 color(0.0f);
                for (int s = 0; s < m_SamplesPP; ++s) {
                    Ray ray = getRay(i, j, pixel00Location, pixelDeltaU, pixelDeltaV); // sample jitter included
                    color += scene->cast(ray, 10);
                }
                color /= float(m_SamplesPP);
                image->write(i, j, color);
            }
            onScanlineRendered(j);
        }
    };

    const int threadCount = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    int slice = imageHeight / threadCount;

    for (int t = 0; t < threadCount; ++t) {
        int start = t * slice;
        int end = (t == threadCount - 1) ? imageHeight : start + slice;
        threads.emplace_back(worker, start, end);
    }

    for (auto& thread : threads)
        thread.join();
    /*
    for (int j = 0; j < imageHeight; j++) {

        for (int i = 0; i < imageWidth; i++) {

            glm::vec3 pixelColor = glm::vec3(0.0f);
            for (int sample = 0; sample < m_SamplesPP; sample++) {
                Ray ray = this->getRay(i, j, pixel00Location, pixelDeltaU, pixelDeltaV);

                pixelColor += scene->cast(ray, 5);

            }

            image->write(i, j, pixelSampleScale * pixelColor);

        }

        onScanlineRendered(j);

    }
*/
    auto end = std::chrono::system_clock::now();

    LOG_INFO("Rendered {}x{} with {} samples in {:.3f} seconds", imageWidth, imageHeight, m_SamplesPP, (end - begin).count() / 1e9f);

}


Ray Camera::getRay(int i, int j, glm::vec3 pixel00, glm::vec3 deltaU, glm::vec3 deltaV) const {

    // Random sample inside the pixel [0,1) x [0,1)
    float px = gentracer::rand(0.0f, 1.0f);
    float py = gentracer::rand(0.0f, 1.0f);

    glm::vec3 pixelOffset = px * deltaU + py * deltaV;

    glm::vec3 pixelCenter = pixel00 + float(i) * deltaU + float(j) * deltaV;
    glm::vec3 pixelSample = pixelCenter + pixelOffset;

    glm::vec3 direction = glm::normalize(pixelSample - m_Origin);
    return Ray(m_Origin, direction);

}
