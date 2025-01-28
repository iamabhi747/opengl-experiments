SOURCES = main.cpp $(wildcard src/*.cpp)

CC = g++
OBJS = $(addprefix build/, $(SOURCES:.cpp=.o))

CFLAGS = --std=c++17 -arch arm64 \
	-I/opt/homebrew/Cellar/glfw/3.4/include \
	-I/opt/homebrew/Cellar/glew/2.2.0_1/include \
	-Iinclude
LDFLAGS = -L/opt/homebrew/Cellar/glfw/3.4/lib \
	-L/opt/homebrew/Cellar/glew/2.2.0_1/lib \
	-lglfw -lglew -framework OpenGL

TARGET = ./build/main

all: $(TARGET)
	$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

build/%.o: %.cpp $(wildcard include/*.h)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@