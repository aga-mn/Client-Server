#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER 128

void uptime(int connectionFd);

int main (int argc, char *argv[])
	{
	int connectionFd;
	int port;
	struct sockaddr_in servaddr;

	if (argc !=3)
		{
		fprintf(stderr,"użycie: %s <adres ip serwera> <port serwera uptime>\n",
		argv[0]);
		exit(1);
		}

	port=atoi(argv[2]);
	
	connectionFd = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);

	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	connect(connectionFd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	uptime(connectionFd);

  	return(0);
	}

void uptime(int connectionFd)
	{
	int in;
	char buffer[MAX_BUFFER+1];
	
	while ((in = read(connectionFd, buffer, MAX_BUFFER)) > 0)
		{
		buffer[in] = 0;
		printf("%s", buffer);
		}
	
	close(connectionFd);
	}

  
