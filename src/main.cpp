#include <glm/ext/vector_float3.hpp>
#include <iostream>

#include <glm/glm.hpp> 
#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "image/image.h"
#include "image/image_writer.h"
#include "logger/logger.h"
int main() {

    // logger
    Logger::init();

    LOG_INFO("Hello World");

    // Image
    int imageWidth = 256;
    int imageHeight = 256;

    // Render
    Image img(256, 256);

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++ ) {
   
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;

        for (int i = 0; i < imageWidth; i++) {
            
            double r = double(i) / (imageWidth - 1);
            double g = double(j) / (imageHeight - 1);
            double b = 0.0;

            img.write(j, i, glm::vec3(r, g, b));

        }

    }

    ImageWriter imgWriter("myimage.ppm");

    imgWriter.write(Image::IMAGE_TYPE_PPM, img);

    std::clog << "\rDone                              \n";

    //std::cout << "Hello World!" << std::endl;

    return 0;

}
