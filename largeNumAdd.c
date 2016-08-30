#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
	char *num1, *num2,*result,*ptr1=NULL,*ptr2=NULL,*ptr3=NULL;
	long resultMaxSize = 0;
	int carry=0;
	num1 = malloc(100*sizeof(char));
	num2 = malloc(100*sizeof(char));
	printf("Enter 1st number: ");	
	fgets(num1,99,stdin);
	printf("Enter 2nd number: ");	
	fgets(num2,99,stdin);
	resultMaxSize = strlen(num1)*strlen(num2);
	result = (char*)malloc((resultMaxSize+1)*sizeof(char));
	ptr1=num1;ptr2=num2;ptr3=result;
	while(*(ptr1+1)!='\n')
		ptr1+=1;
	while(*(ptr2+1)!='\n')
		ptr2+=1;
	while(ptr1>=num1 || ptr2>=num2 || carry>0){
		if((isdigit(*ptr1)||ptr1<num1) && (isdigit(*ptr2)||ptr2<num2))
		{
			if(ptr1>=num1 && ptr2>=num2){
			*ptr3 =(char)( ((*ptr1 - 48) + (*ptr2 - 48) + carry)%10 +48);
			carry = ((*ptr1 - 48) + (*ptr2 - 48)+ carry)/10;
			//printf("%c",*ptr3);
			ptr1-=1;ptr2-=1;
			ptr3+=1;
			}
			else if(ptr2>=num2){
				*ptr3 =(char)( ((*ptr2 - 48) + carry)%10 +48);
				carry = ((*ptr2 - 48)+carry)/10;
				//printf("%c",*ptr3);
//				ptr1-=1;
				ptr2-=1;
				ptr3+=1;
			}
			else if(ptr1>=num1){
				*ptr3 =(char)( ((*ptr1 - 48) + carry)%10 +48);
				carry = ((*ptr1 - 48)+carry)/10;
				//printf("%c",*ptr3);
				ptr1-=1;
//				ptr2-=1;
				ptr3+=1;

			}
			else if(carry>0){
				*ptr3=carry+48;
				ptr3+=1;
				carry=0;
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
