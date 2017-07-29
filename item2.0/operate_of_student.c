#include "operate_of_student.h"
student_linklist_t read_student_file()
{
	FILE *fp=fopen("student.txt","r");
	student_linklist_t temp=NULL;
	student_linklist_t head=NULL;

	temp=(l_student_t *)malloc(sizeof(l_student_t));
	head=(l_student_t *)malloc(sizeof(l_student_t));
	head->next=NULL;
	while(fread(temp,sizeof(l_student_t),1,fp)>0)
	{
		temp->next=head->next;
		head->next=temp;
		temp=NULL;
		temp=(l_student_t *)malloc(sizeof(l_student_t));
	}
	free(temp);
	temp=NULL;
	fclose(fp);
	return head;
}//通过链表的形式读出文件 
//设置头指针，使用头插法

void write_student_file(student_linklist_t head)
{
	if(NULL==head)
	{
		printf("no message to save\n");
		return ;
	}
	FILE *fp=NULL;
	fp=fopen("student.txt","w");
	while(head->next!=NULL)
	{
		fwrite(head->next,sizeof(l_student_t),1,fp);
		head=head->next;
	}
	fclose(fp);
	return;
}
	

void add_student()
{
	student_linklist_t head=read_student_file();
	l_student_t *temp=(l_student_t *)malloc(sizeof(l_student_t));


	if(temp==NULL)
	{
		printf("fail\n");
		return;
	}
	printf("input student id:");
	scanf("%d",&temp->sdata.id);

		while(getchar()!='\n');	
	printf("input student name:");
	scanf("%s",temp->sdata.name);

		while(getchar()!='\n');	
	printf("input student password:");
	scanf("%s",temp->sdata.pwd);

		while(getchar()!='\n');	
	printf("input student math:");
	scanf("%f",&temp->sdata.math);

		while(getchar()!='\n');	
	printf("input student chinese:");
	scanf("%f",&temp->sdata.chinese);
	
while(getchar()!='\n');	


	if(head->next!=NULL)
	{
		temp->next=head->next;
		head->next=temp;
	}//头插
	else
	{
		head->next=temp;
	}
	write_student_file(head);
	return;
}
void show_student()
{
	student_linklist_t head=read_student_file();
	if(head==NULL)
	{
		printf("no message\n");
		return;
	}
	printf("学号\t姓名\t密码\t数学\t语文\n");
	
	while(head->next!=NULL)
	{
		printf("%d\t%s\t%s\t%.2f\t%.2f\n",head->next->sdata.id,head->next->sdata.name,head->next->sdata.pwd,head->next->sdata.math,head->next->sdata.chinese);
		
		head=head->next;
	}
	printf("\n");
	return ;
}

void show_student_by_math()
{
	student_linklist_t head=read_student_file();
	if(head==NULL)
	{
		printf("no message\n");
		return;
	}
	printf("学号\t姓名\t数学\n");
	
	while(head->next!=NULL)
	{
		printf("%d\t%s\t%.2f\n",head->next->sdata.id,head->next->sdata.name,head->next->sdata.math);
		
		head=head->next;
	}
	printf("\n");
	return ;
}

void show_student_by_chinese()
{
	student_linklist_t head=read_student_file();
	if(head==NULL)
	{
		printf("no message\n");
		return;
	}
	printf("学号\t姓名\t语文\n");
	
	while(head->next!=NULL)
	{
		printf("%d\t%s\t%.2f\n",head->next->sdata.id,head->next->sdata.name,head->next->sdata.chinese);
		
		head=head->next;
	}
	printf("\n");
	return ;
}

void sort_by_id()
{
	student_linklist_t head=read_student_file();
	if(head==NULL)
	{
		printf("no message\n");
		return;
	}
	student_linklist_t p1=head->next;
	student_linklist_t low=NULL;
	student_linklist_t p2=NULL;

	student_linklist_t temp=NULL;
	temp=(student_linklist_t)malloc(sizeof(l_student_t));
	temp->next=NULL;

	while(p1!=NULL)
	{
		low=p1;
		p2=p1->next;
		while(p2!=NULL)
		{
			if(low->sdata.id>p2->sdata.id)
			{
				low=p2;
				p2=p2->next;
			}
			else
			{
				p2=p2->next;
			}
		}
		if(low!=p1)
		{
			temp->sdata=low->sdata;
			low->sdata=p1->sdata;
			p1->sdata=temp->sdata;
		}
		p1=p1->next;
	}
	printf("学号\t姓名\t数学\t语文\n");
	while(head->next!=NULL)
	{
		printf("%d\t%s\t%.2f\t%.2f\n",head->next->sdata.id,head->next->sdata.name,head->next->sdata.math,head->next->sdata.chinese);
		head=head->next;
	}
	return;
}


void sort_by_total()
{
	student_linklist_t head=read_student_file();
	if(head==NULL)
	{
		printf("no message\n");
		return;
	}
	student_linklist_t p1=head->next;
	student_linklist_t low=NULL;
	student_linklist_t p2=NULL;

	student_linklist_t temp=NULL;
	temp=(student_linklist_t)malloc(sizeof(l_student_t));
	temp->next=NULL;

	while(p1!=NULL)
	{
		low=p1;
		p2=p1->next;
		while(p2!=NULL)
		{
			if((low->sdata.math+low->sdata.chinese)<(p2->sdata.math+p2->sdata.chinese))
			{
				low=p2;
				p2=p2->next;
			}
			else
			{
				p2=p2->next;
			}
		}
		if(low!=p1)
		{
			temp->sdata=low->sdata;
			low->sdata=p1->sdata;
			p1->sdata=temp->sdata;
		}
		p1=p1->next;
	}
	printf("学号\t姓名\t数学\t语文\n");
	while(head->next!=NULL)
	{
		printf("%d\t%s\t%.2f\t%.2f\n",head->next->sdata.id,head->next->sdata.name,head->next->sdata.math,head->next->sdata.chinese);
		head=head->next;
	}
	return;
}

void sort_by_math()
{
	student_linklist_t head=read_student_file();
	if(head==NULL)
	{
		printf("no message\n");
		return;
	}
	student_linklist_t p1=head->next;
	student_linklist_t low=NULL;
	student_linklist_t p2=NULL;

	student_linklist_t temp=NULL;
	temp=(student_linklist_t)malloc(sizeof(l_student_t));
	temp->next=NULL;

	while(p1!=NULL)
	{
		low=p1;
		p2=p1->next;
		while(p2!=NULL)
		{
			if(low->sdata.math<p2->sdata.math)
			{
				low=p2;
				p2=p2->next;
			}
			else
			{
				p2=p2->next;
			}
		}
		if(low!=p1)
		{
			temp->sdata=low->sdata;
			low->sdata=p1->sdata;
			p1->sdata=temp->sdata;
		}
		p1=p1->next;
	}
	printf("学号\t姓名\t数学\n");
	while(head->next!=NULL)
	{
		printf("%d\t%s\t%.2f\n",head->next->sdata.id,head->next->sdata.name,head->next->sdata.math);
		head=head->next;
	}
	return;
}

void sort_by_chinese()
{
	student_linklist_t head=read_student_file();
	if(head==NULL)
	{
		printf("no message\n");
		return;
	}
	student_linklist_t p1=head->next;
	student_linklist_t low=NULL;
	student_linklist_t p2=NULL;

	student_linklist_t temp=NULL;
	temp=(student_linklist_t)malloc(sizeof(l_student_t));
	temp->next=NULL;

	while(p1!=NULL)
	{
		low=p1;
		p2=p1->next;
		while(p2!=NULL)
		{
			if(low->sdata.chinese<p2->sdata.chinese)
			{
				low=p2;
				p2=p2->next;
			}
			else
			{
				p2=p2->next;
			}
		}
		if(low!=p1)
		{
			temp->sdata=low->sdata;
			low->sdata=p1->sdata;
			p1->sdata=temp->sdata;
		}
		p1=p1->next;
	}
	printf("学号\t姓名\t语文\n");
	while(head->next!=NULL)
	{
		printf("%d\t%s\t%.2f\n",head->next->sdata.id,head->next->sdata.name,head->next->sdata.chinese);
		head=head->next;
	}
	return;
}



void update_student_by_math()
{
	student_linklist_t head=read_student_file();
	student_linklist_t temp=(student_linklist_t)malloc(sizeof(l_student_t ));
	
	if(temp==NULL)
	{
		printf("fail!!!\n");
		return;
	}
	temp=head->next;

	int id=0;
	printf("请输入你想更改的学生的学号\n");
	scanf("%d",&id);
	while(getchar()!='\n');

	while(temp!=NULL)
	{
	
		if(id==temp->sdata.id)
		{
			break;
		}
		temp=temp->next;
	}
	if(temp!=NULL)
	{
		
		printf("input student math:");
		scanf("%f",&temp->sdata.math);

		while(getchar()!='\n');	
	}
	else
			printf("不好意思，没有找到该学生\n");
		
	write_student_file(head);
	free(temp);
	return;

}



void update_student_by_chinese()
{
	student_linklist_t head=read_student_file();
	student_linklist_t temp=(student_linklist_t)malloc(sizeof(l_student_t ));
	
	if(temp==NULL)
	{
		printf("fail!!!\n");
		return;
	}
	temp=head->next;

	int id=0;
	printf("请输入你想更改的学生的学号\n");
	scanf("%d",&id);
	while(getchar()!='\n');

	while(temp!=NULL)
	{
	
		if(id==temp->sdata.id)
		{
			break;
		}
		temp=temp->next;
	}
	if(temp!=NULL)
	{
		
		printf("input student chinese:");
		scanf("%f",&temp->sdata.chinese);

		while(getchar()!='\n');	
	}
	else
			printf("不好意思，没有找到该学生\n");
		
	write_student_file(head);
	free(temp);
	return;
}

void update_student()
{
	student_linklist_t head=read_student_file();
	student_linklist_t temp=(student_linklist_t)malloc(sizeof(l_student_t ));
	
	if(temp==NULL)
	{
		printf("fail!!!\n");
		return;
	}
	temp=head->next;

	int id=0;
	printf("请输入你想更改的学生的学号\n");
	scanf("%d",&id);
	while(getchar()!='\n');

	while(temp!=NULL)
	{
	
		if(id==temp->sdata.id)
		{
		
			break;
		}
		temp=temp->next;
	}
	if(temp!=NULL)
	{
		
		printf("input student id:");
		scanf("%d",&temp->sdata.id);

		while(getchar()!='\n');	
		printf("input student name:");
		scanf("%s",temp->sdata.name);

		while(getchar()!='\n');	
		printf("input student password:");
		scanf("%s",temp->sdata.pwd);

		while(getchar()!='\n');	
		printf("input student math:");
		scanf("%f",&temp->sdata.math);

		while(getchar()!='\n');	
		printf("input student chinese:");
		scanf("%f",&temp->sdata.chinese);
	
		while(getchar()!='\n');	
	}
	else
			printf("不好意思，没有找到该学生\n");
		
	write_student_file(head);
	free(temp);
	return;

}

int  login_of_student()
{
	student_linklist_t head=read_student_file();
	student_linklist_t temp=(student_linklist_t)malloc(sizeof(l_student_t));

	student_linklist_t p=(student_linklist_t)malloc(sizeof(l_student_t));
	if(temp==NULL||p==NULL)
	{
		printf("fail!!!\n");
		printf("没有申请到空间\n");
		printf("按回车键继续\n");
		while(getchar()!='\n');
		return 0;
	}
	temp=head->next;
	int id=0;
	printf("请输入你的学号\n");
	scanf("%d",&id);
	while(getchar()!='\n');

	while(temp!=NULL)
	{
		if(id==temp->sdata.id)
		{
			break;
		}
		temp=temp->next;
		}
		if(temp!=NULL)
		{
			printf("请输入你的姓名：\n");
			scanf("%s",p->sdata.name);
			while(getchar()!='\n');	
			printf("请输入你的密码：\n");
			scanf("%s",p->sdata.pwd);
			while(getchar()!='\n');
			if(strcmp(p->sdata.name,temp->sdata.name)==0&&strcmp(p->sdata.pwd,temp->sdata.pwd)==0)
			{
	//			printf("账号密码正确\n");
				return 1;
			}
			else
			{
				printf("输入错误，密码与用户名不符\n");
			
				printf("按回车键继续\n");
				while(getchar()!='\n');
				return 0;
			}	
		}
		else 
		{
			printf("不好意思，没有该id\n");
			printf("按回车键继续\n");
			while(getchar()!='\n');
			return 0;
		}
		free(temp);
		free(p);

}


void delete_student()
{
	student_linklist_t head=read_student_file();
	student_linklist_t temp=(student_linklist_t)malloc(sizeof(l_student_t ));
	if(temp==NULL)
	{
		printf("fail!!\n");
		return;
	}
	temp=head;

	int id=0;
	printf("请输入你想删除哪个学生的id\n");
	scanf("%d",&id);
	while(getchar()!='\n');

	while(temp!=NULL)
	{

		if(id==temp->next->sdata.id)
		{	
			break;
		}
		temp=temp->next;
	}
	if(temp!=NULL)
	{
		temp->next=temp->next->next;
	}
	else 
		printf("找不到该id，无法删除\n");
	write_student_file(head);
	free(temp),temp=NULL;
	return;
}
	
void student_update()
{
	student_linklist_t head=read_student_file();
	student_linklist_t temp=(student_linklist_t)malloc(sizeof(l_student_t ));
	
	student_linklist_t p=(student_linklist_t)malloc(sizeof(l_student_t));

	char pwd[PWD_LEN]={'\0'};
	char newpwd[PWD_LEN]={'\0'};
	if(temp==NULL||p==NULL)
	{
		printf("fail!!!\n");
		return;
	}
	temp=head->next;

	int id=0;
	printf("请输入你的id\n");
	scanf("%d",&id);
	while(getchar()!='\n');

	while(temp!=NULL)
	{
	
		if(id==temp->sdata.id)
		{
		
			break;
		}
		temp=temp->next;
	}

	printf("请输入你的姓名：\n");
	scanf("%s",p->sdata.name);
	while(getchar()!='\n');	
	
	printf("请输入你的密码：\n");
	scanf("%s",p->sdata.pwd);
	while(getchar()!='\n');		
	if(strcmp(p->sdata.name,temp->sdata.name)==0&&strcmp(p->sdata.pwd,temp->sdata.pwd)==0)
	{
		printf("input student password:");
		scanf("%s",pwd);
		while(getchar()!='\n');

		printf("input student password again:");
		scanf("%s",newpwd);
		while(getchar()!='\n');

		if(strcmp(pwd,newpwd)==0)
		{			
			strcpy(temp->sdata.pwd,pwd);
		}
		else
		{
			printf("输入错误，两次密码不一样\n");
			return;
		}
	}else
	{
		printf("不好意思,用户名或密码错误\n");
		return;
	}	
	write_student_file(head);
	free(temp);
	free(p);
	return;
}



























