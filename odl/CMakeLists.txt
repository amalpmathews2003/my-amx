install(
    DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/"
    DESTINATION "/etc/amx/${PROJECT_NAME}"
    FILES_MATCHING
        PATTERN "*.odl"
    PATTERN "CMakeLists.txt" EXCLUDE
    PATTERN "CMakeFiles" EXCLUDE
    PATTERN "*.cmake" EXCLUDE
)