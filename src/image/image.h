#pragma once

#include <vector>
#include <cstdint>

#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_float3.hpp>

#include <glm/glm.hpp>


class Image {


    public:

        enum ImageType {
            IMAGE_TYPE_PNG,
            IMAGE_TYPE_PPM
        };
        
        Image(int width, int height);
        ~Image();

        void write(int x, int y, glm::vec3 color);
        glm::vec3 read(int x, int y);

        std::vector<uint8_t> data() const;

        int getWidth() const { return m_Width; }
        int getHeight() const { return m_Height; }

        float getAspectRatio() { return static_cast<float>(m_Width) / static_cast<float>(m_Height); }

    private:
        int m_Width;
        int m_Height;

        std::vector<glm::vec3> m_Data;

};
