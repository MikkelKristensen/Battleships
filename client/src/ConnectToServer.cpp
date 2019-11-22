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
    // WSADATA allows the application to get information from windows about the required socket version, and how to implement it.
    WSADATA wsaData;

    // Setup the socket.
    SOCKET ConnectSocket = -1;

    // addrinfo holds informatio about the host.
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;

    // Setup variables for later.
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    // TODO
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    // Setup hints, which is an addrinfo that will act as a template for what information is returned by getaddrinfo()
    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    // Gets address info from the host, which is localhost. Uses hints to figure out which data to get, and stores it in result.
    iResult = getaddrinfo(DEFAULT_ADDRESS, DEFAULT_PORT, &hints, &result);

    // addrinfo info returnd from getaddrinfo can point to a chain of more addrinfo's, which is useful as 1 host can have multiple IPs.
    // Here we attempt to connect to each returned IP, and will break out of the for-loop when it succeeds.
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

    // Frees up the addrinfo that getaddrinfo has stored in result, as we don't need it anymore.
    freeaddrinfo(result);

    // Variable setup for the game.
    bool canSuper = true;
    bool isPlaying = true;
    bool won;

    while(isPlaying){

        // User input phase. Subtracted by 1 because the user will imagine the topleft corner of the grid being (1,1), while a two dimensional array
        // will see it as (0,0).
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

        // If the user has their super ability, ask them if they want to use it. If they do, set super to 1 and canSuper to false.
        int super = 0;
        if(canSuper){
            cout << "Super (y/n): ";
            string superString;
            cin >> superString;
            if(superString == "y" || superString == "Y"){
                super = 1;
                canSuper = false;
            }
        }

        // The input from the user is stored in integers, but to add them to strings we convert them to characters.
        // This however, converts to ASCII decimals, which converts the range 0-9 to the range 48-57. The thing they have in common
        // is that the difference between numbers is constant. Therefore we simply plus '0' (48) onto the number, which converts it
        // nicely to its' ASCII counterpart. Example: Input is 8, but we need the ASCII code for 8, which is 56. Therefore we plus '0' (48) to 8.
        // resulting in 8 + 48 = 56.
        string msgsend = "";
        msgsend += (char)x + '0';
        msgsend += (char)y + '0';
        msgsend += (char)super + '0';

        // c_str() converts a string into a character array.
        const char *sendbuf = msgsend.c_str();

        // Send the character array to the server.
        iResult = send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );

        // Block the program and wait for data from the server. This data is expected to be a character array from the other client.
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

        // iResult represents the amount of bytes being received. Will be 0 if the connection was closed and no data was received.
        if ( iResult > 0 ){
            // as iResult is the amount of bytes being received, it naturally also represents the length of recvbuf.
            // we set this index to 0 as we want to display this character array as a string, and C strings are null-terminated.
            // if this line isn't added and an attempt to display the character array as a string is made, the string will keep displaying
            // until it finds a NULL character, which is unpredictable.
            recvbuf[iResult] = NULL;

            // char to int converts to ASCII, where 0-9 is 48-57. By subtracting '0' (48), we get the values 1-9.
            int x = recvbuf[0] - '0';
            int y = recvbuf[1] - '0';
            int z = recvbuf[2] - '0';

            bool super;
            if(z == 1) {super = true;}
            if(z == 0) {super = false;}

            // Attack the grid with the other clients input. Returns true on hit and false on miss.
            bool attackHit = grid->attack({x,y}, super);
            system("CLS");
            grid->drawGrid();

            if(attackHit){
                msgsend = "You hit!";
            }
            else{
                msgsend = "You missed!";
            }

            // Check if the grid is empty, changing msgsend to "win" and sends it to the other client to notify it that it has won.
            // Also sets isPlaying to false which means the while-loop wont get another iteration.
            if(grid->hasLost()){
                msgsend = "win";
                isPlaying = false;
                won = false;
            }

            // Turn msgsend into a character array and send it to the server.
            const char *sendbuf = msgsend.c_str();
            iResult = send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );

            // Receive information from the server, signalling whether the attack you sent to the server was a hit or a miss on the other client.
            // Add a null-terminator and display it.
            iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
            recvbuf[iResult] = NULL;
            cout << recvbuf << endl;

            // Check if the incoming message was "win", which we know is only the case if the other client detected a loss.
            // if true, set isPlaying to false, ending the while-loop, and set won to true.
            if(recvbuf[0] == 'w' && recvbuf[1] == 'i' && recvbuf[2] == 'n'){
                isPlaying = false;
                won = true;
            }

        }
        else if ( iResult == 0 ){
            printf("Connection closed\n");
        }
    }

    // This area is reached when isPlaying is false, which is after the game has ended.
    // Check if the client has won or not, and spam an appropriate message.
    if(won){
        while(true){
            cout << "You win!" << endl;
        }
    }
    else{
        while(true){
            cout << "You lose!" << endl;
        }
    }
}
