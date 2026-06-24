##
# Project Title
#
# @file
# @version 0.1

CXX = /usr/bin/x86_64-w64-mingw32-g++
CXX_FLAGS = -Wall -Wextra

windows:*.cpp
	$(CXX) $(CXX_FLAGS) *.cpp -o gloggy -mwindows -static

# end
