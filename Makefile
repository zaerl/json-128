BUILD_DIR ?= build
BUILD_TYPE ?= Release

all: configure build

configure:
	@cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

build: configure
	@cmake --build $(BUILD_DIR)

rebuild: clean_build all

test: BUILD_TYPE = Test
test: configure build
	build/tests/json-128-test $(ARGS)

clean_build:
	@cmake --build $(BUILD_DIR) --target clean

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean clean_build configure build test rebuild
