#include "Filter.h"
#include <iostream>

unsigned char* Filter::get_pixel(const int pos, unsigned char** pixels) const {
    return pixels[pos];
}

unsigned char* Filter::get_pixel(const int x, const int y, unsigned char** pixels) const {
    return &pixels[x][y];
}

void Filter::set_rgba(int pos, unsigned char new_value, unsigned char* pixel) const {
    pixel[pos] = new_value;
}

void Filter::replace_pixels(unsigned char** old_pixels, unsigned char** new_pixels, const int size) const {
    for (int i = 0; i < size; i++) {
        delete[] old_pixels[i];
        old_pixels[i] = new_pixels[i];
    }

    delete[] new_pixels;
}

int Filter::clamp(const int rgba_value) const {
    return std::min(std::max(rgba_value, min_rgba_value), max_rgba_value);
}

Filter::~Filter() {
}

/* vim: set ts=4 sw=4 tw=79 ft=cpp et :*/
