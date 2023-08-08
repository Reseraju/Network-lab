#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main(){
	int sockfd, addr_size, n;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr, cliaddr;
	
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0){
		printf("socket creation failed");
		exit(0);
	}
	else{
		printf("socket successfully created...");
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	//filling server info
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	//binding
	if(bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))<0){
		printf("bind failed...");
		exit(0);
	}
	
	while(1){
		bzero(buffer, MAXLINE);
		addr_size = sizeof(cliaddr);
		recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&cliaddr, &addr_size);
		printf("[+] Data recv : %s\n",buffer);
		if(strcmp(buffer,"exit\n")==0){
			exit(0);
		}
		printf("enter a message: ");
		bzero(buffer, MAXLINE);
		n=0;
		while((buffer[n++] = getchar()) != '\n');
		sendto(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&cliaddr, addr_size);
		printf("[+] data send : %s\n", buffer);
		if(strcmp(buffer,"exit\n")==0){
			exit(0);
		}
	}
	return 0;
}
