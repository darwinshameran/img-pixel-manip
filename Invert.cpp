#include "Invert.h"

/* Invert colors. */

Invert::Invert(int width, int height, int channels, unsigned char** pixels) noexcept {
    channels = (channels == 4) ? 3 : channels;
    for (int i = 0; i < height; i++) {
        auto row = pixels[i];

        for (int j = 0; j < width; j++) {
            auto px = &(row[j * channels]);

            /* Invert each channel (R, G, B) */
            for (int x = 0; x < channels; x++) {
                px[x] = (255 - px[x]);
            }
        }
    }
}

Invert::~Invert() {
}

/* vim: set ts=4 sw=4 tw=79 ft=cpp et :*/
