#pragma once

#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <memory>
#include <thread>

#include "../layer.h"
#include "../../logger/logger.h"
#include "../../render/scene.h"
#include "../../render/camera.h"
#include "../../render/impl/sphere.h"
#include "../../image/image.h"
#include "../../image/image_writer.h"
#include "../../imgui/image_renderer.h"

class MainLayer : public Layer {

    public:
        MainLayer(Application* app) : Layer(app), m_ImageWriter("result.png") {}
        virtual ~MainLayer() = default;
    
        virtual void OnAttach(); 
        virtual void OnDetach();
        virtual void OnUpdate(float deltatime);
        virtual void OnRender();

    private:
        std::shared_ptr<Scene> m_Scene;
        std::shared_ptr<Image> m_Image;
        std::shared_ptr<Camera> m_Camera;
        ImGuiImageRenderer m_ImageRenderer;
        ImageWriter m_ImageWriter;

        std::thread m_RenderThread;
        std::atomic<bool> m_RenderFinished = false;
        std::atomic<bool> m_RenderStarted = false;

        std::atomic<int> m_ProgressScanlines = 0;
        int m_TotalScanlines = 1;

        void startRender();

};
