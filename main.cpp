#include <iostream>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h> // Needed for socket creating and binding
#include <netinet/in.h> // Needed to use struct sockaddr_in
#include <thread>
#include <sstream>
#include "headers/httpRequest.h"
#include "headers/router.h"
#include <chrono>

#include "headers/controller.h"
#include "headers/httpResponse.h"
#include "headers/modelPqxx.h"

constexpr int MAX_EVENTS = 1024;
constexpr int MAX_CLIENTS = 1024;
constexpr int PORT = 8081;
// Function to handle client connections
void handleClient(int clientFd)
{
    char buffer[1024] = "";
    std::unique_ptr<httpRequest> request;
    std::unique_ptr<httpResponse> response;
    while (true)
    {

        ssize_t bytesRead = read(clientFd, buffer, sizeof(buffer));
        if (bytesRead > 0)
        {
            //auto start = std::chrono::high_resolution_clock::now();
            //for (int i = 0; i < 1000; i++)
            request = std::make_unique<httpRequest>(buffer,bytesRead);

            // int statusCode = parseRequest(request);

            response = std::make_unique<httpResponse>(parseRequest(request),*request);

            //auto end = std::chrono::high_resolution_clock::now();
            //chrono::duration<double> elapsed_seconds = end - start;

            //std::cout << elapsed_seconds.count() << endl;
            std::cout << buffer << std::endl;
            const std::string stringifyedResponse = (stringifyResponse(*response)).str();
            write(clientFd, stringifyedResponse.c_str(), stringifyedResponse.length());
            
        }
        break;

       
    }
    close(clientFd);
}

int main()
{
    epoll_event event, events[MAX_EVENTS];
    sockaddr_in serverAddress;

    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd == -1)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverFd, reinterpret_cast<struct sockaddr *>(&serverAddress), sizeof(serverAddress)))
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

    int epollFd = epoll_create1(0);
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
    try {
        std::cout << "Server started, listening on port " << PORT << std::endl;
        while (true) {
            int numEvents = epoll_wait(epollFd, events, MAX_EVENTS, -1);
            if (numEvents == -1) {
                std::cerr << "Failed to wait for events" << std::endl;
                break;
            }
            for (int i = 0; i < numEvents; i++) {
                if (events[i].data.fd == serverFd) {
                    // accept new client
                    struct sockaddr_in clientAddress;
                    socklen_t clientAddressLength = sizeof(clientAddress);
                    int clientFd = accept(serverFd, reinterpret_cast<struct sockaddr *>(&clientAddress),
                                          &clientAddressLength);
                    if (clientFd == -1) {
                        std::cerr << "Failed to accept client connection" << std::endl;
                        continue;
                    }
                    // add new client socket to epoll
                    event.events = EPOLLIN;
                    event.data.fd = clientFd;
                    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, clientFd, &event) == -1) {
                        std::cerr << "Failed to add client socket to epoll instance" << std::endl;
                        close(clientFd);
                        continue;
                    }
                    // Create a new thread to handle the client connection
                    //std::thread clientThread(handleClient, clientFd);
                    //clientThread.detach();

                    handleClient(clientFd);

                } else {
                    // Handle client data
                    int clientFd = events[i].data.fd;
                    //std::thread clientThread(handleClient, clientFd);
                    //clientThread.detach();
                    handleClient(clientFd);
                }
            }
        }
        close(serverFd);
        close(epollFd);
        return 0;
    }catch (std::exception& e) {
        close(serverFd);
        close(epollFd);
        std::cerr << e.what();
    };
}