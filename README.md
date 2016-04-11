# Final-Project
A system that tracks a head with a kinect and renders geometry on a screen with the correct perspective transform relative to the location of the head.

## Roles
To see everyone's roles, check out the [roles.md](roles.md) file. The file describes which files are related to each role and who is working on each role. 

## Getting started on your role
One or more function prototypes are included within the header file associated with your role. Each function prototype has documentaion on what it should do. Some of the .c files associated with the respctive .h files have some useful links for implementing the function. Please also note: some of the .c files have placeholder functions that return a simple value. For example, currently the `locate_head()` function in [head_tracker.c](source/head_tracker.c) returns the center of the screen 100 units away. Feel free to overwrite them. See [opengl_objects.h](include/opengl_objects.h) and [opengl_objects.c](source/opengl_objects.c) for an example. glhf!

## Compiling
The running `make` will compile and run a simple hello world like program that will ensure that all required development libraries are installed and are being compiled correctly. It will also fail if code in `source` or `include` has any errors.

## Required packages
*Note:* This should work but hasn't been tested. Update this as necessary.

* Ubuntu: `sudo apt-get install libglfw3-dev libfreenect-dev libglew-dev`
* Fedora: `sudo dnf install glfw-devel libfreenect-devel glew-devel`

## File Structure
Header files are in `include` and source code is in `source`.
`include` is passed as an include directory to the compiler so including a file is as simple as `#include "my_beautiful_header.h"`
