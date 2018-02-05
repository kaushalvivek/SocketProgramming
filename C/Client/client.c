/*

Computer Networks - Assignment 1

Client End C Code for Data Transfer through Sockets

compile as gcc -o client client.c

run as  ./client localhost <port number> <file to be copied>

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>

void error(const char *msg)
{
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[])
{
  char *hello = argv[3];
  char buffer1[1024] = {0};

  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[255];

  if (argc < 3)
  {
    fprintf(stderr, "Usage %s hostname port.\n", argv[0]);
    exit(1);
  }

  portno = atoi(argv[2]);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0)
  {
    error("Error opening socket!");
  }

  server = gethostbyname(argv[1]);
  if (server == NULL)
  {
    error("Error, No such host!");
  }

  bzero(buffer, 255);
  serv_addr.sin_family = AF_INET;
  bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);

  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    error("Connection Failed!");
  }

  printf("Server is connected!\n");

  send(sockfd , hello , strlen(hello) , 0 );


// User input for filname taken, and file saved
  printf("Enter the file name you want the file to be saved as: \n");
  char filename[100];int cw = 0;
  scanf("%s", filename);
  FILE *text;text = fopen(filename, "ab");

// Error detection for empty file 
  if(NULL == text){
    printf("Error opening file");
    return 1;
  }

// Packets read
  while((cw = read(sockfd, buffer, 255)) > 0){
    fwrite(buffer, 1,cw,text);
  }

  if(cw < 0){
    printf("\n Read Error \n");
  }
  printf("File has been recieved successfully!\n");
  close(sockfd);

  return 0;
}