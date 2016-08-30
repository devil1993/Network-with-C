static int SIZE = 10;
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
	struct Credential *next;
};
char* encrypt(char *pp,char *un)
{
	int ppsize,unsize,i,j,f;
	char *ep;
	ppsize=strlen(pp);
	unsize=strlen(un);
	//printf("%d  %d \n",ppsize,unsize);
	ep=(char*)malloc(2*ppsize*sizeof(char));
	j=0;
	for(i=0;i<ppsize-1;i++)
	{
		f=(((int)(*pp+i))-33+((int)(*(un+j)))-33);
		*(ep+(i*2))=(char)(f%94 + 33);
		*(ep+(i*2+1))=(char)(f/94+33+i);
		//printf("%d %c %c %c%c\n",i,*(pp+i),*(un+j),*(ep+(i*2)),*(ep+i*2+1));
		j=(j+1)%(unsize-1);
	}
	*(ep+2*i)='\0';
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
	printf("\n");
	c->userName =(char*)malloc(50*sizeof(char));
	fgets(c->userName,49,stdin);
	//fputs(un,stdout);
	plainPassword =(char*)malloc(50*sizeof(char));
	fgets(plainPassword,49,stdin);
	//fputs(pp,stdout);
	c->encPassword=encrypt(plainPassword,c->userName);
	//fputs(ep,stdout);
}
