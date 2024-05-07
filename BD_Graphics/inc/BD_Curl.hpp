#ifndef BD_CORE_CURL_HPP
#define BD_CORE_CURL_HPP

#include <iostream>

//#ifdef __cplusplus
//extern "C" {
//#endif

#define CURL_GET        0
#define CURL_POST       1
#define CURL_UPDATE     2
#define CURL_DELETE     3

typedef struct{
    std::string url;
}BD_CURL_ST;

int realizarSolicitacaoHTTP(const char *endpoint, const std::string& tipoSolicitacao, const std::string& corpoSolicitacao);
int verificarAPI(const char *endpoint, int typeRequisition, const char *body);





//#ifdef __cplusplus
//}
//#endif

#endif // BD_CORE_CURL_HPP
