#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define WIN#@_LEAN_AND_MEAN
#define buffer_size 256
#define PORT 5000
#define IP 127.0.0.1

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


int takeInput(char *message){
  fgets(message, buffer_size+1, stdin);
  return strlen(message);
}
void clear(char *arr, int size){
  for(int i = 0; i < size, i++){
    arr[i] = '\0';
  }
}


int main(){
  WSADATA wsaData;
  SOCKET socket = INVALID_SOCKET;
  struct sockaddr_in serverAddr;
  char message[buffer_size];
  int iResult;

  if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
    printf("WSAStartup failed");
    return 1;
  }
   
//create socket
  if((c_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVLAID_SOCKET){
    printf("socket creation failed");
    WSACleanup();
    return 1;
  }

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  if(inet_pton(AF_INET, serverIP, &serverAddr.sin_addr) <= 0){
    printf("invalid address");
    closesocket(c_socket);
    WSACleanup();
    return 1;
  }

//connet to server
  if(connect(c_socket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == SOCKET_ERROR){
    printf("server connection failed");
    closesocket(c_socket);
    WSACleanup();
    return 1;
  }


  while(true){
    int size = takeInput(message);
    char *buffer = malloc(size);

    if((iResult = send(c_socket, size, 4, 0)) == SOCKET_ERROR){
      printf("size send failed");
      closesocket(c_socket);
      WSACleanup();
      return 1;
    }
    if((iResult = send(c_socket, message, size, 0)) == SOCKET_ERROR){
      printf("message send failed");
      closesocket(c_socket);
      WSACleanup();
      return 1;
    }
    if((iResult = recv(c_socket, buffer, buffer_size, 0)) > 0){
      buffer[iResult] = '\0';
      printf("revered message: %s", buffer);
    }else if(iResult == 0){
      printf("connection closed");
      return 0;
    }else{
      printf("recieve failed");
      closesocket(c_socket);
      WSACleanup();
      return 1;
    }
    clear(message, size);
    free(buffer);
    buffer = NULL;
  }

}
