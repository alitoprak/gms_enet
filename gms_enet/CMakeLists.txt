cmake_minimum_required(VERSION 4.4.0)

project(gms_enet)

add_subdirectory("enet")

add_library(gms_enet SHARED "gms_enet.c")
target_link_libraries(gms_enet PRIVATE enet)

if(GMS_ENET_DEV)
    add_custom_command(TARGET gms_enet POST_BUILD
                    COMMAND ${CMAKE_COMMAND}
                            -E copy $<TARGET_FILE:gms_enet>
                                    ${CMAKE_CURRENT_SOURCE_DIR}/..
    )
endif()