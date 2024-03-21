//
// Created by Дмитрий Сергиенко on 23.10.2023.
//

#ifndef CPP_HSE_BMP_UTILS_H
#define CPP_HSE_BMP_UTILS_H

#include <cstdint>
#include <string>
#include <fstream>
#include "image.h"

class BmpStream {
public:
    BmpStream(){};
    ~BmpStream();

public:
    struct FileHeader {
        FileHeader(){};
        explicit FileHeader(const Image& image);
        uint16_t type;
        uint32_t size;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t off_bits;
    } __attribute__((packed));

    struct InfoHeader {
        InfoHeader(){};
        explicit InfoHeader(const Image& image);
        uint32_t size;
        int32_t width;
        int32_t height;
        uint16_t color_planes;
        uint16_t bits_per_pixel;
        uint32_t compression;
        uint32_t size_image;
        int32_t hor_resolution;
        int32_t ver_resolution;
        uint32_t colors_num;
        uint32_t important_colors_num;
    } __attribute__((packed));

    void Open(const std::string& filename, char mode);

    void Close();

    const std::string GetFilename() {
        return filename_;
    }

    Image ReadImage();

    void WriteImage(const Image& image);

protected:
    static const uint16_t BMP_TYPE;
    static const uint32_t SIZE_INFO_HEADER;
    static const uint16_t BITS_PER_PIXEL;

    std::string filename_;
    std::fstream file_;
    FileHeader fileHeader_;
    InfoHeader infoHeader_;
    char mode_;

    void ReadFileHeader();

    void ReadInfoHeader();

    void ReadIntPixel(IntPixel& pixel);

    void ReadPixelInfo(Image& image);

    void WriteFileHeader();

    void WriteInfoHeader();

    void WriteIntPixel(const IntPixel& pixel);

    void WritePixelInfo(const Image& image);
};

#endif  // CPP_HSE_BMP_UTILS_H
