#pragma once

#include <vector>
#include <memory>

class Application;

class Layer {

    public:
        Layer(Application* app) : m_Application(app) {}
        virtual ~Layer() = default;

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void OnUpdate(float deltatime) = 0;
        virtual void OnRender() = 0;

    private:
        Application* m_Application;

};

class LayerStack {

    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(std::shared_ptr<Layer> layer);
        void PopLayer(std::shared_ptr<Layer> layer);
        void PopAllLayers();
        void OnUpdate(float deltatime);
        void OnRender();

    private:
        std::vector<std::shared_ptr<Layer>> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
};
