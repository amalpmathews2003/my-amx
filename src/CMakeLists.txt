cmake_minimum_required(VERSION 3.10)
project(my-amx C)

set(STAGING_DIR /home/voldermort/amal/prpl/prplos/staging_dir/target-x86_64_musl)
set(AMX_INCLUDE_DIRS ${STAGING_DIR}/usr/include
                   
)
set(AMX_LIBRARIES ${STAGING_DIR}/usr/lib/libamxs.so
                  ${STAGING_DIR}/usr/lib/libamxo.so
                  ${STAGING_DIR}/usr/lib/libamxb.so
                  ${STAGING_DIR}/usr/lib/libamxd.so
                  ${STAGING_DIR}/usr/lib/libamxrt.so
)  

add_executable(my-amx
            main.c
    )

target_include_directories(my-amx PRIVATE ${AMX_INCLUDE_DIRS}
    # ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(my-amx ${AMX_LIBRARIES})

add_library(my-amxl SHARED my-amx.c 
    my-amx.h my-amx-methods.c
    my-amx-methods.h
)
target_include_directories(my-amxl PRIVATE ${AMX_INCLUDE_DIRS})
target_link_libraries(my-amxl ${AMX_LIBRARIES})


install(TARGETS my-amx DESTINATION bin)
