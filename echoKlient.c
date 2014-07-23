/*Aplikacja echo
a)
Opracuj klienta standardowej usługi echo w wersji TCP (opis usługi echo jest zawarty w RFC 862 -
www.rfc-editor.org).
Niech korzysta on z serwera echo uruchomionego za pomocą xinetd. Aplikacja ma umożliwiać
wprowadzanie danych przesyłanych do serwera do momentu wygenerowania przez użytkownika końca
pliku (CTRL-D). Dane serwera mają być podawane w postaci nazwy lub adresu IP, nazwy lub portu
usługi. Problemy do rozwiązania: Czy klient powinien od razu wyświetlać otrzymaną część tekstu czy
też czekać na zwrócenie przez serwer całego tekstu? Jak sprawdzić czy klient otrzymał od serwera cały
tekst?
Klient powinien przed próbą połączenia wyświetlić komunikat: "Nawiazywane polaczenie z
adres_IP na porcie numer_Portu ...". W miejscu adres_IP należy wyświetlać
właściwy adres IP, i odpowiednio w miejscu numer_Portu – numer portu.
Po nawiązaniu połączenia należy wyświetlić komunikat: "Polaczenie nawiazano. Wprowadz
tekst."
b) b) Sprawdź działanie klienta przy zablokowanej i odblokowanej usłudze echa na serwerze. Uzupełnij
klienta o obsługę błędów.*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_BUFFER 128
#define ECHO_PORT 7

void echo(int connectionFd);
int init_conecction(int Port, char *IPadress) ;

int main (int argc, char *argv[] )
{
  int port;
 
  if ((argc < 2) || (argc > 3)) {
    fprintf(stderr,"Usage: %s <Server IP>  <Echo Port (7) \n",
            argv[0]);
    exit(1);
  }

  if (argc == 3)
    port=atoi(argv[2]);
  else
    port=ECHO_PORT;

printf("\nNawi'?''?'zywanie po'?''?''?''?'czenie adres %s  port %d \n" ,argv[1],port);


int connectionFd;
struct sockaddr_in servaddr;
  
  connectionFd = socket(PF_INET, SOCK_STREAM, 0);

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);

  servaddr.sin_addr.s_addr = inet_addr(argv[1]);

  if((connect(connectionFd, (struct sockaddr *)&servaddr, 
           sizeof(servaddr)))==-1)
  {
    fprintf(stderr,"Polaczenie nie powiodlo sie: %d\n",errno);
    return errno;
  }


  echo(connectionFd);

  return(0);
}


void echo(int connectionFd)
{
  int cn_send,cn_recive;
  char buffer_send[MAX_BUFFER+1];
  char buffer_recive[MAX_BUFFER+1];
   printf("Wprowadz tekst:");
   
 while (gets(buffer_send))
          {
          
            cn_send=strlen(buffer_send);
          
            write(connectionFd,buffer_send,cn_send);
            cn_recive = read(connectionFd,  buffer_recive, MAX_BUFFER) ; 
            buffer_recive[cn_recive] = 0;
            printf("otrzymano: %s \n wprowadz tekst: ",buffer_recive);

          }
  
  close(connectionFd);
}

