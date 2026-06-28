// [h] includes
#include "base.h"
#include "platform/platform.h"
#include <time.h>

#define STB_IMAGE_IMPLEMENTATION
#include "third_party/stb_image.h"

// [c] includes
#include "base.c"
#include "platform/linux_platform.c"
#include "r_gl.c"

#define KB(n) n * (1 << 10)

int main() {
    Arena* main_arena = arena_alloc(KB(5));

    platform_window* window = platform_create_window(main_arena, 800, 600);
    platform_load_gl_functions();

    glViewport(0, 0, 800, 600);

    GLfloat vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    GLuint indices[] = {
    0,1,2,
    0,2,3
    };

    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat)*3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat)*6));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    i32 width, height, stride;
    u8* image = stbi_load("container.jpg", &width, &height, &stride, 0);
    ASSERT(image && "failed to load image");
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)image);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free((void*)image);

    GLuint program = gl_create_program(main_arena, "code/shader/shader.vert", "code/shader/shader.frag");

    //main loop
    while (!platform_window_should_close(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        //(NOTE): bind texture before using a program
        glBindTexture(GL_TEXTURE_2D, tex);
        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        platform_swap_buffers(window);
    }

}
