#include<stdlib.h>
struct StackNode{
	int data;	
	struct StackNode *next;	
};
struct StackNode *top =NULL;
int count =0;

int stackCount(){
	return count;
}
int pop(){
	if(top == NULL){
		return -32768;
	}
	int data = top->data;
	top = top->next;
	count--;
	return data; 	
}

int push(int data){
	struct StackNode *newNode;
	newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
	if(newNode == NULL){
		return 0;	
	}
	else{
		newNode->next = top;
		newNode->data = data;
		top = newNode;
		count++;
		return 1;	
	}
}