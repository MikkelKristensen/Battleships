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

void threadfunc(SOCKET ClientSocket, string msg){

    cout << msg << endl;

}

int main()
{

    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = -1;
    SOCKET ClientSocket1 = -1;
    SOCKET ClientSocket2 = -1;


    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN ];
    int recvbuflen = DEFAULT_BUFLEN;
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);

    freeaddrinfo(result);

    iResult = listen(ListenSocket, BACKLOG);

    ClientSocket1 = accept(ListenSocket, NULL, NULL);
    ClientSocket2 = accept(ListenSocket, NULL, NULL);



    thread client1(threadfunc, ClientSocket1, "1");

    thread client2(threadfunc, ClientSocket2, "2");

    closesocket(ListenSocket);

    while(true){

        client1.join();
        client2.join();

    }


    // iResult = shutdown(ClientSocket, 1);

    // closesocket(ClientSocket);
    // WSACleanup();

    return 0;
}
