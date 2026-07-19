##
# Project Title
#
# @file
# @version 0.1

CC = /usr/bin/g++
CC_FLAGS = -Wall -Wextra -g 

run: code/*.cpp
	$(CC) $(CC_FLAGS) code/main_glfw.cpp -o gloggy -Icode/third_party/glad/include -lglfw -lGL -lm && ./gloggy


# end
