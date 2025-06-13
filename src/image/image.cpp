#include "image.h"
#include <glm/ext/vector_float3.hpp>

Image::Image(int width, int height) : m_Width(width), m_Height(height) {

    m_Data = std::vector<glm::vec3>(m_Width * m_Height);

}                           

Image::~Image() { }

void Image::write(int x, int y, glm::vec3 color) {
    int index = x + y * m_Width;
    m_Data.at(index) = color;
}

