#include "Filter.h"

unsigned char* Filter::get_pixel(const int pos, unsigned char** pixels) const {
    return pixels[pos];
}

int Filter::clamp(const int rgba_value) const {
    return std::min(std::max(rgba_value, min_rgba_value), max_rgba_value);
}

Filter::~Filter() {
}

/* vim: set ts=4 sw=4 tw=79 ft=cpp et :*/
