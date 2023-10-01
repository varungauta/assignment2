# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++14

# Project name and source files
PROJECT_NAME = library_management
SOURCE_FILES = main.cpp UserRegistration.cpp ItemManagement.cpp

# Output executable name
OUTPUT_EXECUTABLE = manage_library

# Build directory
BUILD_DIR = build

# List of object files
OBJECTS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SOURCE_FILES))

# Main build target
$(OUTPUT_EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

# Object file compilation rules
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR) $(OUTPUT_EXECUTABLE)
