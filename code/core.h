typedef int8_t S8;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef U8 B8;
typedef U16 B16;
typedef U32 B32;
typedef U64 B64;

#define function static

#define MemoryCopy(dst, src, size) (memmove((dst), (src), (size)))
#define MemorySet(dst, byte, size) (memset((dst), (byte), (size)))
#define MemoryCompare(a, b, size) (memcmp((a), (b), (size)))
#define MemoryStrlen(s) (strlen(s))

#define MemoryCopyArray(dst, src, count) (MemoryCopy((dst), (src), sizeof(*(dst)) * (count)))
#define MemoryCopyStruct(dst, src) (MemoryCopyArray((dst), (src), 1))

#define MemoryZero(dst, size) (MemorySet((dst), 0, (size)))
#define MemoryZeroArray(dst, count) (MemoryZero((dst), sizeof(*(dst)) * (count)))
#define MemoryZeroStruct(dst) (MemoryZeroArray((dst), 1))

#define MemoryMatch(a, b, size) (MemoryCompare((a), (b), (size)) == 0)

#define Assert(b)                                                                                  \
	if (!(b))                                                                                  \
	{                                                                                          \
		__builtin_debugtrap();                                                             \
	}
