include_directories(${AMX_INCLUDE_DIRS})

# Main executable
add_executable(my-amx main.c)
target_link_libraries(my-amx ${AMX_LIBRARIES})


# Shared library
add_library(my-amxl SHARED
    my-amx.c
    my-amx-methods.c 
    my-amx-events.c
    my-amx-actions.c
    my-amx-rpc.c
    life-events.c
    cpu.c
)
target_link_libraries(my-amxl ${AMX_LIBRARIES})
set_target_properties(my-amxl PROPERTIES PREFIX "" OUTPUT_NAME "my-amx")


# Install target for OpenWrt only
if(DEFINED ENV{STAGING_DIR})
    install(TARGETS my-amx DESTINATION bin)
endif()

install(TARGETS my-amx RUNTIME DESTINATION bin)
install(TARGETS my-amxl LIBRARY DESTINATION lib/amx/my-amx)
