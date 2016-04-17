LIBS = -lGL -lglfw -lGLEW -lm -lfreenect
CFLAGS = -Iinclude

default: test

#Object files required for main program.
bin/main: bin/main.o bin/head_tracker.o bin/kinect_interface.o bin/matrix_math.o bin/opengl_rendering.o bin/opengl_window.o bin/shaders.o
	$(CC) $(CFLAGS) bin/main.o bin/head_tracker.o bin/kinect_interface.o bin/matrix_math.o bin/opengl_rendering.o bin/opengl_window.o bin/shaders.o $(LIBS) -o bin/main

bin/head_tracker_unit_test: bin/head_tracker_unit_test.o bin/kinect_interface.o bin/opengl_window.o
	$(CC) $(CFLAGS) bin/head_tracker.o bin/kinect_interface.o bin/opengl_window.o -o bin/head_tracker_unit_test -lGL -lGLEW -lm -lfreenect

head_tracker_unit_test: bin/head_tracker_unit_test
	bin/head_tracker_unit_test

bin/main.o: source/main.c
		$(CC) $(CFLAGS) -c source/main.c -o bin/main.o

# % is like a wildcard. $< is first prerequisite. $@ is the target.
bin/%.o: source/%.c include/%.h
	$(CC) $(CFLAGS) -c $< -o $@

bin/opengl_rendering.o: source/opengl_rendering.c include/opengl_rendering.h include/shaders.h
	$(CC) $(CFLAGS) -c $< -o $@

bin/%.o: source/%.cpp include/%.h
	$(CXX) $(CFLAGS) -c $< -o $@

SHSRCS = $(wildcard source/*.glsl) # All shader files
bin/shaders.o: $(SHSRCS)
	ld -r -b binary -o bin/shaders.o $(SHSRCS)

test: bin/main
	bin/main



clean:
	rm bin/*.o
