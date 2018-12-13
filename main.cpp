#include <iostream>
#include "Image.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <filename> <filter>\n";
        return false;
    }

    std::string image_fn(argv[1]);
    std::string filter(argv[2]);
    std::string window_title("Image display");

    Image img(image_fn);
    
    img.read_image();

    img.filter(filter);
    img.display_image("Image Display");

    img.write_image();

    return 0;
}
/* vim: set ts=4 sw=4 tw=79 ft=cpp et :*/
