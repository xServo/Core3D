# Compiler
CC = g++

# Compiler version
CVERSION = -std=c++20

# Find all subdirectories in vendor and include them
VENDOR_DIRS = $(shell find vendor -type d -print)
INCLUDE_DIRS = $(foreach dir, $(VENDOR_DIRS), -I$(dir))
INCLUDE_DIRS += -I/opt/homebrew/include/GLFW -I/opt/homebrew/include/GL  -Iinclude

# Compiler flags
CFLAGS = 

# Linker flags
LDFLAGS = -L/opt/homebrew/lib -lassimp -lGLEW -lglfw -framework OpenGL

# Target executable name
TARGET = rend_test

# Source file(s)
SRCS = src/*.cpp vendor/imgui/*.cpp  vendor/imgui/backends/imgui_impl_glfw.cpp vendor/imgui/backends/imgui_impl_opengl3.cpp

# Rule to build the target
$(TARGET): $(SRCS)
	@$(CC) $(CVERSION) -o $(TARGET)  $(SRCS) $(INCLUDE_DIRS) $(CFLAGS) $(LDFLAGS)

# Rule to run the program
run: $(TARGET)
	@./$(TARGET)

# Rule to clean the build (removes the executable)
clean:
	rm -f $(TARGET)

# Phony targets are not real files
.PHONY: clean run
