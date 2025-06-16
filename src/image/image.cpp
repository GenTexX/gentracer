#include "image.h"
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <glm/ext/vector_float3.hpp>
#include "../util/interval.h"

Image::Image(int width, int height) : m_Width(width), m_Height(height) {

    m_Data = std::vector<glm::vec3>(m_Width * m_Height);

}                           

Image::~Image() { }

void Image::write(int x, int y, glm::vec3 color) {
    int index = x + y * m_Width;
    m_Data.at(index) = color;
}

glm::vec3 Image::read(int x, int y) {
    int index = x + y * m_Width;
    return m_Data.at(index);
}

std::vector<uint8_t> Image::data() const {

    size_t count = m_Data.size();
    
    std::vector<uint8_t> data(count * 3);

    float gamma = 2.2f;

    auto toByte = [gamma](float c) -> uint8_t {
        c = std::pow(c, 1.0f / gamma);
        return static_cast<uint8_t>(c * 256.0f);
    };

    static const Interval intensity(0.0f, 0.999f);

    for (size_t i = 0; i < count; i++) {
        data[i * 3 + 0] = toByte(intensity.clamp(this->m_Data[i].r));
        data[i * 3 + 1] = toByte(intensity.clamp(this->m_Data[i].g));
        data[i * 3 + 2] = toByte(intensity.clamp(this->m_Data[i].b));
    }

    return data;

}
