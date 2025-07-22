#include <sys/socket.h>
#include <stdlib.h>
#include <unitstd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>
#define PORT 5000
#define fail() exit(EXIT_FAILURE)

char* reverseStr(char *arrIn, int len){
  char *arrNew = malloc(len); //sizeof(char) = 1
  for(int i = len-1, i > -1, i--){
    *arrNew = arrIn[i];
    arrNew++;
  }
  //need to reset arrNew to first address of arr
  return arrNew-len;
}

int strEquals(char *arr){
  char check[3] = {'d','n','e'};
  for(int i = 0; i < 3; i++){
    if(arr[i] != check[i]){
      return 0;
    }
  }
  return 1;
}

int main(){
  int server_fd, new_socket;
  ssize_t byteNum;
  struct sockaddr_in address;
  int opt = 1 
  sockelen_t addrlen = sizeof(address);

//socket functions wrapped in if statements for error checking

//creates IPv4, TCP socket
  if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    perror("socket creation failed");
    fail();
  }

//tells server to occasionally check if connection is still alive  
  if(setsockopt(server_fd, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(opt)) < 0){
    perror("setsockopt failed");
    fail();
  }
  
  address.sin_family = AF_INET; //sets communication to IPv4 to match socket
  address.sin_addr.s_addr = INADDR_ANY; //allows any IP address to connect
  address.sin_port = htons(PORT); //sets port

//attaches socket to port
  if(bind(server_fd, (struct sockaddr*)&address, addrlen) < 0){
    perror("binding failed");
    fail();
  }

//tells socket to wait for connection attempt
  if(listen(server_fd, 2) < 0){
    perror("listen failed");
    fail();
  }


  if((new_socket = accept(server_fd, (struct sockaddr*)&address, *addrlen)) < 0){
    perror("connection failed");
    fail();
  }

  uint8_t msg_len, total;
  while(true){
    //first message is size of data for next message
    recv(new_socket, &msg_len, sizeof(msg_len), 0);
    //msg_len = ntohl(len); //ntohl() converts byte order from network to host

    //msg_len should only be message
    char *buffer = malloc(msg_len);
    while(total < msg_len){
      byteNum = recv(new_socket, buffer + total, msg_len - total,0);
      total += byteNum;
    } 
    char *revStr = reverseStr(buffer, msg_len);
    free(buffer);
    send(new_socket, revStr, msg_len, 0);
    if(msg_len == 3 && strEquals(revStr)){
      free(revStr);
      break;
    }
    free(revStr);
    revStr = NULL;
    buffer = NULL;
  }
  close(server_fd);
  close(new_socket);
  return 0;
}
