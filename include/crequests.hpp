#pragma once

#include <string>
#include <map>

namespace crequests {

    class Response {
    public:
        std::string text;       //  response body
        long status_code;       //  status code
        std::map<std::string, std::string> headers;     //  headers  

        Response(std::string t, long sc, std::map<std::string, std::string> h)
            : text(t), status_code(sc), headers(h) {}
    };

    class Request {
    public:
        static Response get(const std::string& url, const std::map<std::string, std::string>& headers = {});
        static Response post(const std::string& url, const std::string& data, const std::map<std::string, std::string>& headers = {});
    };

}  // namespace crequests