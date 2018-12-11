#include "Image.h"

/*
 * Initialize libpng I/O. 
 *
 * Allocate and initialize structs png_struct and png_info, both of which are
 * crucial to working with libpng.
 * 
 * struct png_struct is used internally by libpng and must be the first
 * variable to every libpng function call.
 * 
 * struct png_info contains information about the PNG file, such as
 * IHDR chunk, image palette information and text comments.
 *
 * Neither of these structs are directly accessible. Use interface functions
 * png_get_*() to access struct data.
 *
 * Ref: http://refspecs.linuxfoundation.org/LSB_3.1.1/LSB-Desktop-generic/LSB-Desktop-generic/toclibpng.html
 */
void Image::init_png_io() {
    m_read = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    m_info = png_create_info_struct(m_read);

    /* Define our own input function for reading PNG files, as opposed to using
     * the standard C I/O.
     */
    png_set_read_fn(m_read, reinterpret_cast<png_voidp>(&m_file), read_callback);

    png_read_info(m_read, m_info);
}

Image::Image(const std::string fn) {
    m_fn = fn;
    m_file.open(m_fn);

    init_png_io();

    m_width = png_get_image_width(m_read, m_info);
    m_height = png_get_image_height(m_read, m_info);
    m_bitdepth = png_get_bit_depth(m_read, m_info);
    m_rowbytes = png_get_rowbytes(m_read, m_info);
    m_channels = png_get_channels(m_read, m_info);
    m_color_type = png_get_color_type(m_read, m_info);
    m_pixels = new unsigned char*[m_height];

    for (int i = 0; i < m_height; i++) {
        m_pixels[i] = new unsigned char[m_rowbytes];
    }

    png_read_update_info(m_read, m_info);
}

Image::~Image() {
    if (m_read && m_info)
        png_destroy_read_struct(&m_read, &m_info, NULL);

    for (int i = 0; i < m_height; i++) {
        delete[] m_pixels[i];
    }

    delete[] m_pixels;
}

/* vim: set ts=4 sw=4 tw=79 ft=cpp et :*/
