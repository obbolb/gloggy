#include <GLFW/glfw3.h>

typedef struct platform_window {
    GLFWwindow* window;
} platform_window;

//glfw creates an opengl context for us
platform_window* platform_create_window(Arena* arena, u32 width, u32 height) {
    platform_window* result = arena_push_struct(arena, platform_window);
    ASSERT(glfwInit());
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    result->window = glfwCreateWindow(width, height, "gloggy", NULL, NULL);
    glfwMakeContextCurrent(result->window);
    return result;
}

b32 platform_window_should_close(platform_window* window) {
    return glfwWindowShouldClose(window -> window);
}

void platform_swap_buffers(platform_window* window) {
    return glfwSwapBuffers(window->window);
}
