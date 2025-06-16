#include "layer.h"
#include <memory>
#include <algorithm>

LayerStack::LayerStack() {}

    LayerStack::~LayerStack() {
        for (std::shared_ptr<Layer> layer : m_Layers) {
            layer->OnDetach();
        }
    }

    void LayerStack::PushLayer(std::shared_ptr<Layer> layer) {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
        m_LayerInsertIndex++;
        layer->OnAttach();
    }

    void LayerStack::PopLayer(std::shared_ptr<Layer> layer) {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if (it != m_Layers.end()) {
            m_Layers.erase(it);
            m_LayerInsertIndex--;
            layer->OnDetach();
        }
    }

    void LayerStack::PopAllLayers() {
        for (std::shared_ptr<Layer> layer : m_Layers) {
            layer->OnDetach();
        }
        m_Layers.clear();
        m_LayerInsertIndex = 0;
    }

    void LayerStack::OnUpdate(float deltatime) {
        for (std::shared_ptr<Layer> layer : m_Layers) {
            layer->OnUpdate(deltatime);
        }
    }

    void LayerStack::OnRender()
    {
        for (std::shared_ptr<Layer> layer : m_Layers) {
            layer->OnRender();
        }
    }

