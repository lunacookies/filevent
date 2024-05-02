#include "all.h"

function void
MemoryCopy(void *dst, void *src, U64 size)
{
	memmove(dst, src, size);
}

function void
MemorySet(void *dst, U8 byte, U64 size)
{
	memset(dst, byte, size);
}

function void
MemoryZero(void *dst, U64 size)
{
	MemorySet(dst, 0, size);
}

function S32
MemoryCompare(void *dst, void *src, U64 size)
{
	return memcmp(dst, src, size);
}

function B32
MemoryMatch(void *dst, void *src, U64 size)
{
	return MemoryCompare(dst, src, size) == 0;
}

function U64
MemoryNullPosition(void *s)
{
	return strlen(s);
}
