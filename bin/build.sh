#!/bin/sh

set -e

clang-format -i code/*.c code/*.h

rm -rf build
mkdir build

clang -o build/filevent \
	-I code \
	-g3 \
	-fsanitize=address,undefined \
	-Wl,-sectcreate,__TEXT,__info_plist,data/filevent-Info.plist \
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

cp data/filevent.entitlements build/

# Permit debugging.
/usr/libexec/PlistBuddy -c 'Add :com.apple.security.get-task-allow bool YES' \
	build/filevent.entitlements

codesign \
	--sign - \
	--entitlements data/filevent.entitlements \
	--options runtime build/filevent
