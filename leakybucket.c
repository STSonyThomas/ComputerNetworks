#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>

#define BUCKET_LIMIT 10
#define OUTPUT_RATE 3

int main()
{
    int packet_size, bucket_size=0,n,ch;
    bool control= true;
    int *que;

    do{
        bucket_size=0;
        printf("Enter the number of packets to be sent: ");
        scanf("%d",&n);
        que = (int*)malloc(sizeof(int)*n);
        printf("Enter the sizes of the packets in order:");
        for(int i=0;i<n;i++){
            printf("\nPacket %d: ",i+1);
            scanf("%d",&que[i]);
            bucket_size+=que[i];
            if(bucket_size>BUCKET_LIMIT){
                printf("Bucket overflow\n");
                bucket_size-=que[i];
                printf("Packet %d is discarded\n",i+1);
            }
            if(bucket_size>OUTPUT_RATE){
                bucket_size-=OUTPUT_RATE;
            }
            
        }
        printf("Do you wanna control trafficking?(1/0)");
            scanf("%d",&ch);
            if(ch==0){
                control=false;
            }
    }while(control);
}