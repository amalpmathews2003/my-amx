cmake_minimum_required(VERSION 3.10)
project(mod-custom C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(AMX_LIBRARIES -lamxc -lamxb -lamxrt -lamxo -lamxd -lamxm)

include_directories(
   ${PROJECT_SOURCE_DIR}/include_priv
)

add_library(
    mod-custom SHARED
    src/mod-custom.c
)

target_link_libraries(mod-custom ${AMX_LIBRARIES})
