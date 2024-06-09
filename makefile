# g++ -o sdl_test main.cpp -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE -L/opt/homebrew/lib -lSDL2 && ./sdl_test
# Compiler
CC = g++

# Compiler flags
CFLAGS = -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE

# Linker flags
LDFLAGS = -L/opt/homebrew/lib -lSDL2

# Target executable name
TARGET = sdl_test

# Source file(s)
SRCS = main.cpp input.cpp

# Rule to build the target
$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) $(CFLAGS) $(LDFLAGS)

# Rule to run the program
run: $(TARGET)
	@./$(TARGET)

# Rule to clean the build (removes the executable)
clean:
	rm -f $(TARGET)

# Phony targets are not real files
.PHONY: clean run
