LIBS = -lGL -lglfw -lGLEW -lm
CFLAGS = -Iinclude
SRCS = $(wildcard source/*.c) $(wildcard source/*.cpp) # All C and CPP files
SHSRCS = $(wildcard source/*.glsl) # All shader files
OBJS = $(patsubst source/%.cpp, bin/%.o, $(patsubst source/%.c,bin/%.o,$(SRCS))) bin/shaders.o # All the objects that are needed for main

default: test

#All object files
bin/main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o bin/main

bin/main.o: source/main.c
		$(CC) $(CFLAGS) -c source/main.c -o bin/main.o

# % is like a wildcard. $< is first prerequisite. $@ is the target.
bin/%.o: source/%.c include/%.h
	$(CC) $(CFLAGS) -c $< -o $@

bin/opengl_rendering.o: source/opengl_rendering.c include/opengl_rendering.h include/shaders.h
	$(CC) $(CFLAGS) -c $< -o $@

bin/%.o: source/%.cpp include/%.h
	$(CXX) $(CFLAGS) -c $< -o $@

bin/shaders.o: $(SHSRCS)
	ld -r -b binary -o bin/shaders.o $(SHSRCS)

test: bin/main
	bin/main

clean:
	rm bin/*.o
