set(LIB_NAME BD_Graph)

add_library(${LIB_NAME} src/BD_Graphics.cpp ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src/glad.c)
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

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

