#!/bin/sh

set -e

clang-format -i code/*.c code/*.h

rm -rf build
mkdir build

clang -o build/filevent \
	-I code \
	-g3 \
	-fsanitize=address,undefined \
	-W \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Wconversion \
	-Wimplicit-fallthrough \
	-Wmissing-prototypes \
	-Wshadow \
	-Wstrict-prototypes \
	-Wno-unused-parameter \
	code/entry_point.c
