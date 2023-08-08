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

void func(int connfd){
	char buffer[MAX];
	int n;
	while(1){
		bzero(buffer, MAX);
		read(connfd, buffer, sizeof(buffer));
		printf("From client:- %s\n\tTo client:- ",buffer);
		bzero(buffer, MAX);
		n=0;
		while((buffer[n++] = getchar())!='\n');
		write(connfd, buffer, sizeof(buffer));
		if(strcmp(buffer, "exit\n") == 0){
			printf("server exit......\n");
			exit(0);
		}
	}
}

int main(){
	int sockfd, len, connfd;
	struct sockaddr_in servaddr, cliaddr;
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("socket creation failed....\n");
		exit(0);
	}
	else{
		printf("socket created successfully.......\n");
	}
	bzero(&servaddr, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0){
		printf("binding failed......");
		exit(0);
	}
	else{
		printf("binding done successfully....\n");
	}
	if((listen(sockfd, 5)) != 0){
		printf("listen failed...");
		exit(0);
	}
	else{
		printf("server listening...\n");
	}
	len = sizeof(cliaddr);
	connfd = accept(sockfd, (SA *)&cliaddr, &len);
	if(connfd<0){
		printf("server accept failed....\n");
		exit(0);
	}
	else{
		printf("server accepted the client...\n");
	}
	func(connfd);
	close(sockfd);
}












