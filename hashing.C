#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void readFromFile(char * fileName,struct HashNode *hashTable, long size);
static int SIZE = 7;
struct Credential{
	char *userName;
	char *encPassword;
};
struct HashNode{
	int count;
	struct ListNode *next;
};
struct ListNode{
	struct Credential *credential;
	struct ListNode *next;
};
char* getUserName(char *c){
	char *un= (char*)malloc(50);
	int i=0;
	while(1){
		if(*(c+i)==',')
			break;
		else
			*(un+i)=*(c+i);
		i++;
	}
	*(un+i)='\n';	
	//*(un+i+1)='\0';
	//fputs(un,stdout);
	return un;
}
char* getPassword(char *c){
	char *pp= (char*)malloc(50);
	int i=0,j=0;
	while(1){
		if(*(c+i)!=',')
			i++;
		else
			break;
	}
	i++;
	while(1){
		if(*(c+i)=='\n')
			break;
		else
			*(pp+j)=*(c+i);
		i++;j++;
	}
	*(pp+j)='\n';
	//*(pp+j+1)='\0';
	//fputs(pp,stdout);
	return pp;
}
char* encrypt(char *pp,char *un)
{
	int ppsize,unsize,i,j,f;
	char *ep;
	ppsize=strlen(pp);
	unsize=strlen(un);
	//printf("%d  %d \n",ppsize,unsize);
	ep=(char*)malloc(2*ppsize*sizeof(char));
	j=0;
	for(i=0;i<ppsize;i++)
	{
		f=(((int)(*pp+i))-33+((int)(*(un+j)))-33);
		*(ep+(i*2))=(char)(f%94 + 33);
		*(ep+(i*2+1))=(char)(f/94+33+i);
		//printf("%d %c %c %c%c\n",i,*(pp+i),*(un+j),*(ep+(i*2)),*(ep+i*2+1));
		j=(j+1)%(unsize-1);
	}
	*(ep+2*i)='\n';
	return ep;
}
long hash1(char *un){
	long hashVal =0;
	int i;
	for(i=0;i<strlen(un)-1;i++)
	{
		hashVal+=((int)*(un+i))*(i+1);
	}
	return hashVal%SIZE;
}

long hash2(char *un){
	long hashVal =0;
	int i;
	for(i=0;i<strlen(un)-1;i++)
	{
		hashVal=((int)*(un+i))+i*i;//*(i+1);
	}
	//hashVal*=hashVal;
	return hashVal%SIZE;
}
char* decrypt(char *ep,char *un)
{
	int epsize,unsize,i,j;
	char *pp;
	epsize=strlen(ep);
	unsize=strlen(un);
	//printf("%d  %d \n",epsize,unsize);
	pp=(char*)malloc(epsize*sizeof(char));
	j=0;
	for(i=0;i<epsize-1;i++)
	{
		*(pp+i)=(char)((((int)(*ep+i))-33+((int)(*(un+j)))-33)%94 + 33);
		j=(j+1)%(unsize-1);
	}
	*(ep+i)='\0';
	return ep;
}
void getCredentials(struct Credential *c){
	char *plainPassword;	
	printf("LOGIN:\nUSERNAME:");
	c->userName =(char*)malloc(50*sizeof(char));
	fgets(c->userName,49,stdin);
	plainPassword =(char*)malloc(50*sizeof(char));
	fputs("PASSWORD:",stdout);
	fgets(plainPassword,49,stdin);
	c->encPassword=encrypt(plainPassword,c->userName);
}
int main()
{
	struct HashNode hashTable[SIZE];
	struct Credential *c;
	struct ListNode *l;
	int i,hashValue,hops=0;
	for(i=0;i<SIZE;i++){
		hashTable[i].count=0;
	}
	c=(struct Credential*)malloc(sizeof(struct Credential));
	readFromFile("credentials.txt",hashTable,SIZE);
	getCredentials(c);
	hashValue = hash2(c->userName);
	//printf("searching location: %d\t%d\n",hashValue,strlen(c->userName));
	if(hashTable[hashValue].count>0){
		l = hashTable[hashValue].next;
		do{
			hops++;
			//fputs(c->userName,stdout);
			//fputs(l->credential->userName,stdout);
			//printf("%u\n",*(l));
			if(!strcmp(c->userName,l->credential->userName)){
				//fputs(c->encPassword,stdout);
				//fputs(l->credential->encPassword,stdout);
				if(strcmp(c->encPassword,l->credential->encPassword)){
					fputs("\nUnsuccessfull[Password mismatch]",stdout);
					//printf("\n%d",strcmp(c->encPassword,l->credential->encPassword));
					//printf("\n%d",strlen(c->encPassword));
					//printf("\n%d",strlen(l->credential->encPassword));
				}
				else
					fputs("Successfull",stdout);
				break;
			}
			else{
				l=l->next;
			}
		}while(l != NULL);
		if(l==NULL){
			fputs("\nUnsuccessfull[user not found]",stdout);
		}
	}
	else{
		fputs("\nUnsuccessfull[user not found]",stdout);
	}
	printf("\n%d Comparisons done.\n",hops);
//INSERTING FEATURE
//	hashTable[hashValue].count++;
//	hashTable[hashValue].next = (struct ListNode*)malloc(sizeof(struct ListNode));
//	hashTable[hashValue].next->next=NULL;
//	hashTable[hashValue].next->credential=c;
// PRINTING THE COUNT OF ELEMENTS ON THE HASHTABLE
//	for(i=0;i<SIZE;i++){
//		printf("\n%d",hashTable[i].count);
//	}
	return 0;
}

void readFromFile(char * fileName,struct HashNode *hashTable, long size)
{
 	FILE *f = fopen(fileName,"r");
	struct Credential *c;
	struct ListNode *l;
	char buff[100],*userName,*plainPassword;
	int hashValue;
	memset(buff,0,sizeof(buff));
	if(f!=NULL){
		while(fgets(buff,sizeof buff,f)){
//			fputs(buff,stdout);
			plainPassword = getPassword(buff);
			//fputs(plainPassword,stdout);
			userName = getUserName(buff);
			//fputs(userName,stdout);
			c=(struct Credential*)malloc(sizeof(struct Credential));
			c->userName = userName;
			c->encPassword = encrypt(plainPassword,userName);
			hashValue = hash2(userName);
			//printf("%d\t%d\n",hashValue,strlen(userName));
			(hashTable+hashValue)->count++;
			//printf("\nInserting %s\n",c->userName);
			if((hashTable+hashValue)->count==1){
				(hashTable+hashValue)->next = (struct ListNode*)malloc(sizeof(struct ListNode));
				(hashTable+hashValue)->next->next=NULL;
				(hashTable+hashValue)->next->credential=c;
				//printf("\nInserted %s\n",(hashTable+hashValue)->next->credential->userName);
				//printf("%u\n",*((hashTable+hashValue)->next));
			}
			else{
				l =(hashTable+hashValue)->next;
				while(l->next != NULL)
					l=l->next;
				l->next = (struct ListNode*)malloc(sizeof(struct ListNode));
				l->next->next=NULL;
				l->next->credential=c;
			
			}
			memset(buff,0,sizeof(buff));
		}
		fclose(f);
	}
	else
		printf("\nERROR: FILE NOT FOUND\n");	
}
