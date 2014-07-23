#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <errno.h>

#define BUFLEN 512
#define UNIXOWA 2208988800UL

void err(char *s)
{
    perror(s);
    exit(1);
}


int main(int argc, char** argv)
{
 int sockfd;
unsigned short port;
struct sockaddr_in serv_addr;
int slen=sizeof(serv_addr);

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
 
   
        if (sendto(sockfd, NULL, 0, 0, (struct sockaddr*)&serv_addr, slen)<0)
            {        err("sendto()"); exit(1);                                    }
         
   
else {
        int odp;
struct sockaddr_in         cli_addr;
unsigned int slen; slen=sizeof(cli_addr);
int i=0;
    char buf[BUFLEN];
        
        errno = (int)NULL;
        
        while(1)
        {
                odp=recvfrom(sockfd, &buf, BUFLEN, MSG_DONTWAIT, (struct sockaddr*)&cli_addr, &slen);
                                              
                if (odp==-1)
                {
                        
                        if (errno == EAGAIN) //zasob tymczasowo niedostepny
                        {
                                
                                
                                if (i==3) //probujemy 3 razy
                                {
                                        fprintf(stderr, "Czas minal. Brak odpowiedzi serwera\n"); exit(1);
                                }
                                
                                fprintf(stdout, "Brak odpowiedzi. Ponawiam probe\n");
                                
                                        sleep(1);  
                                        i++;
                                }
                                
                                else {perror("recvfrom()"); exit(1);}//inny blad
                        
                        }
                else break;
                
        }
        
        
   time_t tmp=ntohl(atoi(buf));
   time_t nowy=tmp-UNIXOWA;
      
    fprintf(stdout,"%s",ctime(&nowy));
        
        }

    close(sockfd);
    return 0;
}
