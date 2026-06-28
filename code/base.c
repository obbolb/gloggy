#include <stdlib.h>
//arenas
Arena* arena_alloc(i64 size) {
    Arena* result;
    u8* buffer = (u8*)malloc(size);
    //(TODO): assert buffer
    result = (Arena*) buffer;
    result->used = 0;
    result->capacity = size;
    result->base = buffer + sizeof(Arena);
    return result;
}

void* arena_push(Arena *arena, u64 push_size) {
    u64 memory_left = arena -> capacity - arena -> used;
    if (memory_left < push_size) {
        //(TODO): Growable arenas
        ASSERT(!"Arena is full");
    }
    else {
        void* result = (u8*)arena->base + arena -> used;
        arena->used += push_size;
        return result;
    }
}

TempArena start_temp_arena(Arena *arena) {
    TempArena result;
    result.arena = arena;
    result.save_point = arena->used;
    return result;
}

void end_temp_arena(TempArena temp_arena) {
    (temp_arena.arena)->used = temp_arena.save_point;
}
