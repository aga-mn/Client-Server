#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>

#define BUFLEN 512
#define UNIXOWA 2208988800

void err(char *str)
{
    perror(str);
    exit(1);
}

time_t mytime();

int main(int argc, char* argv[])
{
    struct sockaddr_in my_addr, cli_addr;
    int sockfd; 
    socklen_t slen=sizeof(cli_addr);
    char buf[BUFLEN];
    char timebuf[BUFLEN];
    unsigned short port;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
      err("socket");
    //else       printf("Server : Socket() successful\n");

 
 if (argc!=2)
 {fprintf(stderr, "Usage: %s <UDP SERVER PORT>/n", argv[0]); exit(1);}
 port=atoi(argv[1]);
 
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_addr.sin_port=htons(port);
    
    if (bind(sockfd, (struct sockaddr* ) &my_addr, sizeof(my_addr))==-1)
      err("bind(): ");
 //   else       printf("Server : bind() successful\n");

    while(1)
    {
        if (recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen)==-1)
            err("recvfrom()");
   
           printf("Received packet from %s:%d\nData: %s\n\n",
               inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buf);
      
  snprintf(timebuf, BUFLEN, "%ld\n", mytime());
   
    if (sendto(sockfd, timebuf, BUFLEN, 0, (struct sockaddr*)&cli_addr, slen)==-1)
            err("sendto()");
      }

    close(sockfd);
    return 0;
}

time_t mytime()
{
time_t currentTime;
	currentTime = time(NULL);
	time_t tmp=currentTime+UNIXOWA;
		
return htonl(tmp);	
}

