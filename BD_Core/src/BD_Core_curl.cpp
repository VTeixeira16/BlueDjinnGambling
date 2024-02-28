#include "stdio.h" //Vai sumir conforme usarmos o padrão de CPP
#include "curl.h"
#include "BD_Core_curl.hpp"

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

// Função para fazer a solicitação HTTP para o endpoint da API em localhost
int verificarAPI() {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        // Configura a URL para o endpoint da API em localhost
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8000/seu_endpoint");

        // Configura o timeout para a solicitação (opcional)
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

        // Realiza a solicitação HTTP GET
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            std::cerr << "Erro ao realizar a solicitação HTTP: " << curl_easy_strerror(res) << std::endl;

        // Sempre limpe depois de usar
        curl_easy_cleanup(curl);
    }
    return 0;
}
