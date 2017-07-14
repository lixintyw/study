#include<stdio.h>
int main()
{	
		int year,month,day,leap,week;
		int a,b,i,j;
		int count=0;
		long int total=0;
	printf("---------请选择当前的年份： ---------\n");
    scanf("%d",&year);
    getchar();
	printf("---------请输入当前的月份： ---------\n");
	scanf("%d",&month);
	getchar();
	switch (month){
		case 1:day=365;break;
		case 2:day=334;break;
		case 3:day=306;break;
		case 4:day=275;break;
		case 5:day=245;break;
		case 6:day=214;break;
		case 7:day=184;break;
		case 8:day=153;break;
		case 9:day=122;break;
		case 10:day=92;break;
		case 11:day=61;break;
		case 12:day=31;break;
		default:printf("error\n");break;
	}



	printf("星期日\t星期一\t星期二\t星期三\t星期四\t星期五\t星期六\n");
	for(i=1900;i>=year;i--){
		if((0==i%400)||((0==i%4)&&(0!=i%100))){
			leap=1;
		}else{
				leap=0;
		}
		
		if(leap == 1 && i == year && month < 2){
			count += 1;
		}else if(leap == 1 && i != year ){
			count += 1;
		}
	}
		
	total=count+(1899-year)*365+day;
	
			
	
	
	
	week=(total-1)%7;

			switch(month){
				case 1:a=31;break;
				case 2:{
					if((0==(year%400))||((0==year%4)&&(0!=year%100))){
					b=1;
					}else{
						b=0;
					}
					a=28+b;}break;
				case 3:a=31;break;
				case 4:a=30;break;
				case 5:a=31;break;
				case 6:a=30;break;
				case 7:a=31;break;
				case 8:a=31;break;
				case 9:a=30;break;
				case 10:a=31;break;
				case 11:a=30;break;
				case 12:a=31;break;
				default:printf("error\n");
			}

				
			for(i=0;i<7-week;i++){
				printf("\t");
					}	
			for(j=1;j<a+1;j++){
				printf("%d\t",j);
					
				if((0==(i+j)%7)){
						printf("\n");
				}}
				

					printf("\n");

return 0;
}



