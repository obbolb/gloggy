#include "base.h"
#include "third_party/glad.c"

GLuint gl_create_program(Arena* arena, const char *vert_shader_path,
                         const char *frag_shader_path) {
    TempArena temp_arena = start_temp_arena(arena);

    GLuint frag_shader, vert_shader, program;
    //load shader
    vert_shader = glCreateShader(GL_VERTEX_SHADER);
    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* vert_shader_src = platform_read_file(temp_arena.arena, vert_shader_path);
    const char* frag_shader_src = platform_read_file(temp_arena.arena, frag_shader_path);
    glShaderSource(vert_shader, 1, &vert_shader_src, NULL);
    glShaderSource(frag_shader, 1, &frag_shader_src, NULL);

    //check for shader compilation errors
    i32 success;
    glCompileShader(vert_shader);
    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(vert_shader, 512, NULL, log);
        printf("vert shader = %s", log);
    }
    glCompileShader(frag_shader);
    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
            char log[512];
            glGetShaderInfoLog(frag_shader, 512, NULL, log);
            printf("frag shader = %s", log);
    }

    program = glCreateProgram();
    glAttachShader(program, vert_shader);
    glAttachShader(program, frag_shader);
    glLinkProgram(program);
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

    end_temp_arena(temp_arena);
    return program;

}
