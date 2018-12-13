#ifndef INVERT_H
#define INVERT_H
#include "Filter.h"

class Invert : public Filter {
 public:
     Invert(int min_rgba_value, int max_rgba_value)
         : Filter(min_rgba_value, max_rgba_value)
         { }
     virtual ~Invert();

     virtual void apply_filter(int width, int height, int channels, unsigned char** pixels);

};

#endif

/* vim: set ts=4 sw=4 tw=79 ft=cpp et :*/
