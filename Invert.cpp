#include "Invert.h"

/* Invert colors. */

void Invert::apply_filter(int width, int height, int channels, unsigned char** pixels) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            auto px = get_pixel(i, j * channels, pixels);

            /* Invert each channel (R, G, B(, A)) */
            for (int pos = 0; pos < channels; pos++) {
                set_rgba(pos, (255 - px[pos]), px);
            }
        }
    }
}

Invert::~Invert() {
}

/* vim: set ts=4 sw=4 tw=79 ft=cpp et :*/
