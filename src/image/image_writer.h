#pragma once

#include <string>

#include "image.h"

class ImageWriter {

    public:

        ImageWriter(const std::string& fileName);
        ~ImageWriter();

        void write(const Image::ImageType& type, const Image& img);

    private:
        const std::string m_FileName;

        void writePng(int width, int height, const uint8_t* pixels); 
        void writePpm(int width, int height, const uint8_t* pixels);
};
