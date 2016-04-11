# Final-Project
A system that tracks a head with a kinect and renders geometry on a screen with the correct perspective transform relative to the location of the head.

Header files are in `include` and source code is in `source`.

The running `make` will compile and run a simple hello world like program that will ensure that all required development libraries are installed and are being compiled correctly. It will also fail if code in `source` or `include` has any errors.

## Required packages
*Note:* This should work but hasn't been tested. Update this as necessary.

* Ubuntu: `sudo apt-get install libglfw3-dev libfreenect-dev libglew-dev`
* Fedora: `sudo dnf install glfw-devel libfreenect-devel glew-devel`
