#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
	char *num1, *num2,*result,*ptr1=NULL,*ptr2=NULL,*ptr3=NULL;
	long resultMaxSize = 0;
	int borrow=0;
	num1 = malloc(100*sizeof(char));
	num2 = malloc(100*sizeof(char));
	printf("Enter Larger number: ");	
	fgets(num1,99,stdin);
	printf("Enter Smaller number: ");	
	fgets(num2,99,stdin);
	resultMaxSize = strlen(num1)>strlen(num2)?strlen(num1):strlen(num2);
	result = (char*)malloc((resultMaxSize+1)*sizeof(char));	
	ptr1=num1;ptr2=num2;ptr3=result;
	while(*(ptr1+1)!='\n')
		ptr1+=1;
	while(*(ptr2+1)!='\n')
		ptr2+=1;
	while(ptr1>=num1 ){
		if(isdigit(*ptr1) && (isdigit(*ptr2)||ptr2<num2))
		{
			if(ptr1>=num1 && ptr2>=num2){
				if(*ptr1>=(*ptr2+borrow)){
					*ptr3 = (*ptr1-*ptr2-borrow)+48;
					borrow=0;}
				else{
					*ptr3= (*ptr1+10 -*ptr2-borrow)+48;
					borrow=1;	
				}
				ptr1-=1;ptr2-=1;
				ptr3+=1;
			}		
			else if(ptr1>=num1){
				if(*ptr1>=(borrow+48)){
					*ptr3 = (*ptr1-borrow);
					printf("\n x: %d.",*ptr3);
					borrow=0;
				}
				else{
					*ptr3= (*ptr1+10 -borrow);
					printf("\n x: %d",*ptr3);
					borrow=1;	
				}
				ptr1-=1;
				ptr3+=1;
			}
		}
		else
		{printf("\nIncorrect entry: %d,%d\n",*ptr1,*ptr2);exit(1);}
	}
//	printf("\n%u\t%u",result,ptr3);
	ptr3-=1;
	printf("\nResult:\n");
	while(ptr3>=result)
	{
		printf("%c",*ptr3);
		ptr3-=1;
	}
	printf("\n");
	exit(0);
}
