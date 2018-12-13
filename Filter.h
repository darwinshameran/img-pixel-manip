#ifndef FILTER_H
#define FILTER_H
#include <algorithm>

class Filter {
 protected:
     unsigned char* get_pixel(const int pos, unsigned char** pixels) const;
     void set_rgba(int pos, unsigned char new_value, unsigned char* pixels) const;
     void replace_pixel(unsigned char* old_pixel, unsigned char* pixel, const int y) const;
     
     int clamp(const int rgba_value) const;

 private:
     int min_rgba_value;
     int max_rgba_value;
 
 public:
     Filter(int min_rgba_value, int max_rgba_value)
         : min_rgba_value{min_rgba_value}
         , max_rgba_value{max_rgba_value}
       { }
     virtual ~Filter();
     
     virtual void apply_filter(int width, int height, int channels, unsigned char** pixels) = 0;

};

#endif

/* vim: set ts=4 sw=4 tw=79 ft=cpp et :*/
