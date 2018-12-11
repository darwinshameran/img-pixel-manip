#include "Blur.h"

/* Implement a box blur. */

Blur::Blur(int width, int height, int channels, unsigned char** pixels) {
    channels = (channels == 4) ? 3 : channels; /* Not targeting alpha channels. */
    const unsigned int stride = width * channels;

    unsigned char** tmp = new unsigned char*[height];
    for (int i = 0; i < height; i++)
        tmp[i] = new unsigned char[stride];

    for (int y = 0; y < height; y++) {
        unsigned char* row0 = pixels[y == 0 ? y : y - 1];
        unsigned char* row1 = pixels[y];
        unsigned char* row2 = pixels[y == height - 1 ? y : y + 1];

        if (y == 0)
            row0 = row1;

        if (y == height - 1)
            row2 = row1;

        unsigned char* dest = tmp[y];

        for (int i = 0; i < stride; i++) {
            int col0 = i - channels;
            int col1 = i;
            int col2 = i + channels;

            if (i < channels)
                col0 = col1;

            if (i >= stride - channels)
                col2 = col1;

            dest[i] = (row0[col0] + row0[col1] + row0[col2]
                    + row1[col0] + row1[col1] + row1[col2]
                    + row2[col0] + row2[col1] + row2[col2]) / 9;
        }
    }

    /* Replace pixels in m_pixels with blurred ones. */
    for (int i = 0; i < height; i++) {
        delete[] pixels[i];
        pixels[i] = tmp[i];
    }

    delete[] tmp;

}

Blur::~Blur() {
}

/* vim: set ts=4 sw=4 tw=79 ft=cpp et :*/
