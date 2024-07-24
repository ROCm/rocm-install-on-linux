# ##############################################################################
# Copyright (c) 2024 Advanced Micro Devices, Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# ##############################################################################

message(STATUS "++++++++++++++++++++++++++++++++++++++")
message(STATUS "Creating for ROCm Offline Installer UI")
message(STATUS "++++++++++++++++++++++++++++++++++++++")

message(STATUS "Script_directory   = " ${SCRIPT_DIRECTORY})
message(STATUS "UI binary location = " ${CMAKE_BINARY_DIR})

# Find ncurses related items
find_package(Curses REQUIRED)
find_library(MENU_LIBRARY menu)

include_directories(${CURSES_INCLUDE_DIR} ${CURSES_INCLUDE_DIR}/ncurses)

file(GLOB SOURCEFILES "src/*.c")

add_executable(rocm_offline_ui ${SOURCEFILES})

# Set the UI version
add_compile_definitions(OFFLINE_VERSION="${VERSION_STRING}")
add_compile_definitions(ROCM_VERSION="${ROCM_VERSION_STRING}")

# UI target settings
target_compile_options(rocm_offline_ui PRIVATE -Wall -Wextra -Werror)
target_link_libraries(rocm_offline_ui ${CURSES_LIBRARIES} ${MENU_LIBRARY})

add_dependencies(rocm_offline_creator rocm_offline_ui)

add_custom_command(TARGET rocm_offline_ui
                  COMMAND echo "Copying to script directory"
                  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/rocm_offline_ui ${SCRIPT_DIRECTORY}/)
