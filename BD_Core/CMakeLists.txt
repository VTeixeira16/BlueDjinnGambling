

set(CURL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/curl/include/curl)
set(CURL_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/curl/lib)
set(CURL_DLL ${CMAKE_CURRENT_SOURCE_DIR}/curl/bin/libcurl-x64.dll)

#find_package(CURL REQUIRED)
#include_directories(${CURL_INCLUDE_DIR})

#file(GLOB CURL_HEADERS ${CURL_INCLUDE_DIR}/*.h)

add_library(BD_Core STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/BD_Core.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/BD_Core_curl.cpp)
target_include_directories(BD_Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc ${CURL_INCLUDE_DIR})

target_link_libraries(BD_Core PUBLIC ${CURL_DLL})

if(WIN32)
    add_custom_command(TARGET BD_Core POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${CURL_DLL}" "${CMAKE_BINARY_DIR}/libcurl-x64.dll"
    )
endif(WIN32)
