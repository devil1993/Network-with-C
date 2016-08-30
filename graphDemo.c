#include<stdio.h>
//#include<stdlib.h>
#include"graphreader.h"
//#include<string.h>


int main(int argc, char *argv[]){
	struct Graph *g;
	int i;
	system("clear");
	if(argc != 2){
		printf("Please provide 1 filename");
		exit(1);	
	}
//	printf("initiated\n");
	g = readGraphTemp(argv[1]);
	if(g!=NULL){
	printf("Vertices: %d\tEdges: %d\n",g->vertices,g->edges);
		for(i=0;i<g->edges;i++){
				printf("%d->%d\n",g->edgeList[i].start,g->edgeList[i].end);
		}
	}
	return 0;
}