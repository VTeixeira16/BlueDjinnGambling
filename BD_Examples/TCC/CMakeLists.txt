SET(EXAMPLE_NAME "TCC_IMPACTA")

add_executable(${EXAMPLE_NAME} main.cpp)

add_custom_command(TARGET ${EXAMPLE_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_SOURCE_DIR}/shaders" "${BD_OUT}/shaders"
                COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${BD_OUT}/resources"
)

target_link_libraries(${EXAMPLE_NAME} PUBLIC BD_Graph)