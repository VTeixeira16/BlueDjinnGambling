#include "stdio.h" //Vai sumir conforme usarmos o padrão de CPP
#include "curl.h"
#include "BD_Curl.hpp"

int BD_Core_curl_get(std::string url){
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      // Desabilita a verificação do certificado SSL
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

      /* Perform the request, res will get the return code */
      res = curl_easy_perform(curl);
      /* Check for errors */
      if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
      /* always cleanup */
      curl_easy_cleanup(curl);
    }
    return 0;
}

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *data) {
    data->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Função para fazer a solicitação HTTP para o endpoint da API em localhost
int verificarAPI(const char *endpoint) {
    CURL *curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, endpoint);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Realiza a solicitação HTTP GET
        res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            std::cerr << "Erro ao realizar a solicitação HTTP: " << curl_easy_strerror(res) << std::endl;
        }else {
            // Imprimindo a resposta da API
            std::cout << "Resposta da API: " << response << std::endl;
        }
        // Sempre limpe depois de usar
        curl_easy_cleanup(curl);
    }
    return 0;
}
