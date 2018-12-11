#ifndef IMAGE_H
#define IMAGE_H

#include "png.h"
#include <string>
#include <fstream>
#include <stdexcept>
#include <algorithm>

class Image {
 private:
    std::string m_fn;
    std::ifstream m_file;
    unsigned char** m_pixels;
    png_structp m_read;  
    png_infop m_info;
    
    png_uint_32 m_width;
    png_uint_32 m_height; 
    png_uint_32 m_rowbytes;
    png_uint_32 m_bitdepth;
    png_uint_32 m_channels;
    png_uint_32 m_color_type;

    void init_png_io();
    
 public:
    Image(const std::string);
    ~Image();

    void write_image() const;
    void read_image() const;
    bool is_png() const;
    void display_image(const char*) const;
    void apply_filter(const char*) const;
};

#endif

/* vim: set ts=4 sw=4 tw=79 ft=cpp et :*/
