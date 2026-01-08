#include <iostream>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h> // Needed for socket creating and binding
#include <netinet/in.h> // Needed to use struct sockaddr_in
#include <arpa/inet.h>
#include <thread>
#include <vector>
#include <sstream>
#include "src/httpRequest.cpp"

constexpr int MAX_EVENTS = 1024;
constexpr int MAX_CLIENTS = 1024;
constexpr int PORT = 8080;
using namespace std;

// Function to handle client connections
void handleClient(int clientFd)
{
    char buffer[1024] = "";
    std::stringstream response; //temp
    std::unique_ptr<httpRequest> request;
    response << "HTTP/1.1 200 OK\r\n";//temp
    response << "Content-Length: 39\r\n"; // Length of the HTML content//temp
    response << "Content-Type: text/html\r\n";//temp
    response << "\r\n";//temp
    while (true)
    {

        int bytesRead = read(clientFd, buffer, sizeof(buffer));
        if (bytesRead >= 0)
        {
            request = std::make_unique<httpRequest>(buffer);
            std::cout << buffer << std::endl;
        
            response << "<html><body><h1>"<< request->Request[1] <<"</h1></body></html>";//temp
            write(clientFd, response.str().c_str(), response.str().length());
            break;
        }
            
       
    }
    close(clientFd);
}

int main()
{
    int serverFd, epollFd;
    struct epoll_event event, events[MAX_EVENTS];
    struct sockaddr_in serverAddress;
    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd == -1)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)))
    {
        std::cerr << "Failed to bind socket" << std::endl;
        close(serverFd);
        return 1;
    }
    if (listen(serverFd, MAX_CLIENTS) == -1)
    {
        std::cerr << "Failed to listen socket" << std::endl;
        close(serverFd);
        return 1;
    }

    // Create epoll instance

    epollFd = epoll_create1(0);
    if (epollFd == -1)
    {
        std::cerr << "Failed to create epoll instance" << std::endl;
        close(serverFd);
        return 1;
    }

    // Add server socket to epoll

    event.events = EPOLLIN;
    event.data.fd = serverFd;
    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, serverFd, &event) == -1)
    {
        std::cerr << "Failed to add server socket to epoll instance" << std::endl;
        close(serverFd);
        close(epollFd);
        return 1;
    }

    std::cout << "Server started, listening on port " << PORT << std::endl;
    while (true)
    {
        int numEvents = epoll_wait(epollFd, events, MAX_EVENTS, -1);
        if (numEvents == -1)
        {
            std::cerr << "Failed to wait for events" << std::endl;
            break;
        }
        for (int i = 0; i < numEvents; i++)
        {
            if (events[i].data.fd == serverFd)
            {
                // accept new client
                struct sockaddr_in clientAddress;
                socklen_t clientAddrressLength = sizeof(clientAddress);
                int clientFd = accept(serverFd, (struct sockaddr *)&clientAddress, &clientAddrressLength);
                if (clientFd == -1)
                {
                    std::cerr << "Failed to accept client connection" << std::endl;
                    continue;
                }
                // add new client socket to epoll
                event.events = EPOLLIN;
                event.data.fd = clientFd;
                if (epoll_ctl(epollFd, EPOLL_CTL_ADD, clientFd, &event) == -1)
                {
                    std::cerr << "Failed to add client socket to epoll instance" << std::endl;
                    close(clientFd);
                    continue;
                }
                // Create a new thread to handle the client connection
                // std::thread clientThread(handleClient, clientFd);
                // clientThread.detach();
                handleClient(clientFd);
            }
            else
            {
                // Handle client data
                int clientFd = events[i].data.fd;
                // std::thread clientThread(handleClient, clientFd);
                // clientThread.detach();
                handleClient(clientFd);

            }
        }
    }
    close(serverFd);
    close(epollFd);
    return 0;
}