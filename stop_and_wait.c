#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
struct frame{
	int info;
	int seq;
};

int ak;
int t=5,k;
int disconnect = 0;
int errorframe = 1;
int errorack = 1;

struct frame p;
char turn = 's';

void sender();
void receiver();

int main(){
	p.info = 0;
	p.seq = 0;
	while(!disconnect){
		sender();
		sleep(5);
		receiver();
	}
}

void sender(){
	static int flag=0;
	if(turn == 's'){
		if(errorack == 0){
			printf("SENDER: send packet with seq No:%d\n",p.seq);
			errorframe = rand()%4;
			printf("%s\n",(errorframe == 0 ? "error while sending the packet" : ""));
			turn = 'r';
		}
		else{
			if(flag==1){
				printf("SENDER: received ACK for packet %d\n",ak);
			}
			if(p.seq == 5){
				disconnect = 1;
				return;
			}
			p.info = p.info + 1;
			p.seq = p.seq + 1;
			printf("SENDER: send packet with seq No:%d\n",p.seq);
			errorframe = rand() % 4;
			printf("%s\n",(errorframe ==0 ?"error while sending the packet":""));
			turn = 'r';
			flag = 1;		
		}
	}
	else{
		printf("SENDER time reducing\n");
		if(t==0){
			turn = 's';
			errorack = 0;
			t=5;
		}
	}
}

void receiver(){
	static int frexp = 1;
	if(turn == 'r'){
		if(errorframe != 0){
			if(p.seq==frexp){
				printf("RECEIVER: received packet with seq No:%d\n",p.seq);
				ak=p.seq;
				frexp = frexp + 1;
				turn = 's';
				errorack = rand()%4;
				printf("%s\n",(errorack == 0 ? "error while sending the ACK" : ""));
				
			}
			else{
				printf("RECEIVER: duplicated packet with seq No: %d\n",frexp - 1);
				ak = frexp - 1;
				turn = 's';
				errorack = rand() % 4;
				printf("%s\n",(errorack == 0 ? "error while sending the ACK" : ""));
			}
		}
	}
}









