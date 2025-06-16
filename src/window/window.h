#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    void pollEvents() const;
    void swapBuffers() const;

    bool shouldClose() const;
    GLFWwindow* getGLFWwindow() const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    GLFWwindow* window = nullptr;
    int width;
    int height;

    void initGLFW();
};
