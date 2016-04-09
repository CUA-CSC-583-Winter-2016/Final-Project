LIBS = -lGL -lglfw -lGLEW
CFLAGS = -Iinclude
SRCS = $(wildcard source/*.c)
OBJS = $(patsubst source/%.c,bin/%.o,$(SRCS))

default: test

#All object files
bin/main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o bin/main

bin/main.o: source/main.c
		$(CC) $(CFLAGS) -c source/main.c -o bin/main.o

# % is like a wildcard. $< is first prerequisite. $@ is the target.
bin/%.o: source/%.c include/%.h
	$(CC) $(CFLAGS) -c $< -o $@

test: bin/main
	bin/main

clean:
	rm bin/*.o
