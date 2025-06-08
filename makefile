# CTetris++ Makefile
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2
DEBUG_FLAGS = -std=c++20 -Wall -Wextra -g -DDEBUG

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Files
MAIN_FILE = main.cpp
EXECUTABLE = $(BUILD_DIR)/out
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
.PHONY: all clean debug run help install

all: $(EXECUTABLE)

# Create build directories if they don't exist
$(BUILD_DIR) $(OBJ_DIR):
	mkdir -p $@

# Build executable
$(EXECUTABLE): $(OBJ_DIR)/main.o | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo "✅ Build complete! Run with: ./$(EXECUTABLE)"

# Build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Debug build
debug: CXXFLAGS = $(DEBUG_FLAGS)
debug: clean $(EXECUTABLE)
	@echo "🐛 Debug build complete!"

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)/obj $(EXECUTABLE)
	@echo "🧹 Cleaned build artifacts"

# Clean everything
distclean: clean
	rm -rf $(BUILD_DIR)
	@echo "🧹 Cleaned all build files"

# Run the game
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Run with custom board size
run-custom: $(EXECUTABLE)
	@echo "Enter board width and height (e.g., 15 30):"
	@read width height; ./$(EXECUTABLE) $$width $$height

# Install to system (optional)
install: $(EXECUTABLE)
	cp $(EXECUTABLE) /usr/local/bin/ctetris
	@echo "🎮 CTetris++ installed to /usr/local/bin/ctetris"

# Help target
help:
	@echo "CTetris++ Build System"
	@echo "======================="
	@echo "Available targets:"
	@echo "  all        - Build the game (default)"
	@echo "  debug      - Build with debug symbols"
	@echo "  clean      - Remove build artifacts"
	@echo "  distclean  - Remove all build files"
	@echo "  run        - Build and run the game"
	@echo "  run-custom - Build and run with custom board size"
	@echo "  install    - Install to system PATH"
	@echo "  help       - Show this help message"
	@echo ""
	@echo "Examples:"
	@echo "  make              # Build the game"
	@echo "  make run          # Build and run"
	@echo "  make debug        # Debug build"
	@echo "  make clean        # Clean build files"

