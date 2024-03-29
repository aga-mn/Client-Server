#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER 128
#define DAYTIME_SERVER_PORT 13

void daytime(int connectionFd);

int main (int argc, char *argv[] )
{
  int connectionFd;
  int port;
  struct sockaddr_in servaddr;
 
  if ((argc < 2) || (argc > 3)) {
    fprintf(stderr,"Usage: %s <Server IP> [<Daytime Port>]\n",
            argv[0]);
    exit(1);
  }

  if (argc == 3)
    port=atoi(argv[2]);
  else
    port=DAYTIME_SERVER_PORT;

  //connectionFd = socket(PF_INET, SOCK_STREAM, 0);
    if((connectionFd = socket(PF_INET, SOCK_STREAM, 0))<0) {perror("socket()");exit(1);};

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);

  servaddr.sin_addr.s_addr = inet_addr(argv[1]);

  if( connect(connectionFd, (struct sockaddr *)&servaddr, sizeof(servaddr))<0) {perror("connect()");exit(1);}

  daytime(connectionFd);

  return(0);
}
void daytime(int connectionFd)
{
  int in;
  char buffer[MAX_BUFFER+1];
  while ( (in = read(connectionFd, 
                      buffer, MAX_BUFFER)) > 0) {
    buffer[in] = 0;
    printf("\n%s", buffer);
  }
  close(connectionFd);
}
