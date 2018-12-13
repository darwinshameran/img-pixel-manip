#include "Image.h"
#include "Blur.h"
#include "Invert.h"
#include "ImageDisplay.h"

/*
 * Callback function passed to png_set_read_fn()
 */
void read_callback(png_structp png_ptr, png_bytep data, png_size_t len) {
    png_voidp io_ptr = png_get_io_ptr(png_ptr);
    reinterpret_cast<std::ifstream*>(io_ptr)->read(reinterpret_cast<char*>(data), len);
}

/*
 * Callback function passed to png_set_write_fn()
 */
void write_callback(png_structp png_ptr, png_bytep data, png_size_t len) {
    png_voidp io_ptr = png_get_io_ptr(png_ptr);
    reinterpret_cast<std::ofstream*>(io_ptr)->write(reinterpret_cast<char*>(data), len);
}

/*
 * Initialize libpng I/O.
 *
 * Allocate and initialize structs png_struct and png_info, both of which are
 * crucial to working with libpng.
 *
 * struct png_struct is used internally by libpng and must be the first
 * argument to every libpng function call.
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
    m_read = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    m_info = png_create_info_struct(m_read);

    /*
     * Define our own input function for reading PNG files, as opposed to using
     * the standard C I/O.
     */
    png_set_read_fn(m_read, reinterpret_cast<png_voidp>(&m_file), read_callback);

    png_read_info(m_read, m_info);
}

Image::Image(const std::string fn) {
    m_fn = fn;
    m_file.open(m_fn, std::ios::binary);

    if (!m_file)
        throw std::runtime_error("Unable to open file " + m_fn);

    if(!is_png())
        throw std::runtime_error("Invalid filetype; unable to detect PNG signature.");

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

    /* Expand 1, 2 or 4 bit PNG images to 8 */
    if (m_color_type == PNG_COLOR_TYPE_GRAY && m_bitdepth < 8)
        png_set_expand_gray_1_2_4_to_8(m_read);

    png_read_update_info(m_read, m_info);
}

void Image::read_image() const {
    png_read_image(m_read, m_pixels);  /* Populate m_pixels with image data. */
    png_read_end(m_read, m_info);
}

void Image::display_image(const std::string& window_title) const {
    ImageDisplay display(window_title, m_width, m_height, m_channels);
    display.display_image(m_pixels);
}

void Image::filter(std::string& filter) const {
    std::transform(filter.begin(), filter.end(), filter.begin(), ::tolower);
    int max_rgba_value;
    int min_rgba_value;

    if (m_bitdepth == 8)
        max_rgba_value = 255;                         /* 8 bits per channel */
    else
        max_rgba_value = 65535;                       /* 16 bits per channel */

    min_rgba_value = (max_rgba_value - max_rgba_value); /* 0 */

    if (filter == "blur") {
            Blur blur(min_rgba_value, max_rgba_value);
            blur.apply_filter(m_width, m_height, m_channels, m_pixels);
    } else if (filter == "invert") {
        Invert invert(min_rgba_value, max_rgba_value);
        invert.apply_filter(m_width, m_height, m_channels, m_pixels);
    }
}

void Image::write_image() const {
    std::ofstream output("output.png", std::ios::binary);
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

    /*
     * Define our own input function for writing PNG files, as opposed to using
     * the standard C I/O.
     */
    png_set_write_fn(png_ptr, reinterpret_cast<png_voidp>(&output), write_callback, nullptr);

    /* Set file header. */
    png_set_IHDR(
            png_ptr,
            m_info,
            m_width, m_height,
            m_bitdepth,
            m_color_type,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT
            );

    png_write_info(png_ptr, m_info);
    png_write_image(png_ptr, m_pixels);
    png_write_end(png_ptr, m_info);

    png_destroy_write_struct(&png_ptr, nullptr);    /* Free allocated memory. */
}

/*
 * Ensure the first eight bytes of supplied PNG file match the PNG
 * signature. The first eight bytes of a PNG file always contain the same
 * values. Return zero if the signature does not match, respectively, one
 * if the signature does match. The following bytes are used as a signature to
 * verify PNG files:
 *
 *      (decimal)              137  80  78  71  13  10  26  10
 *      (hex)                   89  50  4e  47  0d  0a  1a  0a
 *      (ASCII C)             \211   P   N   G  \r  \n \032 \n
 *
 * Ref: http://www.libpng.org/pub/png/book/chapter08.html#png.ch08.tbl.1
 *
 */
bool Image::is_png() const {
    const unsigned int signature_bytes = 8;
    std::ifstream file(m_fn, std::ios::binary);
    png_byte header[signature_bytes];

    if (!file.good())
        return false;

    file.read(reinterpret_cast<char *>(header), signature_bytes);

    return (png_sig_cmp(header, 0, signature_bytes) == 0);
}

Image::~Image() {
    if (m_read && m_info)
        png_destroy_read_struct(&m_read, &m_info, nullptr);

    for (int i = 0; i < m_height; i++) {
        delete[] m_pixels[i];
    }

    delete[] m_pixels;
}

/* vim: set ts=4 sw=4 tw=79 ft=cpp et :*/
