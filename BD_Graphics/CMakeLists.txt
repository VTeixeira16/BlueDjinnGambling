set(LIB_NAME BD_Graph)


set(BD_GRAPHICS_SRC_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BD_GRAPHICS_INC_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(BD_GRAPHICS_SHADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)

set(CURL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/curl/include/curl)
#set(CURL_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/deps/curl/lib)
set(CURL_DLL ${CMAKE_CURRENT_SOURCE_DIR}/deps/curl/bin/libcurl-x64.dll)

set(FREETYPE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype/include)
#set(FREETYPE_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype/lib/x64)
set(FREETYPE_DLL ${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype/bin/x64/freetype.dll)

file(GLOB BD_GRAPHICS_SOURCES ${BD_GRAPHICS_SRC_DIR}/*.c ${BD_GRAPHICS_SRC_DIR}/*.cpp)
file(GLOB BD_GRAPHICS_HEADERS ${BD_GRAPHICS_INC_DIR}/*.h ${BD_GRAPHICS_INC_DIR}/*.hpp)
file(GLOB BD_GRAPHICS_SHADERS ${BD_GRAPHICS_SHADERS_DIR}/*.glsl ${BD_GRAPHICS_SHADERS_DIR}/*.vs ${BD_GRAPHICS_SHADERS_DIR}/*.fs)


add_library(${LIB_NAME} ${BD_GRAPHICS_SOURCES} ${BD_GRAPHICS_HEADERS} ${BD_GRAPHICS_SHADERS} ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src/glad.c)
target_include_directories(${LIB_NAME} PUBLIC ${BD_GRAPHICS_INC_DIR} ${CURL_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIR})

if(WIN32)
    target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/deps/glm
                                                ${CMAKE_CURRENT_SOURCE_DIR}/deps/stb
                                                ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/include
                                                ${CMAKE_CURRENT_SOURCE_DIR}/deps/glew/include
                                                ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include
                                                )

    target_link_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/lib-mingw-w64
                                            ${CMAKE_CURRENT_SOURCE_DIR}/deps/glew/lib/Release/x64
                                            ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src
                                            )

    target_link_libraries(${LIB_NAME} PUBLIC glfw3.lib
                                            glew32.lib
                                            opengl32.lib
                                            ${CURL_DLL} #avaliar necessidade
                                            ${FREETYPE_DLL}
                                            )

    add_custom_command(TARGET ${LIB_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/deps/glew/bin/Release/x64/glew32.dll" "${CMAKE_BINARY_DIR}/glew32.dll"
                    COMMAND ${CMAKE_COMMAND} -E copy "${CURL_DLL}" "${CMAKE_BINARY_DIR}/libcurl-x64.dll"
                    COMMAND ${CMAKE_COMMAND} -E copy "${FREETYPE_DLL}" "${CMAKE_BINARY_DIR}/freetype.dll"
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
                                      OpenGL::OpenGL
                                      ${CURL_DLL})
endif()

