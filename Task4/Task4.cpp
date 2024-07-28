#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

const int SERVER_PORT = 8080;
const string DOCUMENT_ROOT = "./static";

void handleClientRequest(int clientSocket)
{
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    read(clientSocket, buffer, sizeof(buffer) - 1);

    istringstream requestStream(buffer);
    string method, path, version;
    requestStream >> method >> path >> version;

    if (path == "/") 
    {
        path = "/index.html";
    }

    string fullPath = DOCUMENT_ROOT + path;

    ifstream file(fullPath);
    if (file) 
    {
        ostringstream contentStream;
        contentStream << file.rdbuf();
        string content = contentStream.str();

        string response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Length: " + to_string(content.size()) + "\r\n";
        response += "Content-Type: text/html\r\n";
        response += "\r\n";
        response += content;

        send(clientSocket, response.c_str(), response.size(), 0);
    }
    else 
    {
        string notFoundResponse = "HTTP/1.1 404 Not Found\r\n";
        notFoundResponse += "Content-Length: 0\r\n";
        notFoundResponse += "Content-Type: text/html\r\n";
        notFoundResponse += "\r\n";

        send(clientSocket, notFoundResponse.c_str(), notFoundResponse.size(), 0);
    }

    close(clientSocket);
}

int main() 
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1) 
    {
        cout << "Error creating server socket." << endl;
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(SERVER_PORT);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) 
    {
        cout << "Binding failed." << endl;
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 10) == -1)
    {
        cout << "Listening failed." << endl;
        close(serverSocket);
        return 1;
    }

    cout << "Server is running on port " << SERVER_PORT << endl;

    while (true) 
    {
        sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);

        if (clientSocket == -1) 
        {
            cout << "Failed to accept client connection." << endl;
            continue;
        }

        thread clientThread(handleClientRequest, clientSocket);
        clientThread.detach();
    }

    close(serverSocket);
    return 0;
}
