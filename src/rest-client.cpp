#include <curl/curl.h>
#include <iostream>
#include <string>

static size_t writeCallback(void *buffer, size_t size, size_t nitems, void *outstream)
{
    ((std::string *)outstream)->append((char *)buffer, size * nitems);
    return size * nitems;
}

int main()
{
    CURL *handle = curl_easy_init();

    std::string readBuffer;

    if (handle)
    {
        curl_easy_setopt(handle, CURLOPT_URL, "http://localhost:8000");
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode code = curl_easy_perform(handle);

        curl_easy_cleanup(handle);

        std::cout << readBuffer << std::endl;
    }
}
