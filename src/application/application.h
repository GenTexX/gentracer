#pragma once

#include "../window/window.h"
#include "../imgui/image_renderer.h"

#include "../layer/layer.h"

class Application {
public:
    Application(int width, int height, const std::string& title);
    ~Application();

    void init();    // Create window and other systems
    void run();     // Main loop
    void destroy(); // Cleanup

private:
    Window* m_Window = nullptr;
    int m_Width;
    int m_Height;
    std::string m_Title;

    LayerStack m_LayerStack;

    void update(float delta);  // Per-frame logic
    void render();  // Rendering code
};
