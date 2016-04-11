#ifndef shaders_h
#define shaders_h
#include <stdint.h>

/*
  The following is a trick to compile binary files into code.
  `ld -r -b binary -o shaders.o shader.glsl` formats shader.glsl as an object
  that can be linked and then referenced by extern _binary_FILENAME_start etc.
*/
extern const char _binary_source_vertex_glsl_start[];
extern const char _binary_source_vertex_glsl_size;
extern const char _binary_source_vertex_glsl_end[];

extern const char _binary_source_fragment_glsl_start[];
extern const char _binary_source_fragment_glsl_size;
extern const char _binary_source_fragment_glsl_end[];

#endif
