#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
unsigned long long int size,part,start,end;
FILE *f=NULL;
void childEnded(int sig){
	printf("Child process ended.\n");		
}
char* toString(int n){
	char *s = (char*)malloc(6*sizeof(char));
	int i=0;
	while(n>0) {
		s[i] = n%10 +48;
		n=n/10;
		i++;
	}
	s[i]='\0';
	//printf("%s\n",s);
	return s;
}
void createSubFile(char source[],char fname[],int fno){
	FILE *f = fopen(source,"r");
	char ch,*partFile =(char*)malloc(sizeof(fname)+5),*c =(char*)malloc(sizeof(fname)+5);
	int isSpace = 0;
	strcpy(partFile,fname);
	strcpy(c,fname);
	partFile = strcat(partFile,"_part");
	partFile = strcat(partFile,toString(fno+1));
	c = strcat(c,toString(fno+1));
	//printf("%d : %llu -> %llu\n",(int)getpid(), start, end);
	fseek(f,start,SEEK_SET);
	//printf("%s\t%s\n", partFile,c);
	FILE *fpart = fopen(partFile,"w");
	FILE *fs = fopen(c,"w");
	while(EOF!= (ch=fgetc(f))){
		fputc(ch,fpart);		
		if(isSpace){
			//printf("one Detected\n");
			if(ch != ' '){
				fputc(ch,fs);
				isSpace = 0;
			}
			//else
				//printf("one trimmed\n");
		}
		else {
			fputc(ch,fs);
			//printf("%d_%c_\n",(int)ch,ch);
			if(ch == ' ') 
			{
				//printf("WTF\n");
				isSpace = 1;
			}
		}
		if(end == ftell(f)){
			break;
		}
	}
	fclose(fpart);
	fclose(fs);
	fclose(f);
	printf("Child %d completed\n",(int)getpid());
	//kill(getppid(),SIGCHLD);
}
int main(int argc, char *argv[]){
	time_t before = clock();	

	(void) signal(SIGCHLD,childEnded);

	FILE *fsmall;
	f = fopen(argv[1],"r");
	char c;
	int i =0,j=1,n,stat;	

	printf("Enter the number of processes: ");
	scanf("%d",&n);

	fseek(f,0L,SEEK_END);
	size = ftell(f);
	fseek(f,0L,SEEK_SET);
	//printf("Got size %llu \n",size);
	//getchar();
	fclose(f);

	part = size/n;
	//printf("Got part %llu \n",part);
	int pids[n];
	
	for(i=0;i<n;i++){
	//	printf("%d\n", i);
		start = part*i;
		end = i==n-1?size-1:part*(i+1);
		pid_t pid = fork();
		if(pid<0) {
			printf("FAILED\n");
				break;				
			}
		else if(pid==0){				
			createSubFile(argv[1],argv[2],i);
			return 0;
		}
		else {
			printf("Child process %d started.\n", (int)pid)
;			pids[i] = (int)pid;			
		}
	}	
	//createSubFile(argv[1],ch,i,++j);
	for(i=0;i<n;i++) {
		waitpid(pids[i],NULL,0);		
	}
	//fclose(f);
	printf("Subfiles created\n");
	FILE *fi =fopen(argv[2],"w");
	for(i=1;i<=n;i++) {
		char *smallFile = (char*)malloc(sizeof(argv[2])+5);
		strcpy(smallFile,argv[2]); 
		smallFile = strcat(smallFile,toString(i));
		//printf("%s %s\n",smallFile,argv[2]);		
		fsmall = fopen(smallFile,"r");
		while(EOF!= (c=fgetc(fsmall))){
			//fputc(c,stdout);
			fputc(c,fi);		
		}
		//scanf("%c",&c);
		fclose(fsmall);		
		remove(smallFile);
		//printf("%d marged.\n",i);	
	}
	fclose(fi);
	printf("Time Taken: %ld\n",clock()-before);	
}