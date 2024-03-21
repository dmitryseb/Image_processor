//
// Created by Дмитрий Сергиенко on 23.10.2023.
//

#include "bmp_utils.h"
#include "image.h"

const uint16_t BmpStream::BMP_TYPE = 0x4D42;
const uint32_t BmpStream::SIZE_INFO_HEADER = 40;
const uint16_t BmpStream::BITS_PER_PIXEL = 24;

BmpStream::~BmpStream() {
    Close();
}

void BmpStream::Open(const std::string &filename, char mode) {
    if (file_.is_open()) {
        throw std::logic_error("File is already open.");
    }

    if (filename.empty()) {
        throw std::invalid_argument("Filename is empty.");
    }

    if (filename.size() < 4 || filename.substr(filename.size() - 4, 4) != ".bmp") {
        throw std::logic_error("Giving not .bmp file.");
    }

    filename_ = filename;
    if (mode == 'w') {
        file_.open(filename_, std::ios::out);
    } else if (mode == 'r') {
        file_.open(filename_, std::ios::in);
    }
    mode_ = mode;

    if (!file_.is_open()) {
        throw std::runtime_error("Cannot open file.");
    }
}

void BmpStream::Close() {
    if (file_.is_open()) {
        file_.close();
    }

    mode_ = 0;

    if (file_.is_open()) {
        throw std::runtime_error("Cannot close file.");
    }
}

void BmpStream::ReadFileHeader() {
    if (!file_.is_open()) {
        throw std::logic_error("File is not open.");
    }

    file_.read(reinterpret_cast<char *>(&fileHeader_), sizeof(FileHeader));

    if (fileHeader_.type != BMP_TYPE) {
        throw std::runtime_error("BMP File is not correct.");
    }
}

void BmpStream::ReadInfoHeader() {
    if (!file_.is_open()) {
        throw std::logic_error("File is not open.");
    }

    file_.read(reinterpret_cast<char *>(&infoHeader_), sizeof(InfoHeader));
}

void BmpStream::ReadIntPixel(IntPixel &pixel) {
    file_.read(reinterpret_cast<char *>(&pixel), sizeof(IntPixel));
}

void BmpStream::ReadPixelInfo(Image &image) {
    if (!file_.is_open()) {
        throw std::logic_error("File is not open.");
    }

    image.Resize(infoHeader_.height, infoHeader_.width);
    file_.seekg(fileHeader_.off_bits);

    size_t height = abs(infoHeader_.height);
    size_t width = infoHeader_.width;
    int64_t shift = static_cast<int64_t>((4 - ((width * 3) % 4)) % 4);

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            IntPixel int_pixel;
            ReadIntPixel(int_pixel);
            if (infoHeader_.height > 0) {
                image.ChangePixel(i, j, ToPixel(int_pixel));
            } else {
                image.ChangePixel(height - i - 1, j, ToPixel(int_pixel));
            }
        }
        file_.seekg(file_.tellg() + shift);
    }
    infoHeader_.height = abs(infoHeader_.height);
}

Image BmpStream::ReadImage() {
    if (!file_.is_open()) {
        throw std::logic_error("File is not open.");
    }

    file_.seekg(0);

    ReadFileHeader();

    ReadInfoHeader();

    Image image;
    ReadPixelInfo(image);
    return image;
}

void BmpStream::WriteFileHeader() {
    if (!file_.is_open()) {
        throw std::logic_error("File is not open.");
    }

    file_.write(reinterpret_cast<char *>(&fileHeader_), sizeof(FileHeader));
}

void BmpStream::WriteInfoHeader() {
    if (!file_.is_open()) {
        throw std::logic_error("File is not open.");
    }

    file_.write(reinterpret_cast<char *>(&infoHeader_), sizeof(InfoHeader));
}

void BmpStream::WriteIntPixel(const IntPixel &int_pixel) {
    IntPixel wr_int_pixel = int_pixel;
    file_.write(reinterpret_cast<char *>(&wr_int_pixel), sizeof(IntPixel));
}

void BmpStream::WritePixelInfo(const Image &image) {
    if (!file_.is_open()) {
        throw std::logic_error("File is not open.");
    }

    size_t height = infoHeader_.height;
    size_t width = infoHeader_.width;
    size_t shift = (4 - ((width * 3) % 4)) % 4;

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            IntPixel int_pixel = IntPixel(image.GetPixel(i, j));
            WriteIntPixel(int_pixel);
        }
        char c = 0;
        for (size_t j = 0; j < shift; ++j) {
            file_.write(&c, 1);
        }
    }
}

BmpStream::FileHeader::FileHeader(const Image &image) {
    type = BMP_TYPE;
    uint32_t shift = (4 - ((image.GetWidth() * 3) % 4)) % 4;
    size = sizeof(FileHeader) + sizeof(InfoHeader) + (image.GetWidth() * 3 + shift) * image.GetHeight();
    off_bits = sizeof(FileHeader) + sizeof(InfoHeader);
    reserved1 = 0;
    reserved2 = 0;
}

BmpStream::InfoHeader::InfoHeader(const Image &image) {
    size = SIZE_INFO_HEADER;
    width = static_cast<int>(image.GetWidth());
    height = static_cast<int>(image.GetHeight());
    color_planes = 1;
    bits_per_pixel = BITS_PER_PIXEL;
    compression = 0;
    size_image = 0;
    hor_resolution = 0;
    ver_resolution = 0;
    colors_num = 0;
    important_colors_num = 0;
}

void BmpStream::WriteImage(const Image &image) {
    if (!file_.is_open()) {
        throw std::logic_error("File is not open.");
    }

    file_.seekp(0);

    fileHeader_ = FileHeader(image);
    WriteFileHeader();

    infoHeader_ = InfoHeader(image);
    WriteInfoHeader();

    WritePixelInfo(image);
}
