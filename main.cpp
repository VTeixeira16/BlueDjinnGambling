#include "BD_Graphics.hpp"
#include "BD_Core.hpp"

#include <iostream>


int main(){

    BD_CURL_ST BD_curlRequisition;

    BD_curlRequisition.url = "https://openai.com";

    BD_Core_teste();
    BD_Core_curl_get(BD_curlRequisition.url);
    BD_Graphics_Teste();

    return 0;
}
