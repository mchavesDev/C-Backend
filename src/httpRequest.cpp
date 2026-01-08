#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>
#include <sstream>
#include <string.h>


class httpRequest
{
    
public:
    std::string Request[3];
    std::string Host;
    std::map<std::string, std::string> Headers;

    httpRequest(char buffer[],int totalBytes)
    {
        int i = 0;
        int z = 0;
        int phase = 0;
        // int fullRequestIndex = 0;
        std::stringstream splicedRequest;
        
        while (z <= totalBytes - 2)
        {
            i=z;
            while (buffer[i] !='\r')
            {
                splicedRequest << buffer[i];
                i++;
            }
            if (z==0)
            {
                this->setRequest(splicedRequest.str());
                phase = 1;
                splicedRequest.str(std::string());
            }
            else if(phase == 1 && z > 0)
            {
                this->setHost(splicedRequest.str());
                splicedRequest.str(std::string());
                phase = 2;
            }
            z=i+2;
        }
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
    // void setHeaders(std::string headers)
    // {
    //     this->Headers = headers;
    // }
    
};