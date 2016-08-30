#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Edge{
	int start,end;
	struct Edge *next;
};
struct Graph{
	int vertices;long int edges;
	struct Edge *edgeList;
};

struct Graph* readGraph(char *fileName){
	 	FILE *f = fopen(fileName,"r");
	 	struct Graph *g;
	 	int i=0,flag=0;
	 	char buff[100];
	 	memset(buff,0,sizeof(buff));
	 	if(f!=NULL){
	 		g = (struct Graph*)malloc(sizeof(struct Graph));
	 		g->vertices=0;
	 		g->edges=0;
	 		if(fgets(buff, sizeof buff,f)){
	 			while(buff[i]!='\n' && buff[i]!='\0') {
	 				switch(flag) {
	 					case 0:
	 						g->vertices = (g->vertices)*10+ buff[i]-48;
	 						if(buff[i]==',') {
	 							flag++;	 						
	 						}
	 						break;
	 					case 1:
	 						g->edges = (g->edges)*10+ buff[i]-48;
	 						if(buff[i]==',') {
	 							flag++;	 			
	 							g->edgeList = (struct Edge*)malloc(sizeof(struct Edge)*g->edges);			
	 						}
	 						break;
	 					case 2:
	 						if(buff[i]=='}'||buff[i]=='{')
	 							break;
	 				}
	 				i++;
	 			}
	 			return NULL;
	 		}
	 		else {
	 			printf("\nerror: No data.");
	 			return NULL;
	 		}
	 	}
	 	else {
	 		printf("\nerror: File not found.");
	 		return NULL;
	 	}
}
struct Graph* readGraphTemp(char *fileName){ 	
	 	FILE *f = fopen(fileName,"r");	 	
	 	struct Graph *g;
	 	int i=0,j=0,temp=0;
	 	char buff[100];
//	 	printf("1");
//	 	getchar();
	 	memset(buff,0,sizeof(buff));
	 	if(f!=NULL){
//	 		printf("2");
//	 		scanf("%c");
	 		g = (struct Graph*)malloc(sizeof(struct Graph));
	 		g->vertices=0;
	 		g->edges=0;
	 		if(fgets(buff, sizeof buff,f)){
//	 			printf("3");
	 			while(buff[i]!='\n' && buff[i]!='\0') {
					g->vertices = (g->vertices)*10+ buff[i]-48;
		 			//if(buff[i]==',') {
					//	break;		 			
		 			//}
		 			i++;
//		 			printf("4.%d",i);
		 		}
//		 		printf("4");
		 	}
		 	i=0;
		 	memset(buff,0,sizeof(buff));
		 	if(fgets(buff, sizeof buff,f)){
//		 		printf("5");
	 			while(buff[i]!='\n' && buff[i]!='\0') {
					g->edges = (g->edges)*10+ buff[i]-48;
		 			//if(buff[i]==',') {
					//	break;		 			
		 			//}
		 			i++;
		 		}
		 		//printf("6");
		 	}		 
	 		g->edgeList = (struct Edge*)malloc(sizeof(struct Edge)*g->edges);
//	 		printf("7");
	 		memset(buff,0,sizeof(buff));
	 		while(fgets(buff, sizeof buff,f)) {
//	 			printf("8");
	 			i=0;temp=0;
	 			while(buff[i]!=' ') {
	 				temp = temp*10+buff[i]-48;
	 				i++;
	 			}
//	 			printf("9");
	 			g->edgeList[j].start = temp;
	 			i++;temp=0;
//	 			printf("10");
	 			while(buff[i]!='\n' && buff[i]!='\0'){
	 				temp = temp*10+buff[i]-48;
	 				i++;
	 			}
//	 			printf("11");
	 			g->edgeList[j].end=temp;
	 			j++;
	 			memset(buff,0,sizeof(buff));
	 		}
//	 		printf("12");
	 		fclose(f);
	 		return g;			
	 	}
	 	else {
	 		printf("\nerror: File not found.");
//	 		getchar();
	 		return NULL;
	 	}
}

int writeGraph(struct Graph *g, char *filename){
	struct Edge *e=NULL;	
	FILE *f = fopen(filename,"w");
	if(f==NULL)
		return 0;
	else{
		fprintf(f,"%d\n",g->vertices);
		fprintf(f,"%ld\n",g->edges);
		e = g->edgeList;
		while(e!=NULL){
			fprintf(f,"%d %d\n",e->start,e->end);
			e=e->next;
		}
		fclose(f);
		return 1;
	}
}