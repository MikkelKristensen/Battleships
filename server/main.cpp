#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x501

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <thread>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define BACKLOG 10

using namespace std;

void threadfunc(SOCKET Client, SOCKET otherClient, string msg){

    // Setup
    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN ];
    int recvbuflen = DEFAULT_BUFLEN;
    int iResult;

    while(true){

        // Block the program, waiting for buffer from client.
        iResult = recv(Client, recvbuf, recvbuflen, 0);

        // If iResult is 0, that means the client closed the connection.
        if (iResult > 0){

            // Make the last index a null, because C uses null terminators when displaying strings.
            recvbuf[iResult] = NULL;

            // Send the input to the other client.
            iSendResult = send(otherClient, recvbuf, (int)strlen(recvbuf), 0);
        }
        else if ( iResult == 0 ){
            printf("Connection closed\n");
        }
    }

}

int main()
{

    // TODO: what the fuck is wsadata.
    WSADATA wsaData;
    int iResult;

    // Set up the sockets.
    SOCKET ListenSocket = -1;
    SOCKET ClientSocket1 = -1;
    SOCKET ClientSocket2 = -1;

    // TODO
    struct addrinfo *result = NULL;
    struct addrinfo hints;

    // TODO
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    // TODO
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // TODO
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

    // TODO
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    // TODO
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);

    // TODO
    freeaddrinfo(result);

    // TODO
    iResult = listen(ListenSocket, BACKLOG);

    // Listen for 2 clients.
    ClientSocket1 = accept(ListenSocket, NULL, NULL);
    ClientSocket2 = accept(ListenSocket, NULL, NULL);


    // Set up the threads, calling function threadFunc and parsing in the arguments.
    thread client1(threadfunc, ClientSocket1, ClientSocket2, "1");
    thread client2(threadfunc, ClientSocket2, ClientSocket1, "2");

    // Close the ListenSocket, as we're not actively listening for more clients.
    closesocket(ListenSocket);

    while(true){
        // This loop makes sure the program doesn't terminate.
    }

    // iResult = shutdown(ClientSocket, 1);

    // closesocket(ClientSocket);
    // WSACleanup();

    return 0;
}
