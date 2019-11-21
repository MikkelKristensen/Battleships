#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x501

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

#define DEFAULT_ADDRESS "localhost"

using namespace std;

int main()
{
    int y=0;
    WSADATA wsaData;
    SOCKET ConnectSocket = -1;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    iResult = getaddrinfo(DEFAULT_ADDRESS, DEFAULT_PORT, &hints, &result);

    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);

        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == -1) {
            closesocket(ConnectSocket);
            ConnectSocket = -1;
        }else{
            break;
        }
    }
    freeaddrinfo(result);

    //const char *sendbuf = "Hello, Network! This is Battleships, developed by FRAC and Mikkel";
    while(true){
        cin >> ws;
        string msgsend;
        getline(cin, msgsend);
        const char *sendbuf = msgsend.c_str();
        iResult = send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );
        printf("Bytes Sent: %d\n", iResult);

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 ){
            recvbuf[iResult] = NULL;
            printf("Bytes received: %d\n", iResult);
            printf("Message received: %s\n", recvbuf);
        }
        else if ( iResult == 0 ){
            printf("Connection closed\n");
        }
    }

    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}
