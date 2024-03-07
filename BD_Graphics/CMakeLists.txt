set(LIB_NAME BD_Graph)

set(BD_GRAPHICS_SRC_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BD_GRAPHICS_INC_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(BD_GRAPHICS_SHADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)

file(GLOB BD_GRAPHICS_SOURCES ${BD_GRAPHICS_SRC_DIR}/*.c ${BD_GRAPHICS_SRC_DIR}/*.cpp)
file(GLOB BD_GRAPHICS_HEADERS ${BD_GRAPHICS_INC_DIR}/*.h ${BD_GRAPHICS_INC_DIR}/*.hpp)
file(GLOB BD_GRAPHICS_SHADERS ${BD_GRAPHICS_SHADERS_DIR}/*.glsl ${BD_GRAPHICS_SHADERS_DIR}/*.vs ${BD_GRAPHICS_SHADERS_DIR}/*.fs)


add_library(${LIB_NAME} ${BD_GRAPHICS_SOURCES} ${BD_GRAPHICS_HEADERS} ${BD_GRAPHICS_SHADERS} ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src/glad.c)
target_include_directories(${LIB_NAME} PUBLIC ${BD_GRAPHICS_INC_DIR})

if(WIN32)
    target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/deps/glm
                                                ${CMAKE_CURRENT_SOURCE_DIR}/deps/stb
                                                ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/include
                                                ${CMAKE_CURRENT_SOURCE_DIR}/deps/glew/include
                                                ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include
                                                )

    target_link_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/lib-mingw-w64
                                            ${CMAKE_CURRENT_SOURCE_DIR}/deps/glew/lib/Release/x64
                                            ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src)

    target_link_libraries(${LIB_NAME} PUBLIC glfw3.lib
                                            glew32.lib
                                            opengl32.lib)

    add_custom_command(TARGET ${LIB_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/deps/glew/bin/Release/x64/glew32.dll" "${CMAKE_BINARY_DIR}/glew32.dll"
#                    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/shaders" "${CMAKE_BINARY_DIR}/shaders"
#                    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/res" "${CMAKE_BINARY_DIR}/res"
                    COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_SOURCE_DIR}/shaders" "${CMAKE_BINARY_DIR}/shaders"
                    COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CMAKE_BINARY_DIR}/resources"
    )

else()
    find_package(glfw3 REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(glad REQUIRED)
    #TODO - Necessario validar linkagem GLAD no Linux

    target_include_directories(${LIB_NAME} PRIVATE deps/stb deps/glm)
    target_link_libraries(${LIB_NAME} GLEW::glew
                                     glfw
                                     glad
                                     OpenGL::OpenGL)
endif()

