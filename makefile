default: main

LIBS = -lGL -lglfw -lglut -lGLEW
main: main.o
  $(CC) main.o $(LIBS) -o main
  
main.o: main.c
  $(CC) -c main.c -o main.o
