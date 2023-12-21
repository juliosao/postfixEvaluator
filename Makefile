TARGET=eval
CFLAGS=
LFLAGS=
COMPILER=gcc
LINKER=g++

SOURCES=$(wildcard src/*.cpp)
OBJS=$(patsubst src/%.cpp,obj/%.o,$(SOURCES))

CFLAGS+= -I ./inc -Wfatal-errors
LFLAGS+= -fPIC

.phony: all clean

all: bin/$(TARGET)

clean:
	-rm -rf obj bin

bin/$(TARGET): 	$(OBJS) | bin
	$(LINKER) $(LFLAGS) $(OBJS) -o bin/$(TARGET)

obj/%.o: src/%.cpp Makefile inc/*.h | obj
	$(COMPILER) $(CFLAGS) -c $< -o $@

obj:
	mkdir obj

bin:
	mkdir bin

