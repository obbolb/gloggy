##
# Project Title
#
# @file
# @version 0.1

CC = /usr/bin/clang
CC_FLAGS = -Wall -Wextra -g 

run: code/*.c
	$(CC) $(CC_FLAGS) code/main_glfw.c -o gloggy -Icode/third_party/glad/include -lglfw -lGL -lm && ./gloggy


# end
