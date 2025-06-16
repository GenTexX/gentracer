#pragma once

#include <algorithm>
#include <vector>

#include <GL/glew.h>
#include "../image/image.h"

#include <imgui.h>

class ImGuiImageRenderer {

    public:
        ImGuiImageRenderer() {}
        ~ImGuiImageRenderer() {
            if (m_TextureID != 0) {
                glDeleteTextures(1, &m_TextureID);
            }
        }

        void uploadImage(const Image& image) {

            if (m_TextureID != 0) {
                glDeleteTextures(1, &m_TextureID);
            }

            m_Width = image.getWidth();
            m_Height = image.getHeight();

            // Delete existing texture if any
            if (m_TextureID != 0) {
                glDeleteTextures(1, &m_TextureID);
            }

            // Generate new texture
            glGenTextures(1, &m_TextureID);
            glBindTexture(GL_TEXTURE_2D, m_TextureID);

            // Set texture parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            // Convert glm::vec3 data to RGB bytes
            std::vector<unsigned char> pixelData;
            pixelData.reserve(m_Width * m_Height * 3);

            auto imageData = image.data();
            for (const auto& pixel : imageData) {
                // Clamp values to [0,1] and convert to [0,255]
                pixelData.push_back(static_cast<unsigned char>(pixel));
            }

            // Upload to GPU
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData.data());

            glBindTexture(GL_TEXTURE_2D, 0);

            m_HasUploaded = true;
        }

        bool hasUploaded() {
            return m_HasUploaded;
        }

        void drawInImGui(float displayWidth = 0.0f, float displayHeight = 0.0f) {
            if (m_TextureID == 0) {
                ImGui::Text("No image loaded");
                return;
            }

            // Use original size if no display size specified
            if (displayWidth <= 0.0f) displayWidth = static_cast<float>(m_Width);
            if (displayHeight <= 0.0f) displayHeight = static_cast<float>(m_Height);

            // Cast texture ID to ImTextureID (usually void*)
            ImTextureID texID = reinterpret_cast<ImTextureID>(static_cast<unsigned long long>(m_TextureID));

            // Display the image
            ImGui::Image(texID, ImVec2(displayWidth, displayHeight));
        }

    private:
        GLuint m_TextureID = 0;
        int m_Width = 0;
        int m_Height = 0;
        bool m_HasUploaded = false;

};
