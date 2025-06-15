#include "image_writer.h"
#include <cstdint>
#include <fstream>
#include <string>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#include "../logger/logger.h"

ImageWriter::ImageWriter(const std::string& fileName) : m_FileName(fileName) {

}

ImageWriter::~ImageWriter() { }

void ImageWriter::write(const Image::ImageType& type, const Image& img) {

    auto rawImg = img.data();

    switch (type) {

        case Image::IMAGE_TYPE_PNG:
            this->writePng(img.getWidth(), img.getWidth(), img.data().data());
            break;
        case Image::IMAGE_TYPE_PPM:
            this->writePpm(img.getWidth(), img.getHeight(), img.data().data());
            break;
    
    }

}


void ImageWriter::writePng(int width, int height, const uint8_t* pixels) {

    stbi_write_png(this->m_FileName.c_str(), width, height, 3, pixels, width * 3);

}

void ImageWriter::writePpm(int width, int height, const uint8_t* pixels) {

    std::ofstream file(this->m_FileName);
    if (!file.is_open()) {
        LOG_ERROR("Failed to open file {}", this->m_FileName);
        return;
    }

    file << "P3\n" << width << " " << height << "\n255\n";

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int i = (y * width + x) * 3;
            file << (int)pixels[i + 0] << " "
                 << (int)pixels[i + 1] << " "
                 << (int)pixels[i + 2] << "\n";
        }
    }

}
