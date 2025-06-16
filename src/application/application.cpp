#include "application.h"
#include "../logger/logger.h"
#include "../imgui/gentracer_imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <memory>
#include "../image/image_writer.h"
#include "../ray/ray.h"
#include "../layer/impl/main_layer.h"

glm::vec3 rayColor(Ray ray) {
    glm::vec3 unitDirection = glm::normalize(ray.getDirection());
    float a = 0.5f * (unitDirection.y + 1.0f);
    return (1.0f - a) * glm::vec3(1.0f, 1.0f, 1.0f) + a * glm::vec3(0.5f, 0.7f, 1.0f);
}

Application::Application(int width, int height, const std::string& title)
    : m_Width(width), m_Height(height), m_Title(title), m_LayerStack() {}

Application::~Application() {
}

void Application::init() {
    
    Logger::init();

    m_Window = new Window(m_Width, m_Height, m_Title);

    // Initialize GLEW AFTER context is made current
    glewExperimental = GL_TRUE; // Ensures core profile support
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        throw std::runtime_error(std::string("Failed to initialize GLEW: ") +
                                 reinterpret_cast<const char*>(glewGetErrorString(err)));
    }

    imguiInit(m_Window->getGLFWwindow());

    m_LayerStack.PushLayer(std::make_shared<MainLayer>(this));

    LOG_TRACE("Application initialized with GLEW {}", reinterpret_cast<const char*>(glewGetString(GLEW_VERSION)));
}

void Application::run() {
    LOG_TRACE("Application running...");
    bool opt_fullscreen = true;
    bool opt_padding = false;
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    bool dockSpaceOpen = true;


    auto lastTime = std::chrono::system_clock::now();

    while (!m_Window->shouldClose()) {
        m_Window->pollEvents();

        auto now = std::chrono::system_clock::now();

        update((now - lastTime).count() / 1000.0f);


        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;


        auto io = ImGui::GetIO();
        if (opt_fullscreen)
        {
            const ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }


        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        
        ImGui::Begin("dockspace", &dockSpaceOpen, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("dockspace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }       

        render();
         
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backupCurrentContext);

        }

        m_Window->swapBuffers();


        lastTime = now;
    }
}

void Application::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete m_Window;
    m_Window = nullptr;
    LOG_TRACE("Application destroyed."); 
}

void Application::update(float delta) {
    m_LayerStack.OnUpdate(delta);
}

void Application::render() {
    m_LayerStack.OnRender();
}
