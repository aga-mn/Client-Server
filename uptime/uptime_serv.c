#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BACKLOG		5
#define MAX_BUFFER		128

void HandleClient (int connectionFd);

int main ( int argc, char *argv[])
{
  int serverFd, connectionFd;
  struct sockaddr_in servaddr;
  int uptimePort;
  

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
    exit(1);  }
    
  uptimePort=atoi(argv[1]);

  serverFd = socket(AF_INET, SOCK_STREAM, 0);

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(uptimePort);

  if((bind(serverFd, (struct sockaddr *)&servaddr, sizeof(servaddr)))==-1) {perror("bind(): "); exit(1);}
  if((listen(serverFd, MAX_BACKLOG))<0)  {perror("listen(): ");exit(1);} 
 

  while ( 1 ) {

    connectionFd = accept(serverFd, (struct sockaddr *)NULL, NULL);
    if (connectionFd >= 0) {
      HandleClient(connectionFd);
    }
  }
}
void HandleClient(int connectionFd)
{
  char uptimebuffer[MAX_BUFFER+1];
	
	FILE *uptime;
	
	//popen - tworzy proces potomny i uruchamia polecenie (uptime), tworzy potok i zwraca strukturę FILE 
	//mamy dostęp do wyjścia generowanego przez polecenie
	
	uptime = popen("uptime", "r");
	fgets(uptimebuffer, sizeof (uptimebuffer), uptime);
	pclose(uptime);

	write(connectionFd, uptimebuffer, sizeof(uptimebuffer));
	close(connectionFd);
}

