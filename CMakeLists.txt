cmake_minimum_required(VERSION 3.10)
project(my-amx C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -DDEBUG")

# Detect if building for OpenWrt
if(DEFINED ENV{STAGING_DIR})
    message(STATUS "Cross-compiling for OpenWrt")
    set(STAGING_DIR $ENV{STAGING_DIR})
    set(AMX_INCLUDE_DIRS ${STAGING_DIR}/usr/include)
    set(AMX_INCLUDE_DIRS ${AMX_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include_priv)
    set(AMX_LIBRARIES
        ${STAGING_DIR}/usr/lib/libamxs.so
        ${STAGING_DIR}/usr/lib/libamxo.so
        ${STAGING_DIR}/usr/lib/libamxb.so
        ${STAGING_DIR}/usr/lib/libamxd.so
        ${STAGING_DIR}/usr/lib/libamxrt.so
        ${STAGING_DIR}/usr/lib/libamxc.so
        ${STAGING_DIR}/usr/lib/libamxm.so
        ${STAGING_DIR}/lib/libsahtrace.so
    )
else()
    message(STATUS "Native or Docker build")
    set(AMX_INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/include_priv
    )
    set(AMX_LIBRARIES
        -lamxc -lamxb -lamxrt -lamxo -lamxd -lamxm -lsahtrace
    )
endif()


# Pass variables to sub-CMake
add_subdirectory(src)



# Optional subdirectory (optional if exists)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/mod-custom")
    add_subdirectory(mod-custom)
endif()
