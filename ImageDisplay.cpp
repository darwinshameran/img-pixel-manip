#include "ImageDisplay.h"

ImageDisplay::ImageDisplay(const char* window_title, int width, int height, int channels) noexcept(false) {
    m_window_title = window_title;
    m_width = width;
    m_height = height;
    m_channels = channels;

    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        throw std::runtime_error("SDL_Init failed to initialize");
    }

    m_window = SDL_CreateWindow(m_window_title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            m_width, m_height,
            SDL_WINDOW_SHOWN);

    m_screen = SDL_GetWindowSurface(m_window);
}

ImageDisplay::~ImageDisplay() {
}

/* vim: set ts=4 sw=4 tw=79 ft=cpp et :*/
