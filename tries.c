#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Trienode{
	struct Trienode *tnp[26];
	int isLeaf; 
};
int sci=0;
struct Trienode* createTrieNode(){
	struct Trienode *tn;
	int i;
	tn = (struct Trienode*)malloc(sizeof(struct Trienode));
	tn->isLeaf=0;
	for(i=0;i<26;i++){
		*(tn->tnp + i) = NULL;
	}
	return tn;
}

struct Trienode* createTrieLeafNode(){
	struct Trienode *tn;
	tn = createTrieNode();
	tn->isLeaf = 1;
	return tn;
}

int insertTrie(struct Trienode *head, char buff[]){
	int i =0,currentChar;
	struct Trienode *currentNode = head;
	do{
		if(buff[i]=='\n' || buff[i]=='\0'){
			currentNode->isLeaf = 1;
//			printf("..%d..\n",currentNode->isLeaf);
			break;
		}
		currentChar = buff[i] - 97;
		if((currentNode->tnp[currentChar])==NULL){
			currentNode->tnp[currentChar] = createTrieNode();
			printf("Created for %c\n",currentChar+97);
		}
		currentNode = (currentNode->tnp[currentChar]);	
		i++;
	}while(1);
	return 1;
}
void constructFromFile(struct Trienode *head,char *fileName){
	FILE *f = fopen(fileName,"r");
	char buff[35];
	memset(buff,0,sizeof(buff));
	if(f!=NULL){
		while(fgets(buff,sizeof buff,f)){
			insertTrie(head,buff);
			printf("Inserted: %s\n",buff);
			memset(buff,0,sizeof(buff));
		}
	}
	else
		printf("FILE NOT FOUND.\n");
}

int searchWord(struct Trienode *head, char buff[]){
	int i=0,currentChar;
	struct Trienode *currentNode = head;
	while(buff[i] != '\n' && buff[i] != '\0'){
		currentChar = buff[i] - 97;
		if(currentNode->tnp[currentChar] != NULL){
//			printf("Found %c: %d\n",currentChar+97,currentNode->isLeaf);
			currentNode = currentNode->tnp[currentChar];
		}
		else
			return 0;
		i++;
	}
	if(currentNode->isLeaf)
		return 1;
	else
		return 0;
}

long searchPrefix(struct Trienode *head, char buff[]){
	int i=0,currentChar;
	char currentWord[35];
	struct Trienode *currentNode = head;
	while(buff[i] != '\n' && buff[i] != '\0'){
		currentChar = buff[i] - 97;
		if(currentNode->tnp[currentChar] != NULL){
//			printf("Found %c: %d\n",currentChar+97,currentNode->isLeaf);
			currentNode = currentNode->tnp[currentChar];
			currentWord[i] = buff[i];
		}
		else
			return 0;
		i++;
	}
	printf("\n------------------------------------------------------------------------------------------\n");
	return printAll(currentNode,currentWord,i);
}

int printAll(struct Trienode *current, char currentWord[],int size){
	int i=0;long sum = 0;
	if(current->isLeaf){
		currentWord[size] = '\0';
		fputs(currentWord,stdout);
		printf("\t");
		sum++;
		if(++sci == 4){
			sci = 0;
			printf("\n");
		}
	}
	for(;i<26;i++){
		if(current->tnp[i]!=NULL){
			currentWord[size] = 97+i;
//			size++;
			sum+=printAll(current->tnp[i],currentWord,size+1);
		}
	}
	return sum;
}

int main(int argc, char *argv[]){
	struct Trienode *head;
	int choice,result=0;
	long words;
	char word[35];
	head = createTrieNode();
	if(argc != 2){
		printf("Please provide 1 filename");
		exit(0);	
	}
	constructFromFile(head,argv[1]);	
//	system("clear");
//	fgets(word,34,stdin);
	while(1){
		printf("Dictionary loaded....\n0.Clear screen\n1.Search\n2.Add\n3.Search for prefix.\n4.Exit\nENTER CHOICE(0/1/2/3/4): ");
		scanf("%d",&choice);
		switch(choice){
			case 1: printf("Enter word: ");
				scanf("%s",word);				
//				fflush(stdin);
//				fgets(word,34,stdin);
				result = searchWord(head,word);
				if(result)
					printf("--------------------------------Word valid.----------------------------------\n");
				else
					printf("----------------------------Word not in dictionary---------------------------\n");
				break;
			case 2: printf("Enter word: ");
				scanf("%s",word);				
//				fgets(word,34,stdin);
				result = insertTrie(head,word);
				if(result)
					printf("--------------------------------Word added.----------------------------------\n");
				else
					printf("-------------------------------Word not added.-------------------------------\n");
					break;
			case 3: printf("Enter prefix: ");
				scanf("%s",word);				
//				fgets(word,34,stdin);
				words = searchPrefix(head,word);
				printf("\n------------------------------%ld words found--------------------------------\n",words);
				break;
			case 4: exit(0);
			case 0: system("clear");
				break;
			default:printf("Incorrect Entry.\n");		
		}
	}
}
