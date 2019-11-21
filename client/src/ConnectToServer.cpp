#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x501

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <Grid.h>
#include "ConnectToServer.h"

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

#define DEFAULT_ADDRESS "localhost"

using namespace std;

ConnectToServer::ConnectToServer(Grid * grid)
{
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

    while(true){
        // cin >> ws;

        cout << "X: ";
        int x;
        cin >> x;
        x--;
        cout << endl;

        cout << "Y: ";
        int y;
        cin >> y;
        y--;
        cout << endl;

        cout << "Super? (1/0): ";
        int super;
        cin >> super;
        cout << endl;

        string msgsend = "";
        msgsend += (char)x + '0';
        msgsend += (char)y + '0';
        msgsend += (char)super + '0';

        const char *sendbuf = msgsend.c_str();

        iResult = send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 ){
            recvbuf[iResult] = NULL;

            // char to int converts to ASCII, where 1-9 is 49-57. By subtracting '0' (48), we get the values 1-9.
            int x = recvbuf[0] - '0';
            int y = recvbuf[1] - '0';
            int z = recvbuf[2] - '0';
            bool super;

            if(z == 1) {super = true;}
            if(z == 0) {super = false;}
            grid->attack({x,y}, super);
            system("CLS");
            grid->drawGrid();
        }
        else if ( iResult == 0 ){
            printf("Connection closed\n");
        }
    }
}
