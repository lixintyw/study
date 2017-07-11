#include<stdio.h>
int main()
{
		int age;
		char sex;

		printf("请输入你的年龄\n");
		scanf("%d",&age);
		getchar();
		if(age<=15)
		
				printf("人小鬼大，这里少儿不宜，快点回家\n");
		else		
		{   	printf("请输入你的性别\n男士为“M”，女士为“F”\n");
				           scanf("%c",&sex);
		}
		if(age>15&&age<=18&&sex=='M')
				printf("小伙子白又白，叔叔有套来不来\n");
		if(age>15&&age<=18&&sex=='F')
				printf("妹妹，你的问题很严重啊！晚上来我房间\n");
	    if(age>18&&age<=30)
				printf("进击的老司机\n");
	    if(age>30&&age<=45)
				printf("好饥渴啊，朋友！\n");
	    if(age>45&&age<=60)
				printf("大爷大妈，你们过分了啊！\n");
		if(age>60)
				printf("人心不古老流氓！\n");
		return 0;
}
				 
				  

