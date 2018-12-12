#ifndef BLUR_H
#define BLUR_H

class Blur {
 public:
     Blur(int width, int height, int channels, unsigned char** pixels);
     ~Blur(); 
};

#endif
/* vim: set ts=4 sw=4 tw=79 ft=cpp et :*/
