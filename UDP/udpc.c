// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT	 8080
#define MAXLINE 1024
	
// Driver code
int main() {
	int sockfd, n, addr_size;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr, cliaddr;
	
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0){
		printf("client socket creation failed...");
		exit(0);
	}
	else{
		printf("socket created successfully....");
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	while(1){
		printf("enter a message: ");
		bzero(buffer, MAXLINE);
		n=0;
		while((buffer[n++] = getchar()) != '\n');
		sendto(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
		printf("Data send : %s\n",buffer);
		if(strcmp(buffer, "exit\n")==0){
			exit(0);
		}
		addr_size = sizeof(servaddr);
		bzero(buffer,MAXLINE);
		recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&servaddr, &addr_size);
		printf("[+] Data received : %s\n",buffer);
		if(strcmp(buffer, "exit\n")==0){
			exit(0);
		}
	}

	return 0;
}
