# Main executable
add_executable(${PROJECT_NAME} main.c)


set(SOURCES
    my-amx.c
    my-amx-methods.c 
    my-amx-events.c
    my-amx-actions.c
    my-amx-rpc.c
    life-events.c
    htable.c
)

set(LIB_NAME "${PROJECT_NAME}_shared")


add_library(${LIB_NAME} SHARED ${SOURCES})
set_target_properties(${LIB_NAME} PROPERTIES 
    PREFIX "" 
    OUTPUT_NAME ${PROJECT_NAME}
)


install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(TARGETS ${LIB_NAME} LIBRARY DESTINATION lib/amx/${PROJECT_NAME})
