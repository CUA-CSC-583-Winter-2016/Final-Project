LIBS = -lGL -lglfw -lGLEW
CFLAGS = -Iinclude
SRCS = $(wildcard source/*.c) # All C files
SHSRCS = $(wildcard source/*.glsl) # All shader files
OBJS = $(patsubst source/%.c,bin/%.o,$(SRCS)) bin/shaders.o # All the objects that are needed for main

default: test

#All object files
bin/main: $(OBJS) bin/shaders.o
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o bin/main

bin/main.o: source/main.c
		$(CC) $(CFLAGS) -c source/main.c -o bin/main.o

# % is like a wildcard. $< is first prerequisite. $@ is the target.
bin/%.o: source/%.c include/%.h
	$(CC) $(CFLAGS) -c $< -o $@

bin/shaders.o: $(SHSRCS)
	ld -r -b binary -o bin/shaders.o $(SHSRCS)

test: bin/main
	bin/main

clean:
	rm bin/*.o
