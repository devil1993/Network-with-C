#include<stdio.h>
#include"graphreader.h"
int main(int argc, char *argv[]){
	int nodes,n1,n2,isFail=0;
	long edges=0;
	struct Graph *g;
	struct Edge *lastEdge,*t;
	float probability=0.0;
	int failureCount=0;
	if(argc!=2){printf("\nEnter 1 filename to save."); exit(1);}
	printf("Enter the number of nodes: ");
	scanf("%d",&nodes);
	printf("Enter the probability: ");
	scanf("%f",&probability);
	g= (struct Graph*)malloc(sizeof(struct Graph));
	g->vertices=nodes;
	g->edgeList=NULL;
	while(failureCount<100){
		isFail=0;
		n1 = (int)((float)rand()/RAND_MAX*nodes);
		n2 = (int)((float)rand()/RAND_MAX*nodes);
		if(n1==n2){
			failureCount++;
			isFail =1;		
		}
		t=g->edgeList;
		while(t!=NULL){
			if((t->start == n1+1 && t->end == n2+1) || (t->start == n2+1 && t->end == n1+1)){
				isFail=1;break;
			}
			t=t->next;
		}
		if(((float)rand()/RAND_MAX)<probability && isFail==0){
			if(g->edgeList==NULL){
				g->edgeList = (struct Edge*)malloc(sizeof(struct Edge));
				lastEdge=g->edgeList;			
			}
			else {
				lastEdge->next = (struct Edge*)malloc(sizeof(struct Edge));
				lastEdge=lastEdge->next;
			}
			lastEdge->next = NULL;
			lastEdge->start = n1+1;
			lastEdge->end =n2+1;
			failureCount = 0;
			edges++;
		}
		else {
			isFail=1;
		}
		if(isFail)
			failureCount++;
		printf(".");
	}
	g->edges = edges;
	if(writeGraph(g,argv[1])){
		t=g->edgeList;
		while(t!=NULL){
			printf("\n%d -> %d",t->start,t->end);
			t=t->next;	
		}
		printf("\nVertices: %d\nEdges:%ld\n",g->vertices,edges);
	}
	return 0;
}