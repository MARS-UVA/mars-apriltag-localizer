//
// Created by Ivan on 1/12/26.
//

#include <fstream>
#include <iostream>

#include "field.hpp"

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cerr << "field file not provided" << std::endl;
        return 1;
    }
    std::ifstream field_file(argv[1]);

    const apriltag::AprilTagField field = apriltag::AprilTagField::parse(field_file);

    std::cout << "Got field " << field.name() << "\n";
}
