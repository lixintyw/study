#include "operate_of_teacher.h"
teacher_linklist_t read_teacher_file()
{
	FILE *fp=fopen("teacher.txt","r");
	teacher_linklist_t temp=NULL;
	teacher_linklist_t head=NULL;

	temp=(l_teacher_t *)malloc(sizeof(l_teacher_t));
	head=(l_teacher_t *)malloc(sizeof(l_teacher_t));
	head->next=NULL;
	while(fread(temp,sizeof(l_teacher_t),1,fp)>0)
	{
		temp->next=head->next;
		head->next=temp;
		temp=NULL;
		temp=(l_teacher_t *)malloc(sizeof(l_teacher_t));
	}
	free(temp);
	temp=NULL;
	fclose(fp);
	return head;
}//通过链表的形式读出文件 
//设置头指针，使用头插法

void write_teacher_file(teacher_linklist_t head)
{
	if(NULL==head)
	{
		printf("no message to save\n");
		return ;
	}
	FILE *fp=NULL;
	fp=fopen("teacher.txt","w");
	while(head->next!=NULL)
	{
		fwrite(head->next,sizeof(l_teacher_t),1,fp);
		head=head->next;
	}
	fclose(fp);
	return;
}
	

void add_teacher()
{
	teacher_linklist_t head=read_teacher_file();
	l_teacher_t *temp=(l_teacher_t *)malloc(sizeof(l_teacher_t));


	if(temp==NULL)
	{
		printf("fail\n");
		return;
	}
	printf("input teacher name:");
	scanf("%s",temp->tdata.name);

	printf("input teacher password:");
	scanf("%s",temp->tdata.pwd);

	printf("input which class the teacher teaches:");
	scanf("%d",&temp->tdata.class);

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
	write_teacher_file(head);
	return;
}
void show_teacher()
{
	teacher_linklist_t head=read_teacher_file();
	if(head==NULL)
	{
		printf("no message\n");
		return;
	}
	printf("\t\t\t老师名单\n");
	printf("\t\t姓名\t密码\t执教班级\n");
	while(head->next!=NULL)
	{
		printf("\t\t%s\t%s\t%d\n",head->next->tdata.name,head->next->tdata.pwd,head->next->tdata.class);
		
		head=head->next;
	}
	printf("\n");
	return ;
}

void update_teacher()
{
	teacher_linklist_t head=read_teacher_file();
	teacher_linklist_t temp=(teacher_linklist_t)malloc(sizeof(l_teacher_t ));
	
	if(temp==NULL)
	{
		printf("fail!!!\n");
		return;
	}
	temp=head->next;

	int class=0;
	printf("请输入你想更改哪个班的老师\n");
	scanf("%d",&class);
	while(getchar()!='\n');

	while(temp!=NULL)
	{
	
		if(class==temp->tdata.class)
		{
		
			break;
		}
		temp=temp->next;
	}
	if(temp!=NULL)
	{
			printf("input teacher name:");
			scanf("%s",temp->tdata.name);
	
			printf("input teacher password:");
			scanf("%s",temp->tdata.pwd);

			printf("input which class the teacher teaches:");
			scanf("%d",&temp->tdata.class);

		
while(getchar()!='\n');	
	}
	else
			printf("不好意思，没有找到该班级\n");
		
	write_teacher_file(head);
	free(temp);
	return;
}
	
		
	

void delete_teacher()
{
	teacher_linklist_t head=read_teacher_file();
	teacher_linklist_t temp=(teacher_linklist_t)malloc(sizeof(l_teacher_t ));
	if(temp==NULL)
	{
		printf("fail!!\n");
		return;
	}
	temp=head->next;

	int class=0;
	printf("请输入你想删除哪个班的老师的信息\n");
	scanf("%d",&class);
	while(getchar()!='\n');

	while(temp!=NULL)
	{

		if(class==temp->next->tdata.class)
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
		printf("找不到该班级，无法删除\n");
	write_teacher_file(head);
	free(temp);
	return;
}
	

int  login_of_teacher()
{
	teacher_linklist_t head=read_teacher_file();
	teacher_linklist_t temp=(teacher_linklist_t)malloc(sizeof(l_teacher_t));

	teacher_linklist_t p=(teacher_linklist_t)malloc(sizeof(l_teacher_t));
	if(temp==NULL||p==NULL)
	{
		printf("fail!!!\n");
		printf("没有申请到空间\n");
		printf("按回车键继续\n");
		while(getchar()!='\n');
		return 0;
	}
	temp=head->next;
	int class=0;
	printf("请输入你执教的班级\n");
	scanf("%d",&class);
	while(getchar()!='\n');

	while(temp!=NULL)
	{
		if(class==temp->tdata.class)
		{
			break;
		}
		temp=temp->next;
		}
		if(temp!=NULL)
		{
			printf("请输入你的姓名：\n");
			scanf("%s",p->tdata.name);
				
		while(getchar()!='\n');	
			printf("请输入你的密码：\n");
			scanf("%s",p->tdata.pwd);

		while(getchar()!='\n');	
			if(strcmp(p->tdata.name,temp->tdata.name)==0&&strcmp(p->tdata.pwd,temp->tdata.pwd)==0)
			{
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
			printf("不好意思，没有该班级\n");
			printf("按回车键继续\n");
			while(getchar()!='\n');
			return 0;
		}
		free(temp);
		free(p);

}



void teacher_update()
{
	teacher_linklist_t head=read_teacher_file();
	teacher_linklist_t temp=(teacher_linklist_t)malloc(sizeof(l_teacher_t ));
	
	teacher_linklist_t p=(teacher_linklist_t)malloc(sizeof(l_teacher_t));
	if(temp==NULL||p==NULL)
	{
		printf("fail!!!\n");
		return ;
	}
	
	temp=head->next;

	int class=0;
	printf("请输入你是哪个班的老师\n");
	scanf("%d",&class);
	while(getchar()!='\n');

	while(temp!=NULL)
	{
	
		if(class==temp->tdata.class)
		{
		
			break;
		}
		temp=temp->next;
	}
	printf("请输入你的姓名：\n");
scanf("%s",p->tdata.name);
	while(getchar()!='\n');	
	
	printf("请输入你的密码：\n");
scanf("%s",p->tdata.pwd);
	while(getchar()!='\n');		
	if(strcmp(p->tdata.name,temp->tdata.name)==0&&strcmp(p->tdata.pwd,temp->tdata.pwd)==0)
	{
		printf("input teacher new password:");
		scanf("%s",temp->tdata.pwd);
		while(getchar()!='\n');	
		
	}else
	{
		printf("修改失败，用户名或密码不对\n");
		return ;
	}		
	write_teacher_file(head);
	free(temp);
	free(p);
	return ;
}

