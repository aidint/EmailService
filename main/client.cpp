#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string>
using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

bool tasavi(char a[],string x)
{
  for(int i=0;i<x.size();i++)
    if(x[i]!=a[i])
      return 0;
  if(a[x.size()]=='\0' || a[x.size()]=='\n' || a[x.size()]=='\t')
    return 1;
  return 0;
}


int main()
{
  char argv[3][256];
  while(1)
    {
      scanf("%s",argv[0]);
      if(!tasavi(argv[0],"connect"))
	{
	  printf("usage : connect <IP> <port> \n");
	  continue;
	}
      scanf("%s %s\n",argv[2],argv[1]);
      break;
    }
  fflush(stdin);
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[1024];
 


 portno = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) 
    error("ERROR opening socket");
  server = gethostbyname(argv[1]);
  if (server == NULL) {
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, 
	(char *)&serv_addr.sin_addr.s_addr,
	server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    error("ERROR connecting");
  while(1)
    {
      //  printf("Please enter the message: ");
      bzero(buffer,1024);
      fgets(buffer,1023,stdin);
      n = write(sockfd,buffer,strlen(buffer));
      if (n < 0) 
	error("ERROR writing to socket");
      bzero(buffer,1024);
      n = read(sockfd,buffer,1023);
      if (n < 0) 
	error("ERROR reading from socket");
      if(tasavi(buffer,"exit"))
	{
	  close(sockfd);
	  return 0;
	}
      if(tasavi(buffer,"disconnect"))
	{
	  close(sockfd);
	  main();
	  return 0;
	}
      printf("%s",buffer);
    }
  //close(sockfd);
  return 0;
}
