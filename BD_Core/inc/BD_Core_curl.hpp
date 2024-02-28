#ifndef BD_CORE_CURL_HPP
#define BD_CORE_CURL_HPP

#include <iostream>

//#ifdef __cplusplus
//extern "C" {
//#endif

typedef struct{
    std::string url;
}BD_CURL_ST;




int BD_Core_curl_get(std::string url);

//#ifdef __cplusplus
//}
//#endif

#endif // BD_CORE_CURL_HPP
