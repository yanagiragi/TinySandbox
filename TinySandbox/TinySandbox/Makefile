all: main

CC=g++
OUT=a.out
INCLUDE_DIR=includes
FLAGS=-I${INCLUDE_DIR} -lglfw -ldl --std=c++11
OBJS= glad.o TinySandbox.o GraphicsAPI.o

main: $(OBJS)
	$(CC) -o $(OUT) $^ $(FLAGS)

%.o: %.cpp
	$(CC) -c -o $@ $< $(FLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(FLAGS)

.PHONY: clean

clean:
	rm -f $(OUT) *.o
