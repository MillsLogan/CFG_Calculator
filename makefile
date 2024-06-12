CC = g++
CFLAGS = -g -Wall -std=c++20 -Wc++20-extensions
DEPFLAGS = -MMD -MP

# Define directories
SRCDIR = src
BUILDDIR = build
INCDIR = src  # Assuming headers are alongside source files in src and its subdirectories

# Find all source files in the src directory and its subdirectories
SRC = $(shell find $(SRCDIR) -name '*.cpp')

# List of object files in the build directory, maintaining the directory structure
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRC))

# List of dependency files in the build directory
DEPS = $(OBJ:.o=.d)

# Executable name
EXEC = calculator

# Default target: build the executable
all: $(BUILDDIR) $(EXEC)

# Rule to link the object files into the executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)  # Ensure the directory exists
	$(CC) $(CFLAGS) $(DEPFLAGS) -I$(INCDIR) -c $< -o $@

# Include the dependency files
-include $(DEPS)

# Ensure the build directory exists
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Clean up the build artifacts
clean:
	rm -f $(EXEC) $(OBJ) $(DEPS)
	rm -rf $(BUILDDIR)

# Phony targets
.PHONY: all clean
