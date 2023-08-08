#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd){
	char buffer[MAX];
	int n;
	while(1){
		printf("enter a message: ");
		bzero(buffer, MAX);
		n=0;
		while((buffer[n++] = getchar()) != '\n');
		write(sockfd, buffer, sizeof(buffer));
		bzero(buffer, MAX);
		read(sockfd, buffer, sizeof(buffer));
		printf("message from server: %s\n",buffer);
		if(strcmp(buffer, "exit\n") == 0){
			printf("client exiting....\n");
			exit(0);
		}
	}
}

int main(){
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("socket creation failed......\n");
		exit(0);
	}
	else{
		printf("socket created successfully....\n");
	}
	bzero(&servaddr, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);
	
	if(connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0){
		printf("connection with server failed...\n");
		exit(0);
	}
	else{
		printf("connected to server....\n");
	}
	func(sockfd);
	close(sockfd);
}











