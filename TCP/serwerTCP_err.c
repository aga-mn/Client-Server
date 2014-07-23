#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BACKLOG		5
#define MAX_BUFFER		128

void HandleClient(int connectionFd);

int main ( int argc, char *argv[])
{
  int serverFd, connectionFd;
  struct sockaddr_in servaddr;
  int daytimePort;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
    exit(1);
  }
  daytimePort=atoi(argv[1]);

  if((serverFd = socket(AF_INET, SOCK_STREAM, 0))<0) {perror("socket()");exit(1);};

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(daytimePort);

  if ((bind(serverFd, (struct sockaddr *)&servaddr,sizeof(servaddr)))<0)
  {perror ("bind()");exit(1);}

  if (listen(serverFd, MAX_BACKLOG)<0){perror("listen()");exit(1);};

  while ( 1 ) {

if ((connectionFd = accept(serverFd, (struct sockaddr *)NULL, NULL))<0)
{perror("accept()");exit(1);}
    else{
      HandleClient(connectionFd);
    }  }}

void HandleClient(int connectionFd)
{
  char timebuffer[MAX_BUFFER+1];
  time_t currentTime;
  currentTime = time(NULL);
  snprintf(timebuffer, MAX_BUFFER, "%s\n", ctime(&currentTime));
 if(( write(connectionFd, timebuffer, strlen(timebuffer)))<0){perror("write()");exit(1);}
  close(connectionFd);
}

