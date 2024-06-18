# Compiler
CC = g++

# Compiler version
CVERSION = -std=c++20
# Compiler flags
CFLAGS = -I/opt/homebrew/include/GLFW -I/opt/homebrew/include/GL   

# Linker flags
LDFLAGS = -L/opt/homebrew/lib -lGLEW -lglfw -framework OpenGL

# Target executable name
TARGET = rend_test

# Source file(s)
SRCS = src/*.cpp

# Rule to build the target
$(TARGET): $(SRCS)
	@$(CC) $(CVERSION) -o $(TARGET)  $(SRCS) $(CFLAGS) $(LDFLAGS)

# Rule to run the program
run: $(TARGET)
	@./$(TARGET)

# Rule to clean the build (removes the executable)
clean:
	rm -f $(TARGET)

# Phony targets are not real files
.PHONY: clean run
