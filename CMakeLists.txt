cmake_minimum_required(VERSION 3.10)
project(my_tool)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add a library from the 'lib' directory
add_subdirectory(lib)

# Add the 'src' directory as a source directory
add_subdirectory(src)

# Specify the include directories
include_directories(include)

# Link the 'my_tool' executable against the 'my_lib' library
target_link_libraries(my_tool PRIVATE my_lib)