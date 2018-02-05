/*

Computer Networks - Assignment 1

Server End C Code for Data Transfer through Sockets

compile as gcc -o server server.c

run as  ./server <port number>

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
  perror(msg);
  exit(1);
}

int main(int argc, char const *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "Port number not provided.\n Program Terminated!");
    exit(1);
  }

  char buffer1[1024] = {0};

  int sockfd, newsockfd, portno, n;
  char buffer[255];

  struct sockaddr_in serv_addr, cli_addr;
  socklen_t clilen;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0)
  {
    error("Error opening socket");
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));

  portno = atoi(argv[1]);

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    error("Binding Failed!");
  }

  listen(sockfd, 5);

  clilen = sizeof(cli_addr);

  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

  if (newsockfd < 0)
  {
    error("Error on Accept!");
  }

  printf("Client is connected!\n");

// Value read for request file 
  int valread = read( newsockfd , buffer1, 1024);

// File Opened
  FILE *text;text = fopen('./Data/'+buffer1, "rb");

// Loop for sending file in packets
  while(1)
  {
    int cw = fread(buffer, 1, 255, text);

    if(cw > 0){
      printf("Sending!\n");
      write(newsockfd, buffer, cw);
    }

    if (cw < 255){
        if (feof(text)) printf("End of file\n");
        if (ferror(text)) printf("Error reading\n");
        break;
    }
  }

  close(newsockfd);sleep(1);
  close(sockfd);
  return 0;
}