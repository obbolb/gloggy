#include "base.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// arenas
Arena* arena_alloc(u64 size) {
  Arena* result;
  u8* buffer = (u8*)malloc(size);
  Assert(buffer);
  //  TODO: assert buffer
  result           = (Arena*)buffer;
  result->used     = 0;
  result->capacity = size;
  result->buffer   = buffer + sizeof(Arena);
  return result;
}

void* arena_push_align(Arena* arena, u64 push_size, u64 alignment) {
  u64 memory_left = arena->capacity - arena->used;
  if (memory_left < push_size) {
    //  TODO: Growable arenas
    Assert(!"Arena is full");
  }
  else {
    u8* result         = arena->buffer + arena->used;
    u8* aligned_result = (u8*)align_forward(result, alignment);
    arena->used        = (aligned_result - arena->buffer);
    return result;
  }
}

TempArena temp_arena_start(Arena* arena) {
  TempArena result;
  result.arena      = arena;
  result.save_point = arena->used;
  return result;
}

void temp_arena_end(TempArena temp_arena) {
  (temp_arena.arena)->used = temp_arena.save_point;
}

// logging
void _log(LogLevel level, const char* fmt, ...) {
  static const char* msg_prefix[LOG_LEVEL_COUNT] = {"[ERROR] : ", "[INFO] : ", "[DEBUG] : "};
  char msg[512];

  va_list args;
  va_start(args, fmt);
  vsnprintf(msg, 512, fmt, args);
  va_end(args);

  fprintf(stderr, "%s%s\n", msg_prefix[level], msg);
}
