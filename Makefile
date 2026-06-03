BUILD_DIR ?= build
BUILD_TYPE ?= Release

all: lemon configure build

configure:
	@cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

build: configure
	@cmake --build $(BUILD_DIR)

rebuild: clean_build all

test: BUILD_TYPE = Test
test: configure build
	build/tests/json-128-test $(ARGS)

build_lemon:
	@$(CC) tools/lemon.c -o tools/lemon

lemon: build_lemon
	tools/lemon tools/lemon-parser.y -Ttools/lempar.c -dsrc -l -p -s

clean_build:
	@cmake --build $(BUILD_DIR) --target clean

clean:
	rm -rf $(BUILD_DIR) && rm -f tools/json.h tools/json.c tools/json.out src/lemon-parser.*

.PHONY: all clean clean_build configure build test rebuild build_lemon lemon
