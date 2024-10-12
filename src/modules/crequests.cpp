#include "crequests.hpp"
#include <curl/curl.h>
#include <sstream>

namespace crequests {
    size_t write_callback(void* contents, size_t size, size_t nmemb, std::string* buffer) {
        size_t total_size = size * nmemb;
        buffer->append((char*)contents, total_size);
        return total_size;
    }
    Response perform_request(const std::string& url, const std::string& method, const std::string& data = "", const std::map<std::string, std::string>& headers = {}) {
        CURL* curl;
        CURLcode res;
        std::string response_string;
        std::string header_string;
        long http_code = 0;
        std::map<std::string, std::string> response_headers;

        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            
            if (method == "POST") {
                curl_easy_setopt(curl, CURLOPT_POST, 1L);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
            }

            struct curl_slist* chunk = NULL;
            for (const auto& header : headers) {
                std::string header_str = header.first + ": " + header.second;
                chunk = curl_slist_append(chunk, header_str.c_str());
            }
            if (chunk) {
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
            }

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                curl_easy_cleanup(curl);
                curl_global_cleanup();
                throw std::runtime_error("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
            }

            // Handle HTTP status code
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

            std::istringstream header_stream(header_string);
            std::string header_line;
            while (std::getline(header_stream, header_line) && header_line != "\r") {
                auto delimiter_pos = header_line.find(':');
                if (delimiter_pos != std::string::npos) {
                    std::string key = header_line.substr(0, delimiter_pos);
                    std::string value = header_line.substr(delimiter_pos + 1);
                    response_headers[key] = value;
                }
            }

            // Cleaning
            curl_easy_cleanup(curl);
            curl_slist_free_all(chunk);
        }
        curl_global_cleanup();

        return Response(response_string, http_code, response_headers);
    }

    Response Request::get(const std::string& url, const std::map<std::string, std::string>& headers) {
        return perform_request(url, "GET", "", headers);
    }

    Response Request::post(const std::string& url, const std::string& data, const std::map<std::string, std::string>& headers) {
        return perform_request(url, "POST", data, headers);
    }
}