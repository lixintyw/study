#include<stdio.h>
int fact(int j);
int main()
{
	int i,s;
	scanf("%d",&i);
	s=fact(i);
	printf("%d\n",s);
	return 0;
}


int fact(int j)
{
	int i,mux=1;
	if(j==0&&j==1){
		mux=1;
	}
	for(i=2;i<j+1;i++){
		mux=mux*i;
	}
	return mux;
	}	
