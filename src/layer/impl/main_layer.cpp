#include "main_layer.h"

#include <cmath>
#include <glm/ext/vector_float3.hpp>
#include <imgui.h>
#include <memory>
#include <thread>

#include "../../render/camera.h"

void MainLayer::OnAttach() {

    const int imageWidth = 3840;
    const int imageHeight = 2160;

    m_Image = std::make_shared<Image>(imageWidth, imageHeight);
    m_TotalScanlines = imageHeight;
    m_Scene = std::make_shared<Scene>();

    m_Scene->add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, glm::vec3(0.619f, 0.286f, 0.396f)));
    m_Scene->add(std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f, glm::vec3(0.619f, 0.286f, 0.396f)));

    m_Camera = std::make_shared<Camera>(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    m_Camera->setSamplesPerPixel(2048); 
    this->startRender();

}

void MainLayer::OnDetach() {
    if (m_RenderThread.joinable())
        m_RenderThread.join();
}

void MainLayer::OnUpdate(float deltatime) { 

}

void MainLayer::OnRender() {
    ImGui::Begin("Hello gentracer");

    ImVec2 contentSize = ImGui::GetContentRegionAvail();
    float padding = 8.0f;
    float maxWidth = contentSize.x - padding;
    float maxHeight = contentSize.y - padding - 100.0f;

    float imageWidth = static_cast<float>(m_Image->getWidth());
    float imageHeight = static_cast<float>(m_Image->getHeight());

    float widthRatio = maxWidth / imageWidth;
    float heightRatio = maxHeight / imageHeight;
    float ratio = std::min(widthRatio, heightRatio);

    ImGui::SetCursorPos(ImVec2(padding, padding));

    if (m_RenderFinished) {
        if (!m_ImageRenderer.hasUploaded())
            m_ImageRenderer.uploadImage(*m_Image); // upload only once

        m_ImageRenderer.drawInImGui(imageWidth * ratio, imageHeight * ratio);
        if(ImGui::Button("Redraw")) {
            this->startRender();
        }
        if(ImGui::Button("Save")) {
            m_ImageWriter.write(Image::IMAGE_TYPE_PNG, *m_Image);
        }
    } else if (m_RenderStarted) {
        ImGui::Text("Rendering in progress...");
        float progress = static_cast<float>(m_ProgressScanlines) / m_TotalScanlines;
        ImGui::ProgressBar(progress, ImVec2(-1.0f, 0.0f));
    } else {
        ImGui::Text("Render not started.");
        if(ImGui::Button("Draw")) {
            this->startRender();
        }
    }

    ImGui::End();
}

void MainLayer::startRender() {

    if (m_RenderThread.joinable()) {
        m_RenderThread.join();  // wait for previous render to finish
    }

    m_RenderFinished = false;
    m_RenderStarted = true;
    m_ProgressScanlines = 0;
    m_TotalScanlines = m_Image->getHeight();

    m_RenderThread = std::thread([this]() {
            m_Camera->render(m_Scene, m_Image, [this](int j) {
                    m_ProgressScanlines++;
                    });
            m_RenderFinished = true;
            });

}
