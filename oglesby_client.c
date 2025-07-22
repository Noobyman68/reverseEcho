#include <sys/socket.h>
#include <stdlib.h>
#include <unitstd.h>
#include <stdio.h>
#include <arpa/init.h>
#include <stdint.h>
#include <string.h>
#define PORT 5000
#define fail() exit(EXIT_FAILURE)
#define bufferSize 256

char* takeInput(){
  char buffer[bufferSize];
  fget(buffer, bufferSize, stdin);
  return buffer;
}


int main(){
  int status, client_fd;
  struct sockaddr_in serv_addr;
  

  if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("Socket client creation error\n");
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
    printf("Invalid address/ Address not supported\n");
    return -1;
  }

  if((status = connect(client_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr))) < 0){
    printf("Connection Failed\n");
    return -1;
  }
  
  while(true){
    char *message = takeInput();
    uint8_t size = sizeof(message); //sizeof(char) = 1
    //send size of next message
    send(client_fd, size, sizeof(size), 0);

    //send message
    send(client_fd, message, size, 0);

    char *buffer = malloc(size);
    byteNum = recv(client_fd,buffer, size,0);

    free(message);
    message = NULL;

    for(int i = 0; i < size; i++){
      printf(buffer[i]);
    }
    printf("\n");
    if(strEqual(buffer)){
      break;
    }
  }
  close(client_fd);
  return 0;
}
