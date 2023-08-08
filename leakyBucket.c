#include<stdio.h>
#include<unistd.h>
int main(){
	int buffSize, noOfPackets, buffS, i, bucket[50], count=0, packetS[50], rateF, time, temp, datasent=0;
	printf("enter the size of buffer: ");
	scanf("%d",&buffSize);
	buffS = buffSize;
	printf("enter the no of packets: ");
	scanf("%d",&noOfPackets);
	for(i=0;i<noOfPackets;i++){
		printf("size of packet [%d] : ",i);
		scanf("%d",&temp);
		if(temp>buffS){
			printf("packet size is greater than buffer space\n");
		}
		else{
			bucket[count] = i;
			buffS -= temp;
			packetS[count] = temp;
			count++;
		}
	}
	printf("\nenter the data flow rate: ");
	scanf("%d",&rateF);
	printf("enter the time interval of data flow: ");
	scanf("%d",&time);
	for(i=0;i<count;i++){
		while(packetS[i] > 0){
			sleep(time);
			packetS[i] -= rateF;
			datasent++;
		}
		printf("packet [%d] completed in %d send\n",bucket[i],datasent);
	}
}