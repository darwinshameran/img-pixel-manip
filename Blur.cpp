#include "Blur.h"

/* Implement a box blur. */

void Blur::apply_filter(int width, int height, int channels, unsigned char** pixels) {
    const unsigned int stride = width * channels;

    unsigned char** tmp = new unsigned char*[height];
    for (int i = 0; i < height; i++)
        tmp[i] = new unsigned char[stride];

    for (int y = 0; y < height; y++) {
        unsigned char* row0 = get_pixel(y == 0 ? y : y - 1, pixels);
        unsigned char* row1 = get_pixel(y, pixels);
        unsigned char* row2 = get_pixel(y == height - 1 ? y : y + 1, pixels);

        if (y == 0)
            row0 = row1;

        if (y == height - 1)
            row2 = row1;

        unsigned char* dest = get_pixel(y, tmp);

        for (int i = 0; i < stride; i++) {
            int col0 = i - channels;
            int col1 = i;
            int col2 = i + channels;

            if (i < channels)
                col0 = col1;

            if (i >= stride - channels)
                col2 = col1;

            set_rgba(i, (row0[col0] + row0[col1] + row0[col2]
                    + row1[col0] + row1[col1] + row1[col2]
                    + row2[col0] + row2[col1] + row2[col2]) / 9, dest);
        }
    }

    /* Replace pixels in m_pixels with blurred ones. */
    replace_pixels(pixels, tmp, height);
}

Blur::~Blur() {
}

/* vim: set ts=4 sw=4 tw=79 ft=cpp et :*/
