#include<stdio.h>
#include<stdlib.h>
#include"graphreader.h"
#include"stack.h"
struct component{
	int size;
	struct component *next;
};

int getVertex(int *vertices, int size){
	int i;
	for(i=0;i<size;i++){
		if(vertices[i] == 0)
			break;	
	}
	return i;
}

struct component* getComponents(struct Graph *g){
	printf("---------");	
	int vertices[g->vertices];
	int i,node=1;
	struct component *root,*current,*newC;
	printf("---------");
	for(i=0;i<g->vertices;i++)
		vertices[i] = 0;
	root = NULL;	
	current = root;
	do{
		//printf("\nNew Component: %d",node);
		newC = (struct component*)malloc(sizeof(struct component));
		if(root==NULL){
			root = newC;					
		}
		else{
			current->next = newC;
		}
		current= newC;
		current->size=1;		
		current->next=NULL;		
		push(node);
		vertices[node-1]=1;
		while(stackCount()>0){
			node = pop();	
			//printf("\nNode: %d",node);
			if(node==-32768)	
				continue;				
			for(i=0;i<g->edges;i++){
				if((g->edgeList[i].start == node && vertices[g->edgeList[i].end-1]==0)){
					push((g->edgeList[i].end));
					vertices[g->edgeList[i].end-1]=1;
					current->size+=1;										
				}
				else if(g->edgeList[i].end == node && vertices[g->edgeList[i].start-1]==0) 
				{
					push((g->edgeList[i].start));
					vertices[g->edgeList[i].start-1]=1;
					current->size+=1;										
				}
			} 
		}
		node=getVertex(vertices,g->vertices)+1;
		printf(".");
	}while(node<=(g->vertices));
	
	return root;
}
struct Graph* dummy(){
	int nodes,n1,n2,isFail=0;
	long edges=0;
	struct Graph *g;
	struct Edge *lastEdge,*t;
	float probability=0.0;
	int failureCount=0;
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
			if((t->start == n1 && t->end == n2) || (t->start == n2 && t->end == n1)){
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
			lastEdge->start = n1;
			lastEdge->end =n2;
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
	g->edges=edges;
	t=g->edgeList;
	while(t!=NULL){
		printf("\n%d -> %d",t->start,t->end);
		t=t->next;	
	}
	printf("\nVertices: %d\nEdges:%ld\n",g->vertices,edges);
	return g;
}
int main(int argc, char *argv[]){
	struct Graph *g=NULL;
	struct component *c=NULL;
	
		g= dummy();
		printf("-/-/-/-/-/-/-/\n");
		getchar();
		c= getComponents(g);
		while(c!=NULL){
			printf("\nComponent with size: %d",c->size);
			c= c->next;		
		}
	printf("\nPress ENTER to finish");
	getchar();
	system("clear");
	return(0);	
}