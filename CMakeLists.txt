  
cmake_minimum_required (VERSION 2.6)
project (dem)
set (CMAKE_CXX_FLAGS "-Wall")
set (CMAKE_CXX_FLAGS_DEBUG "-g")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")

file(GLOB tutorial_SRC
    "*.h"
    "*.cpp"
)
file(COPY resources DESTINATION .)
file(COPY output DESTINATION .)
add_executable(dem ${tutorial_SRC})
