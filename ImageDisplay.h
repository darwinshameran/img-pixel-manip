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

    SDL_Surface* m_screen;
    SDL_Window* m_window;

    void convert_to_rgba(unsigned char** pixels);

 public:
    ImageDisplay(const std::string& window_title, int width, int height, int channels);
    ~ImageDisplay();
    void display_image(unsigned char** pixels);
};

#endif

/* vim: set ts=4 sw=4 tw=79 ft=cpp et :*/
