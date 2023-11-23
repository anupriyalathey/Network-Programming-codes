// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <netinet/in.h>
// #include <string.h>
// #define err_log(log) do{perror(log); exit(1);}while(0)
// #define N 128
// int main(int argc, const char *argv[])
// {
//  int sockfd;
//  char buf[N];
//  struct sockaddr_in broadcastaddr, srcaddr;
//  if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
//  {
//  err_log("fail to socket");
//  }
//  broadcastaddr.sin_family = AF_INET;
//  broadcastaddr.sin_addr.s_addr = inet_addr("INADDR_ANY"); //Broadcast address
//  broadcastaddr.sin_port = htons(10000);
//  if(bind(sockfd, (struct sockaddr*)&broadcastaddr, sizeof(broadcastaddr)) < 0)
//  {
//  err_log("fail to bind");
//  }
//  socklen_t addrlen = sizeof(struct sockaddr);
//  while(1)
//  {
//  if(recvfrom(sockfd,buf, N, 0, (struct sockaddr *)&srcaddr, &addrlen) < 0)
//  {
//  err_log("fail to sendto");
//  }
//  printf("buf:%s ---> %s %d\n", buf, inet_ntoa(srcaddr.sin_addr), ntohs(srcaddr.sin_port));
//  }
//  return 0;
// }

#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
int main()
{
int r=1;
int sock;
struct sockaddr_in serv;
char str1[100],str2[10];
bzero(&serv,sizeof(serv));
sock=socket(AF_INET,SOCK_DGRAM,0);
setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&r,sizeof(r));
serv.sin_family=AF_INET;
serv.sin_port=htons(12345);
serv.sin_addr.s_addr=INADDR_ANY;
bind(sock,(struct sockaddr *)&serv,sizeof(serv));
while(1)
{
bzero(str2,10);
if(strncmp(str2,"bye",3)==0){break;}else{
bzero(str1,100);
recvfrom(sock,str1,100,0,NULL,NULL);
printf("recvd data is %s",str1);}
}
close(sock);
}
