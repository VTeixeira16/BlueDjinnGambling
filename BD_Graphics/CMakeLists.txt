set(LIB_NAME BD_Graph)

set(BD_GRAPHICS_SRC_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BD_GRAPHICS_INC_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(BD_GRAPHICS_SHADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)

set(MINGW_INCLUDE_DIR "C:/msys64/mingw64/include")
set(MINGW_BINARY_DIR "C:/msys64/mingw64/bin") 
set(MINGW_LIBRARY_DIR "C:/msys64/mingw64/lib")

set(FREETYPE_INCLUDE_DIR "${MINGW_INCLUDE_DIR}/freetype2")


file(GLOB BD_GRAPHICS_SOURCES ${BD_GRAPHICS_SRC_DIR}/*.c ${BD_GRAPHICS_SRC_DIR}/*.cpp)
file(GLOB BD_GRAPHICS_HEADERS ${BD_GRAPHICS_INC_DIR}/*.h ${BD_GRAPHICS_INC_DIR}/*.hpp)
file(GLOB BD_GRAPHICS_SHADERS ${BD_GRAPHICS_SHADERS_DIR}/*.glsl ${BD_GRAPHICS_SHADERS_DIR}/*.vs ${BD_GRAPHICS_SHADERS_DIR}/*.fs)


#Avaliar necessidade

#set(CMAKE_PREFIX_PATH 
#    "${CMAKE_PREFIX_PATH}"
#    "${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw"
#)


add_library(${LIB_NAME} ${BD_GRAPHICS_SOURCES} ${BD_GRAPHICS_HEADERS} ${BD_GRAPHICS_SHADERS} ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src/glad.c)
target_include_directories(${LIB_NAME} PUBLIC ${BD_GRAPHICS_INC_DIR} ${MINGW_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIR} ${BOOST_INCLUDE_DIR})

if(WIN32)
    target_include_directories(${LIB_NAME} PUBLIC ${MINGW_INCLUDE_DIR}/glm
                                                ${MINGW_INCLUDE_DIR}/stb
                                                ${MINGW_INCLUDE_DIR}/glfw/include
                                                ${MINGW_INCLUDE_DIR}/glew/include
                                                ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include
                                                )

    target_link_directories(${LIB_NAME} PUBLIC #${GLFW_DIR}
                                            #${CMAKE_CURRENT_SOURCE_DIR}/deps/glew/lib/Release/x64
                                            ${MINGW_LIBRARY_DIR}
                                            ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src
                                            #${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype/lib/x64
                                            )

    target_link_libraries(${LIB_NAME} PUBLIC
                                            glfw3.lib
                                            glew32.lib
                                            opengl32.lib
                                            libcurl.dll.a
                                            freetype.lib
                                            #${CMAKE_CURRENT_SOURCE_DIR}/deps/curl/bin/libcurl-x64.dll
                                            )

    add_custom_command(TARGET ${LIB_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy "${MINGW_BINARY_DIR}/glew32.dll" "${BD_OUT}/glew32.dll"
                    COMMAND ${CMAKE_COMMAND} -E copy "${MINGW_BINARY_DIR}/libfreetype-6.dll" "${BD_OUT}/libfreetype-6.dll"
                    COMMAND ${CMAKE_COMMAND} -E copy "${MINGW_BINARY_DIR}/glfw3.dll" "${BD_OUT}/glfw3.dll"
#                    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/shaders" "${BD_OUT}/shaders"
#                    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/res" "${BD_OUT}/res"
    )

    add_custom_command(TARGET ${LIB_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy "${MINGW_BINARY_DIR}/libcurl-4.dll" "${BD_OUT}/libcurl-4.dll"
    )

else()
    find_package(glfw3 REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(glad REQUIRED)
    #TODO - Necessario validar linkagem GLAD no Linux

    target_include_directories(${LIB_NAME} PRIVATE stb glm)
    target_link_libraries(${LIB_NAME} GLEW::glew
                                      glfw
                                      glad
                                      OpenGL::OpenGL
                                      )
endif()

