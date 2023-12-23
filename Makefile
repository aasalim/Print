BUILD_GENERATOR= "Ninja"
BUILD_TYPE ?= Debug

BUILD_DIR_X86 ?= build_x86

# Defaults to building the project
all: coverage

# Configure poetry
configure:
	@export CTEST_OUTPUT_ON_FAILURE=1
	poetry install

# Configure x86 CMake
configure_x86: configure
	@cmake -G $(BUILD_GENERATOR) \
	-S . \
	-B $(BUILD_DIR_X86) \
	-DCMAKE_TOOLCHAIN_FILE=cmake/GCC_LINUX_Toolchain.cmake \
	-DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

# Build
build: configure_x86
	@cmake --build $(BUILD_DIR_X86) --config $(BUILD_TYPE)

# Coverage
coverage: test
	@cmake --build $(BUILD_DIR_X86) --target coverage

# Unit Tests
test: build
	@cmake --build $(BUILD_DIR_X86) --target test

# Clean build directory
clean:
	@echo Cleaning build directory...
	@rm -rf $(BUILD_DIR_X86)
	@echo Cleaned!

# Clean build directory and clear terminal
clear:
	@echo Cleaning build directory...
	@rm -rf $(BUILD_DIR_X86)
	@clear
	@echo Cleared!
