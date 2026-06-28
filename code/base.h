#ifndef GLOGGY_BASE_H_
#define GLOGGY_BASE_H_

//basic types
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

#define false 0;
#define true 1;

#define debug_break() (*((volatile u8*)0)= 0)
#define ASSERT(expr) do{if(!expr) {debug_break();}}while(0)

typedef struct Arena {
    void* base;
    u64 used;
    u64 capacity;
} Arena;

Arena* arena_alloc(i64 size);
void* arena_push(Arena *arena, u64 push_size);

#define arena_push_array(arena, type, num) arena_push(arena, sizeof(type) * num)
#define arena_push_struct(arena, struct) arena_push(arena, sizeof(struct))

typedef struct TempArena {
    Arena *arena;
    u64 save_point;
} TempArena;

TempArena start_temp_arena(Arena* arena);
void end_temp_arena(TempArena temp_arena);


#endif // GLOGGY_BASE_H_
