#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <glad/glad.h>
#include <GL/glx.h>

//(TODO):use native windowing
#include "glfw_window.c"

void platform_load_gl_functions() {
    ASSERT(gladLoadGLLoader((GLADloadproc) glXGetProcAddress) && "failed to load opengl functions");
}

//file i/o
static u64 linux_get_file_size(i32 fd) {
    struct stat file_stat;
    if (fstat(fd, &file_stat) == 0) {
        return (u64)file_stat.st_size;
    }
    return 0;
}

char* platform_read_file(Arena* arena, const char* path) {
    i32 fd = open(path, O_RDONLY);
    ASSERT((fd != -1) && "unable to open file");
    u64 file_size = linux_get_file_size(fd);
    char* result = arena_push(arena, file_size + 1);
    read(fd, result, file_size);
    result[file_size] = '\0';
    return result;
}
