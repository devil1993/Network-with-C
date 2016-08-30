#include<stdio.h>
#include<stdlib.h>
#include"graphreader.h"
#include"queue.h"
int main(int argc, char *argv[]){
	struct Graph *g;
	int *flags,i,currentNode;	
	system("clear");
	if(argc==2){
		g = readGraphTemp(argv[1]);
		printf("Graph Loaded\n");
		flags = (int*)malloc(sizeof(int)*g->vertices);
		for(i=0;i<g->vertices;i++) {
			flags[i]=0;
		}		
		currentNode = 1;		
		enqueue(currentNode);
		flags[0]=1;
		while(getQueueCount()>0){
			currentNode = dequeue();	
			if(currentNode==-32768)	
				continue;	
			printf("Node: %d\n",currentNode);
			for(i=0;i<g->edges;i++){
				if((g->edgeList[i].start == currentNode && flags[g->edgeList[i].end-1]==0)){
					enqueue((g->edgeList[i].end));
					flags[g->edgeList[i].end-1]=1;						
				}
				else if(g->edgeList[i].end == currentNode && flags[g->edgeList[i].start-1]==0) 
				{
					enqueue((g->edgeList[i].start));
					flags[g->edgeList[i].start-1]=1;						
				}
			} 
		}
	}
	else{
		printf("\nerror: Enter 1 filename.");
	}
}