#include<stdlib.h>
struct QueueNode{
	int data;
	struct QueueNode *next;	
};
struct QueueNode *front =NULL;
struct QueueNode *rear =NULL;
int queueCount = 0;
int dequeue(){
	struct QueueNode *cur=front;
	if(front == NULL || queueCount ==0){
		return -32768;
	}
	int data = front->data;
	front = front->next;
	queueCount--;
	return data; 	
}

int getQueueCount(){
	return queueCount;
}

int enqueue(int data){
	struct QueueNode *newNode=NULL;
	newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
	if(newNode == NULL){
		return 0;	
	}
	else{
		newNode->next = NULL;
		newNode->data = data;
		if(rear==NULL){
			rear=newNode;
		}
		else {			 	
			rear->next=newNode;
		}
		if(front==NULL)
			front=newNode;
		rear = newNode;		
		queueCount++;
		return 1;	
	}
}