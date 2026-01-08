#include <iostream>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <string.h>


class httpRequest
{
public:
    std::string Request[3];
    std::string Host;
    std::string Headers;
    httpRequest(){}

    std::string transformBuffer (char *buffer)
    {
        
        int i = 0;
        // int fullRequestIndex = 0;
        std::stringstream splicedRequest;

        if(sizeof(&buffer)>0){
            while (i <= 1024 && buffer[i] !='\r')
            {
                splicedRequest << buffer[i];

                i++;
            }
        }
        this->setRequest(splicedRequest.str());
        
    }

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