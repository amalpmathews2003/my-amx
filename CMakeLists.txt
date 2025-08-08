cmake_minimum_required(VERSION 3.10)
project(my-amx
    VERSION 1.0
    DESCRIPTION "My AMX Project"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
# Disable compiler-specific extensions
set(CMAKE_C_EXTENSIONS OFF)

# Enable all warnings, treat them as errors
add_compile_options(-Wall -Wextra -Wpedantic -Werror) 

# Define DEBUG for Debug builds
add_compile_definitions($<$<CONFIG:Debug>:DEBUG>) 
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
# Debug flags
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g") 
endif()


if(DEFINED ENV{STAGING_DIR})
    message(STATUS "Cross-compiling for OpenWrt")
else()
    message(STATUS "Native or Docker build")
endif()

set(STAGING_DIR $ENV{STAGING_DIR})

include_directories(
    ${STAGING_DIR}/usr/include
    ${PROJECT_SOURCE_DIR}/include_priv
)
link_directories(
    ${STAGING_DIR}/usr/lib
    ${STAGING_DIR}/lib
)

link_libraries(
    -lamxc -lamxb -lamxrt -lamxo -lamxd -lamxm -lsahtrace
)

add_subdirectory(src)
add_subdirectory(odl)
add_subdirectory(mod-custom)
