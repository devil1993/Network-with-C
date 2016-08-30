#include<stdio.h>
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
	int vertices[g->vertices];
	int i,node=1;
	struct component *root,*current,*newC;
	for(i=0;i<g->vertices;i++)
		vertices[i] = 0;
	root = NULL;	
	current = root;
	do{
		printf("\nNew Component: %d",node);
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
			printf("\nNode: %d",node);
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
	}while(node<=(g->vertices));
	
	return root;
}



int main(int argc, char *argv[]){
	struct Graph *g=NULL;
	struct component *c=NULL;
	if(argc==2)
	{
		g= readGraphTemp(argv[1]);
		printf("\nGraph Loaded\n");
		c= getComponents(g);
		while(c!=NULL){
			printf("\nComponent with size: %d",c->size);
			c= c->next;		
		}
	}
	else {
		printf("\nerror: Enter one filename.");
		exit(1);
	}
	printf("\nPress ENTER to finish");
	getchar();
	system("clear");
	return(0);	
}