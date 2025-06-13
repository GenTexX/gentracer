#pragma once

#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_float3.hpp>
#include <vector>

#include <glm/glm.hpp>

class Image {

    public:
        Image(int width, int height);
        ~Image();

        void write(int x, int y, glm::vec3 color);

    private:
        int m_Width;
        int m_Height;

    std::vector<glm::vec3> m_Data;

};
