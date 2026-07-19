#ifndef GLOGGY_BASE_H_
#define GLOGGY_BASE_H_

////////////////////////////////
// context cracking

#if defined(__gnu_linux__)
#define OS_LINUX 1
#elif defined(_WIN32) || defined(_WIN64)
#define OS_WINDOWS 1
#endif

#if defined(__GNUC__)
#define COMPILER_GCC 1
#elif defined(__CLANG__)
#define COMPILER_CLANG 1
#elif defined(_MSC_VER)
#define COMPILER_MSVC 1
#endif

// set undefined macros to 0
#if !defined(OS_LINUX)
#define OS_LINUX 0
#endif
#if !defined(OS_WINDOWS)
#define OS_WINDOWS 0
#endif
#if !defined(COMPILER_GCC)
#define COMPILER_GCC 0
#endif
#if !defined(COMPILER_CLANG)
#define COMPILER_CLANG 0
#endif
#if !defined(COMPILER_MSVC)
#define COMPILER_MSVC 0
#endif

////////////////////////////////
// basic types
#include <stdint.h>
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef u8 b8;
typedef u32 b32;
typedef float f32;
typedef double f64;

#define false 0
#define true 1

#define KB(n) n * (1 << 10)
#define MB(n) KB(n) * (1 << 10)
#define GB(n) MB(n) * (1 << 10)

////////////////////////////////
// constants
f32 pi32 = 3.1415926535897f;

////////////////////////////////
// math functions
#include <math.h>
#define sin_f32(r) sinf(r)
#define sin_f64(r) sin(r)
#define cos_f32(r) cosf(r)
#define cos_f64(r) cos(r)

////////////////////////////////
// utils
#if COMPILER_GCC || COMPILER_CLANG
#define Alignof(t) __alignof__(t)
#endif

#define DebugBreak() (*((volatile u8*)0) = 0)
#define Assert(expr)                                                                               \
  do {                                                                                             \
    if (!(expr)) {                                                                                 \
      log_error("%s : assertion failed at line %d in %d", #expr, __LINE__, __FILE__);              \
      DebugBreak();                                                                                \
    }                                                                                              \
  } while (0)

#define align_forward(ptr, b) ((((u64)ptr) + (b - 1)) & ~(b - 1))

////////////////////////////////
// arenas
typedef struct Arena {
  u8* buffer;
  u64 used;
  u64 capacity;
} Arena;

Arena* arena_alloc(u64 size);
void* arena_push_align(Arena* arena, u64 push_size, u64 alignment);

#define DEFAULT_ALIGNMENT sizeof(void*)

#define arena_push(arena, size) arena_push_align(arena, size, DEFAULT_ALIGNMENT)
#define arena_push_array(arena, type, num)                                                         \
  (type*)arena_push_align(arena, sizeof(type) * num, Alignof(type))
#define arena_push_struct(arena, struct)                                                           \
  (struct*)arena_push_align(arena, sizeof(struct), Alignof(struct))

typedef struct TempArena {
  Arena* arena;
  u64 save_point;
} TempArena;

TempArena temp_arena_start(Arena* arena);
void temp_arena_end(TempArena temp_arena);

////////////////////////////////
// logging
typedef enum LogLevel {
  LOG_LEVEL_ERROR,
  LOG_LEVEL_INFO,
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_COUNT
} LogLevel;

void _log(LogLevel level, const char* fmt, ...);
#define log_error(fmt, ...) _log(LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__);
#define log_info(fmt, ...) _log(LOG_LEVEL_INFO, fmt, ##__VA_ARGS__);
#define log_debug(fmt, ...) _log(LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__);

////////////////////////////////
// file I/O : per_os_impl

// returns ptr to buf contaning file contents
// get buffer length by specifying a u64 ptr to read_len
u8* read_file(Arena* arena, const char* file_path, u64* buf_len, b8 null_terminated);

#endif // GLOGGY_BASE_H_
