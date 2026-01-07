#include <iostream>
#include <unistd.h>
#include <vector>
#include <sstream>

class httpRequest
{
public:
    std::string Request[3];
    std::string Host;
    std::string Headers;
    void setRequest(std::string request)
    {
        std::stringstream splitRequest(request);
        std::string temp;
        char del = ' ';
        int i = 0;
        while (getline(splitRequest, temp, del))
        {

            this->Request[i] = temp;
            i++;
        }
    }
    void setHost(std::string host)
    {
        this->Host = host;
    }
    void setHeaders(std::string headers)
    {
        this->Headers = headers;
    }
};