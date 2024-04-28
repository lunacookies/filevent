typedef int8_t S8;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef S8 B8;
typedef S16 B16;
typedef S32 B32;
typedef S64 B64;

#define function static

function void MemoryCopy(void *dst, void *src, U64 size);
function void MemorySet(void *dst, U8 byte, U64 size);
function void MemoryZero(void *dst, U64 size);
function S32 MemoryCompare(void *dst, void *src, U64 size);
function B32 MemoryMatch(void *dst, void *src, U64 size);
function U64 MemoryNullPosition(void *s);

#define MemoryCopyArray(dst, src, count) (MemoryCopy((dst), (src), sizeof(*(dst)) * (count)))
#define MemoryCopyStruct(dst, src) (MemoryCopyArray((dst), (src), 1))
#define MemoryZeroArray(dst, count) (MemoryZero((dst), sizeof(*(dst)) * (count)))
#define MemoryZeroStruct(dst) (MemoryZeroArray((dst), 1))

#define Breakpoint() __builtin_debugtrap()
#define Assert(b) \
	if (!(b)) \
	{ \
		Breakpoint(); \
	}
