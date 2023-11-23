// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <arpa/inet.h>
// #include<sys/socket.h>
// #include<unistd.h>
// #define MULTICAST_IP "227.1.1.1"
// #define PORT 2434

// int main() {
//     int sockfd,r=1;
//     struct sockaddr_in client_addr;
//     char message[255],m[10];

//     sockfd = socket(AF_INET, SOCK_DGRAM, 0);

//     memset(&client_addr, 0, sizeof(client_addr));
//     client_addr.sin_family = AF_INET;
//     client_addr.sin_addr.s_addr = inet_addr("227.1.1.1");
//     client_addr.sin_port = htons(2434);
//         setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&r,sizeof(r));
//     if (bind(sockfd, (struct sockaddr*)&client_addr, sizeof(client_addr)) == -1) {
//         perror("bind");
//         exit(1);
//     }

//     struct ip_mreq mreq;
//     mreq.imr_multiaddr.s_addr = inet_addr("227.1.1.1");
//     mreq.imr_interface.s_addr = htonl(INADDR_ANY);
//     setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) ;
//     printf("Multicast client is running...\n");

//     while (1) {
//     	printf("Do you want to multicast");
//     	fgets(m,10,stdin);
//     	if(strncmp(m,"yes",3)==0)
//     	{
//     	printf("Enter the message");
//         bzero(message,255);
//         fgets(message,255,stdin);
//         sendto(sockfd, message, sizeof(message), 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
//         printf("Received: %s", message);
//         }
//     }

//     close(sockfd);
//     return 0;
// }

//server multicast
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
int main()
{
	int b=1,sock;
	char str[100],str2[10];
	struct sockaddr_in serv;
	bzero(&serv,sizeof(serv));
	sock=socket(AF_INET,SOCK_DGRAM,0);
	
	serv.sin_family=AF_INET;
	serv.sin_port=htons(12345);
	serv.sin_addr.s_addr=inet_addr("224.1.1.1");
	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr=inet_addr("224.1.1.1");
	mreq.imr_interface.s_addr=INADDR_ANY;
	setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
	while(1)
	{
		printf("do you want to send data?");
		fgets(str2,10,stdin);
		if(strncmp(str2,"yes",3)==0)
		{
			bzero(str,100);
			printf("Enter the string");
			fgets(str,100,stdin);
			sendto(sock,str,strlen(str),0,(struct sockaddr*)&serv,sizeof(serv));
		}
		else
		{
			break;
		}
	}
	close(sock);
}   