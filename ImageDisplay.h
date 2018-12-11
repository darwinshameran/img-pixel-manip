#ifndef ImageDisplay_H
#define ImageDisplay_H

#include "SDL2/SDL.h"
#include <cstdlib>
#include <stdexcept>

class ImageDisplay {
 private:
    int m_height;
    int m_width;
    int m_channels;
    int m_pitch;
    unsigned int* m_pixels;
    const char* m_window_title;

    SDL_Surface* m_screen;
    SDL_Window* m_window;

    void convert_to_rgba(unsigned char**);
 public:
    ImageDisplay(const char*, int, int, int);
    ~ImageDisplay();
    void display_image(unsigned char**);
};

#endif

/* vim: set ts=4 sw=4 tw=79 ft=cpp et :*/
