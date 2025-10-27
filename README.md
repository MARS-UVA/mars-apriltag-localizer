# mars-apriltag-localizer

## Installation

### General

The library needs to be built from source. It implicitly requires the AprilTag
library, and you'll have to make sure the shared library, headers, and CMake
metadata are in your CMake prefix path.

One way to do this is to run the provided `dev_configure.py` script, which will
automatically pull the latest version of the library from GitHub, build it, and
install it in the project directory. You'll then need to build with your prefix
path set to the project path.

While the above is definitely the most automatic, any method will work as long
as you set your prefix path appropriately!
