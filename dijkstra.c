#include<stdio.h>
#include"graphreader.h"
#include"queue.h"

int main(int argc, char *argv[]){
	struct Graph *g;
	int src,*paths,i,current,*flag,j;
	if(argc==2){
		g = readGraphTemp(argv[1]);
		printf("Enter Source Node: ");
		scanf("%d",&src);
		paths = (int*)malloc(sizeof(int)*g->vertices);
		flag = (int*)malloc(sizeof(int)*g->vertices);
		for(i=0;i<g->vertices;i++) {
			paths[i]=32767;
			flag[i]=0;		
		}
		paths[src-1]=0;
		flag[src-1]=1;
		enqueue(src);
		while(queueCount>0) {
			current = dequeue();
			for(i=0;i<g->edges;i++) {			
				if(g->edgeList[i].start==current || g->edgeList[i].end==current) {
					if(paths[current-1]+1<paths[g->edgeList[i].end-1]){
						paths[g->edgeList[i].end-1]=paths[current-1]+1;
						if(!flag[g->edgeList[i].end-1]){
							enqueue(g->edgeList[i].end);
							flag[g->edgeList[i].end-1]=1;
						}
					}
					if(paths[current-1]+1<paths[g->edgeList[i].start-1]){
						paths[g->edgeList[i].start-1]=paths[current-1]+1;
						if(!flag[g->edgeList[i].start-1]){
							enqueue(g->edgeList[i].start);
							flag[g->edgeList[i].start-1]=1;
						}
					}
				}
			}
		}
		for(i=0;i<g->vertices;i++) {
			if(paths[i]!=32767)
				printf("\n %d->%d : %d",src,i+1,paths[i]);
			else 
				printf("\n %d->%d : Infinite",src,i+1);
		}
   }	
	else {
		printf("\nENTER ONE FILENAME\n");
		return 1;
	}
	printf("\n");
	return 0;
}