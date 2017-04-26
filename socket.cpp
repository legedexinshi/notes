#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <syslog.h>
#include <errno.h>
#include <stdlib.h>
using namespace std;

#define MAX_LISTEN_NUM 5
#define SEND_BUF_SIZE 100
#define RECV_BUF_SIZE 100
#define LISTEN_PORT 6789
int main()
{
  int listen_sock = 0;
  int app_sock = 0;
  close(app_sock);
	struct sockaddr_in hostaddr;
  struct sockaddr_in clientaddr;
  socklen_t socklen = sizeof(clientaddr);
  char sendbuf[SEND_BUF_SIZE] = {0};
  char recvbuf[RECV_BUF_SIZE] = {0};
  int sendlen = 0;
  int recvlen = 0;
  int retlen = 0;
  int leftlen = 0;
	char *ptr = NULL;
  memset((void *)&clientaddr, 0, sizeof(clientaddr));
  hostaddr.sin_family = AF_INET;
  hostaddr.sin_port = htons(LISTEN_PORT);
  hostaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  listen_sock = socket(AF_INET, SOCK_STREAM, 0);
  if(listen_sock != 0)
  {
      syslog(LOG_ERR, "%s:%d, create socket failed", __FILE__, __LINE__);
      exit(1);
  }
  int x= bind(listen_sock, (struct sockaddr *)&hostaddr, sizeof(hostaddr)); 
  if (x < 0)
  {
      syslog(LOG_ERR, "%s:%d, bind socket failed", __FILE__, __LINE__);
      exit(1);
  }
  if(listen(listen_sock, MAX_LISTEN_NUM) < 0)
  {
      syslog(LOG_ERR, "%s:%d, listen failed", __FILE__, __LINE__);
      exit(1);
  }

	sockaddr_in * p = new sockaddr_in;
	socklen_t alen;

  while(1)
  {
	 cout<<"im listening"<<endl;
     app_sock = accept(listen_sock, (struct sockaddr *)&clientaddr, &socklen);
     if(app_sock < 0)
     {
        syslog(LOG_ERR, "%s:%d, accept failed", __FILE__, __LINE__);
        exit(1);
	 }
	 int n;
	 char ch[1000];

cout <<"connect succeed\n";	 
sockaddr_in *s = new sockaddr_in;
socklen_t len = (socklen_t) sizeof(*s);
if (getpeername( app_sock, (sockaddr *)s, &len)) cout <<"get error\n";
cout << ntohs(s->sin_port)<<endl;
cout << inet_ntop(AF_INET, &(s->sin_addr), ch, 1000) << endl;

	 while (n=read(app_sock , ch, 1000)>0) cout << ch<<endl; 

  }
  
  return 0;
  
  
}
