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

void err(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char** argv)
{
    struct sockaddr_in serv_addr,cli_addr;
    int sockfd, slen=sizeof(serv_addr);
    unsigned int slen2;
    char buf[BUFLEN];
  char buf1[BUFLEN];
     unsigned short port;

    if(argc <3)
    {
      printf("Usage : %s <Server-IP> <PORT>\n",argv[0]);
      exit(1);
    }
    
    port=atoi(argv[2]);
    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
        err("socket");
	
    memset (&serv_addr, 0, slen);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
 
char *tekst=" ";
    
         snprintf(buf, BUFLEN, "%s", tekst);
   
        if (sendto(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&serv_addr, slen)<0)
            {	err("sendto()"); exit(1);	    			}
         

   slen2=sizeof(cli_addr);
        if (recvfrom(sockfd, &buf1, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen2)>0){
			
			
   time_t tmp=ntohl(atoi(buf1));
   time_t nowy=tmp-UNIXOWA;
      
    fprintf(stdout,"%s",ctime(&nowy));
	
   }
	else	
            err("recvfrom()");
      
    close(sockfd);
    return 0;
}
