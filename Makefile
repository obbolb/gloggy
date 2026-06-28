##
# Project Title
#
# @file
# @version 0.1

CC = /usr/bin/gcc
CC_FLAGS = -Wall -Wextra -g 

windows:code/*.c
	$(CC) $(CC_FLAGS) code/gloggy.c -o gloggy -Iinclude -lglfw -lGL -lm

# end
