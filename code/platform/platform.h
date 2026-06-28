#ifndef PLATFORM_H_
#define PLATFORM_H_

typedef struct platform_window platform_window;
//platform window management
//init opengl & double buffered window by defualt
platform_window* platform_create_window(Arena* arena, u32 width, u32 height);
b32 platform_window_should_close(platform_window* window);
void platform_swap_buffers(platform_window* window);
void platform_load_gl_functions();

//platform file I/O
char* platform_read_file(Arena* arena, const char* path);
#endif // PLATFORM_H_
