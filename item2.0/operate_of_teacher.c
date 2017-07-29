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
	char status[STATUS_LEN]={'\0'};
	char subject[SUBJECT_LEN]={'\0'};
	int index;

	if(temp==NULL)
	{
		printf("fail\n");
		return;
	}
	printf("input teacher id_work:\n");
	scanf("%d",&temp->tdata.id_work);
	while(getchar()!='\n');	
	printf("\n");
	printf("input teacher name:\n");
	scanf("%s",temp->tdata.name);
	while(getchar()!='\n');	

	printf("\n");
	printf("input teacher password:\n");
	scanf("%s",temp->tdata.pwd);
	while(getchar()!='\n');	

	printf("\n");
	printf("input the status of teacher:\n");
	printf("\n");
	printf("1 for head teacher 0 for other teacher\n");
	scanf("%s",status);
	while(getchar()!='\n');	
	while((strcmp(status,"1")!=0)&&strcmp(status,"0")!=0)
	{
		printf("录入错误，请重新再来\n");
		return;
	}
	strcpy(temp->tdata.status,status);

	printf("\n");
	printf("input which subject you teach\n");
	printf("\n");
	printf("head for head teacher and math for math teacher and so on\n");
	scanf("%s",subject);
	while(getchar()!='\n');
	while(strcmp(subject,"head")!=0&&strcmp(subject,"math")!=0&&strcmp(subject,"chinese")!=0)
	{
		printf("录入失败，请重新再来\n");
		return;
	}
	strcpy(temp->tdata.subject,subject);

	printf("\n");
	printf("input wheather this teacher go out\n");
	printf("\n");
	printf("1 for go out and 0 for stay\n");
	scanf("%d",&index);
	while(getchar()!='\n');	
	while(index!=0&&index!=1)
	{
		printf("录入失败，请重新再来\n");
		return;
	}
	temp->tdata.flag=index;


//	printf("\n");
//	printf("input which subject the teacher teaches:");
//	scanf("%s",temp->tdata.subject);
//	while(getchar()!='\n');	
	
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
	printf("工号\t姓名\t密码\t职位\t执教科目\t是否离职\n");
	while(head->next!=NULL)
	{
		printf("%d\t",head->next->tdata.id_work);
		printf("%s\t",head->next->tdata.name);
		printf("%s\t",head->next->tdata.pwd);
		printf("%s\t",head->next->tdata.status);
		printf("%s\t",head->next->tdata.subject);
		printf("\t%d\n",head->next->tdata.flag);
		head=head->next;
	}
	printf("\n");
	return ;
}

void update_teacher()
{
	teacher_linklist_t head=read_teacher_file();
	teacher_linklist_t temp=(teacher_linklist_t)malloc(sizeof(l_teacher_t ));
	
	char status[STATUS_LEN]={'\0'};
	char subject[SUBJECT_LEN]={'\0'};
	int index;
	if(temp==NULL)
	{
		printf("fail!!!\n");
		return;
	}
	temp=head->next;

	int id=0;
	printf("请输入你想更改工号为什么的老师？\n");
	scanf("%d",&id);
	while(getchar()!='\n');

	while(temp!=NULL)
	{
	
		if(id==temp->tdata.id_work)
		{
		
			break;
		}
		temp=temp->next;
	}
	if(temp!=NULL)
	{
//直接修改，管理员	
		printf("\n");
		printf("input teacher name:\n");
		scanf("%s",temp->tdata.name);
		while(getchar()!='\n');	
	
		printf("\n");
		printf("input teacher password:\n");
		scanf("%s",temp->tdata.pwd);
		while(getchar()!='\n');	

		printf("\n");
		printf("input the status of teacher:\n");
		printf("\n");
		printf("1 for head teacher 0 for other teacher\n");
		scanf("%s",status);
		while(getchar()!='\n');	
		while((strcmp(status,"1")!=0)&&strcmp(status,"0")!=0)
		{
			printf("修改错误，请重新再来\n");
			return;
		}
		strcpy(temp->tdata.status,status);

		printf("\n");
		printf("input which subject you teach\n");
		printf("\n");
		printf("head for head teacher and math for math teacher and so on\n");
		scanf("%s",subject);
		while(getchar()!='\n');
		while(strcmp(subject,"head")!=0&&strcmp(subject,"math")!=0&&strcmp(subject,"chinese")!=0)
		{
			printf("修改失败，请重新再来\n");
			return;
		}
		strcpy(temp->tdata.subject,subject);

		printf("\n");
		printf("input wheather this teacher go out\n");
		printf("\n");
		printf("1 for go out and 0 for stay\n");
		scanf("%d",&index);
		while(getchar()!='\n');	
		while(index!=0&&index!=1)
		{
			printf("修改失败，请重新再来\n");
			return;
		}
		temp->tdata.flag=index;


//		printf("\n");
//		printf("input which subject the teacher teaches:");
//		scanf("%s",temp->tdata.subject);
//		while(getchar()!='\n');	
	}
	else
			printf("不好意思，没有找到该老师\n");
		
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

	int id=0;
	printf("请输入你想删除哪个老师\n");
	scanf("%d",&id);
	while(getchar()!='\n');

	while(temp!=NULL)
	{

		if(id==temp->next->tdata.id_work)
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
	write_teacher_file(head);
	free(temp);temp=NULL;
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
	int id;
	printf("请输入你的工号\n");
	scanf("%d",&id);
	while(getchar()!='\n');

	while(temp!=NULL)
	{
		if(id==temp->tdata.id_work)
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

int login_of_other_teachers()
{
	teacher_linklist_t head=read_teacher_file();
	teacher_linklist_t temp=(teacher_linklist_t)malloc(sizeof(l_teacher_t ));
	if(temp==NULL)
	{
		printf("fail!!\n");
		return 0;
	}
	temp=head->next;

	int id=0;
	char subject[20]={'\0'};
	printf("请输入你的工号是多少\n");
	scanf("%d",&id);
	while(getchar()!='\n');

	while(temp!=NULL)
	{

		if(id==temp->next->tdata.id_work)
		{
			break;
		}
		temp=temp->next;
	}
	if(temp!=NULL)
	{
		printf("请输入你执教的科目\n");
		printf("此处为初始登录，请输入科目全称\n");
		scanf("%s",subject);
		while(getchar()!='\n');
		if(strcmp(subject,temp->next->tdata.subject)==0)
		{
			printf("欢迎登录\n");
			return 1;
		}
		else
		{
			printf("id与执教科目不符\n");
			return 0;
		}
	}
}
void speak()
{
	teacher_linklist_t head=read_teacher_file();

	teacher_linklist_t temp=(teacher_linklist_t)malloc(sizeof(l_teacher_t ));
	int id=0;
	char judge='\0';
	if(temp==NULL)
	{
		printf("fail!!!\n");
		return;
	}
	temp=head->next;
	while(temp!=NULL)
	{		
		if(temp->tdata.flag==1)
		{
			break;
		}
		temp=temp->next;		
	}
	if(temp!=NULL)			
	{			
		id=temp->tdata.id_work;
		printf("工号为%d的老师申请离职是否同意\n",id);
		printf("y表示同意\n");
		scanf("%c",&judge);
		while(getchar()!='\n');
		if(judge!='y')
		{
			temp->tdata.flag=0;
			
		}
		else
			return;
	}
	write_teacher_file(head);
	free(temp);
	return;
}


void teacher_update()
{
	teacher_linklist_t head=read_teacher_file();
	teacher_linklist_t temp=(teacher_linklist_t)malloc(sizeof(l_teacher_t ));
	
	teacher_linklist_t p=(teacher_linklist_t)malloc(sizeof(l_teacher_t));

	char pwd[PWD_LEN]={'\0'};
	char newpwd[PWD_LEN]={'\0'};
	if(temp==NULL||p==NULL)
	{
		printf("fail!!!\n");
		return ;
	}
	
	temp=head->next;

	int id=0;
	printf("请输入你的工号\n");
	scanf("%d",&id);
	while(getchar()!='\n');

	while(temp!=NULL)
	{
	
		if(id==temp->tdata.id_work)
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
		scanf("%s",pwd);
		while(getchar()!='\n');	
		
		printf("input teacher new password again:");
		scanf("%s",newpwd);
		while(getchar()!='\n');

		if(strcmp(pwd,newpwd)==0)
		{			
			strcpy(temp->tdata.pwd,pwd);
		}
		else
		{
			printf("输入错误，两次密码不一样\n");
			return;
		}
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

void teacher_go_out()
{
	teacher_linklist_t head=read_teacher_file();
	teacher_linklist_t temp=(teacher_linklist_t)malloc(sizeof(l_teacher_t ));
	
	teacher_linklist_t p=(teacher_linklist_t)malloc(sizeof(l_teacher_t));

	int index=0;
	
	if(temp==NULL||p==NULL)
	{
		printf("fail!!!\n");
		return ;
	}
	
	temp=head->next;

	int id=0;
	printf("请输入你的工号\n");
	scanf("%d",&id);
	while(getchar()!='\n');

	while(temp!=NULL)
	{
	
		if(id==temp->tdata.id_work)
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
		printf("是否离职\n");
		printf("离职为1，留下来为0\n");
		scanf("%d",&index);
		while(getchar()!='\n');	
		
	//	printf("input teacher new password again:");
	//	scanf("%s",newpwd);
	//	while(getchar()!='\n');

	//	if(strcmp(pwd,newpwd)==0)
	//	{			
		temp->tdata.flag=index;
	//	}
	//	else
	//	{
	//		printf("输入错误，两次密码不一样\n");
	//		return;
	
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
int  judge()
{
	teacher_linklist_t head=read_teacher_file();
	int id=0;
	printf("请再次输入id\n");
	scanf("%d",&id);
	while(getchar()!='\n');
	
	if(head==NULL)
	{
		printf("fail!!!\n");
		return 0;
	}
	head=head->next;
	while(head!=NULL)
	{		
		if(head->tdata.id_work==id)
		{
			break;
		}
		head=head->next;		
	}
	if(head!=NULL)			
	{			
		if(strcmp(head->tdata.status,"1")==0)
			return 1;
		else
		{
			printf("不是班主任，权限不够\n");
		return 0;
		}
	
	}
	else
	{
		printf("没有这个id\n");
		return 0;
	}
}


void show_word()
{
	teacher_linklist_t head=read_teacher_file();
	int id=0;
	printf("请再次输入id\n");
	scanf("%d",&id);
	while(getchar()!='\n');

	if(head==NULL)
	{
		printf("fail!!\n");
		return;
	}
	head=head->next;
	while(head!=NULL)
	{
		if(head->tdata.id_work==id)
		{
			break;
		}
		head=head->next;
	}
	if(head!=NULL)
	{
		printf("%s\n",head->tdata.word);
	}
	else
	{
		printf("没有这个id\n");
		return;
	}
}
void speak_to_teacher()
{
	teacher_linklist_t head=read_teacher_file();
	teacher_linklist_t temp=(teacher_linklist_t)malloc(sizeof(l_teacher_t ));
	
	
	if(temp==NULL)
	{
		printf("fail!!!\n");
		return ;
	}
	
	temp=head->next;

	int id=0;
	char word[100]={'\0'};
	printf("请输入你想留言的老师的工号\n");
	scanf("%d",&id);
	while(getchar()!='\n');

	while(temp!=NULL)
	{
	
		if(id==temp->tdata.id_work)
		{
		
			break;
		}
		temp=temp->next;
	}
	if(temp!=NULL)
	{
		printf("请输入想留言的内容\n");
		mygets(word,100);
		strcpy(temp->tdata.word,word);
	}
		
	else
	{
		printf("留言失败，无此工号\n");
		return;
	}
	write_teacher_file(head);
	free(temp);
	return;
}



void mygets(char * str, int size)
{
	int i = 0 ;
	for(i = 0 ; i < size -1 ; i++)
	{
		str[i] = getchar();
		if(str[i] == '\n')
		{
			break;
		}
	}
	str[i] = '\0';
	if(i == size -1){
		while(getchar() != '\n');
	}
}














	

















