#include <iostream>
#include "Image.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <filename> <filter>\n";
        return false;
    }

    Image img(argv[1]);
    
    img.read_image();
    img.apply_filter(argv[2]);
    img.display_image("Image display");
    img.write_image();

    return 0;
}
/* vim: set ts=4 sw=4 tw=79 ft=cpp et :*/
