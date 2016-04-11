#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

/*
  Creates an opengl window and context.
*/
void create_window();

/*
  Checks if the window should be closed.
  @return 1 when window should be closed, zero otherwise.
*/
int should_close_window();

/*
  Swaps the drawing buffer.
*/
void swap_buffers();

/*
  closes and the window destroyes the opengl context.
*/
void close_window();

#endif
