#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define PORT 5000

#pragma comment(lib, "ws2_32.lib")


char* reverse(char *arr, int size){
  char *reversed = malloc(size);
  for(int i = size-1; i > -1; i--){
    *reversed = arr[i];
    reversed++;
  }
  return reversed - size;
 }


bool endCheck(char *arr){
  char check[3] = {'d','n','e'};
  for(int i = 0; i < 3; i++){
    if(check[i] != arr[i]){
      return false;
    }
  }
  return true;
}

int main(){
  WSADATA wsaData;
  SOCKET s_socket = INVALID_SOCKET, c_socket = INVALID_SOCKET;
  struct sockaddr.in serverAddr, clientAddr;
  int clientAddrLen = sizeof(clientAddr);
  int size;

  if (WSAStartup(MAKEWORD(2,2), &wsaData)!= 0){
    printf("WSAStartup failed");
    return 1;
  }

  if((s_socket = socket(AF_INET, SOCKSTREAM, IPPROTO_TCP)) == INVALID_SOCKET){
    printf("socket creation failed");
    WSACleanup();
    return 1;
  }

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(PORT);

  if(bind(s_socket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == SOCKET_ERROR){
    printf("binding failed");
    closesocket(s_socket);
    WSACleanup();
    return 1;
  }

  if(listen(s_socket, 3) == SOCKET_ERROR){
    printf("listen failed");
    closesocket(s_socket);
    WSACleanup();
    return 1;
  }
  
  if((c_socket = accept(s_socket, (struct sockaddr) &clientAddr, &clientAddrLen)) == INVALID_SOCKET){
    printf("accept failed");
    closesocket(s_socket);
    closesocket(c_socket);
    WSACleanup();
    return 1;
  }
  
  while(true){
    if((recSize = recv(clientSocket, size, 4,0)) < 0){
      printf("size recieve failed");
      closesocket(s_socket);
      closesocket(c_socket);
      WSACleanup();
      return 1;
    }
    char *buffer = malloc(size);
    if((recSize = recv(c_socket, buffer, size, 0)) < 0){
      printf("message recieve failed");
      closesocket(s_socket);
      closesocket(c_socket);
      WSACleanup();
      return 1;
    }
    char *reversed = reverse(buffer, size);
    if((iResult = send(c_socket, reversed, size, 0)) == SOCKET_ERROR){
      printf("send failed");
      closesocket(s_socket);
      closesocket(c_socket);
      WSACleanup();
      free(buffer);
      return 1;
    }
    if(size == 3 && endCheck(reversed)){
      closesocket(s_socket);
      closesocket(c_socket);
      WSACleanup();
      free(buffer);
      free(reversed);
      return 0;
    }
    free(buffer);
    free(reversed);
    reversed = NULL;
    buffer = NULL;
  }

}
