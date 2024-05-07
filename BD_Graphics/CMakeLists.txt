set(LIB_NAME BD_Graph)

set(BD_GRAPHICS_SRC_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BD_GRAPHICS_INC_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(BD_GRAPHICS_SHADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)

set(CURL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/curl/include)
set(CURL_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/curl/bin)
set(CURL_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/curl/lib)

set(CURL_DLL ${CURL_BINARY_DIR}/libcurl-x64.dll)
set(CURL_LIB ${CURL_LIBRARY_DIR}/libcurl.dll.a)
set(GLFW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/lib-mingw-w64)
set(FREETYPE_DIR_DLL ${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype/bin/lib-mingw-w64/x64)

set(FREETYPE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype/include)
#set(FREETYPE_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype/lib/x64)
set(FREETYPE_DLL ${FREETYPE_DIR_DLL}/freetype.dll)
set(GLFW_DLL     ${GLFW_DIR}/glfw3.dll)


file(GLOB BD_GRAPHICS_SOURCES ${BD_GRAPHICS_SRC_DIR}/*.c ${BD_GRAPHICS_SRC_DIR}/*.cpp)
file(GLOB BD_GRAPHICS_HEADERS ${BD_GRAPHICS_INC_DIR}/*.h ${BD_GRAPHICS_INC_DIR}/*.hpp)
file(GLOB BD_GRAPHICS_SHADERS ${BD_GRAPHICS_SHADERS_DIR}/*.glsl ${BD_GRAPHICS_SHADERS_DIR}/*.vs ${BD_GRAPHICS_SHADERS_DIR}/*.fs)


#Avaliar necessidade

#set(CMAKE_PREFIX_PATH 
#    "${CMAKE_PREFIX_PATH}"
#    "${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw"
#)


add_library(${LIB_NAME} ${BD_GRAPHICS_SOURCES} ${BD_GRAPHICS_HEADERS} ${BD_GRAPHICS_SHADERS} ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src/glad.c)
target_include_directories(${LIB_NAME} PUBLIC ${BD_GRAPHICS_INC_DIR} ${CURL_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIR} ${BOOST_INCLUDE_DIR})

if(WIN32)
    target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/deps/glm
                                                ${CMAKE_CURRENT_SOURCE_DIR}/deps/stb
                                                ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/include
                                                ${CMAKE_CURRENT_SOURCE_DIR}/deps/glew/include
                                                ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include
                                                )

    target_link_directories(${LIB_NAME} PUBLIC ${GLFW_DIR}
                                            ${CMAKE_CURRENT_SOURCE_DIR}/deps/glew/lib/Release/x64
                                            ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src
                                            ${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype/lib/x64
                                            )

    target_link_libraries(${LIB_NAME} PUBLIC
                                            glfw3.lib
                                            glew32.lib
                                            opengl32.lib
                                            ${CURL_LIB}
                                            freetype.lib
                                            #${CMAKE_CURRENT_SOURCE_DIR}/deps/curl/bin/libcurl-x64.dll
                                            )

    add_custom_command(TARGET ${LIB_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/deps/glew/bin/Release/x64/glew32.dll" "${BD_OUT}/glew32.dll"
                    COMMAND ${CMAKE_COMMAND} -E copy "${FREETYPE_DLL}" "${BD_OUT}/freetype.dll"
                    COMMAND ${CMAKE_COMMAND} -E copy "${GLFW_DLL}" "${BD_OUT}/glfw3.dll"
#                    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/shaders" "${BD_OUT}/shaders"
#                    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/res" "${BD_OUT}/res"
    )

    add_custom_command(TARGET ${LIB_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy "${CURL_DLL}" "${BD_OUT}/libcurl-x64.dll"
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
                                      )
endif()

