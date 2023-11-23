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
//     char message[255];

//     sockfd = socket(AF_INET, SOCK_DGRAM, 0);

//     memset(&client_addr, 0, sizeof(client_addr));
//     client_addr.sin_family = AF_INET;
//     client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
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
//         memset(message, 0, sizeof(message));
//         if (recvfrom(sockfd, message, sizeof(message), 0, NULL, NULL) == -1) {
//             perror("recvfrom");
//             exit(1);
//         }
//         printf("Received: %s", message);
//     }

//     close(sockfd);
//     return 0;
// }

//client multicast
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
int main()
{
	int r=1,sock;
	struct sockaddr_in serv;
	char str[100];
	bzero(&serv,sizeof(serv));
	sock=socket(AF_INET,SOCK_DGRAM,0);
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&r,sizeof(r));
	serv.sin_family=AF_INET;
	serv.sin_port=htons(12345);
	serv.sin_addr.s_addr=INADDR_ANY;
	bind(sock,(struct sockaddr*)&serv,sizeof(serv));
	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr=inet_addr("224.1.1.1");
	mreq.imr_interface.s_addr=INADDR_ANY;
	setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
	while(1)
	{
		bzero(str,100);
		recvfrom(sock,str,100,0,(struct sockaddr*)NULL,NULL);
		printf("%s",str);
	}
	close(sock);
}