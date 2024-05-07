SET(EXAMPLE_NAME "BD_DEV")

add_executable(${EXAMPLE_NAME} main.cpp)

add_custom_command(TARGET ${EXAMPLE_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_SOURCE_DIR}/BD_Graphics/shaders" "${BD_OUT}/shaders"
                COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_SOURCE_DIR}/BD_Graphics/resources" "${BD_OUT}/resources"
)

target_link_libraries(${EXAMPLE_NAME} PUBLIC BD_Graph)