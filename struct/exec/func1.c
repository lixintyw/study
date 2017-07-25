#include<stdio.h>
#include"func1.h"

void print_menu(void)
{
	printf("SQ Student Manger V1.0\n");
	printf("1.add\n");
	printf("2.del\n");
	printf("3.update\n");
	printf("4.query\n");
	printf("5.print\n");
	printf("0.exit\n");
	printf("input func no: ");
}

int add_student_to_list(
		line_list_t *l,
		student_t stu)
{
	if (is_list_full(l))
		return -1;

	l->data[l->count]=stu;
	l->count++;
	
	return 0;
}

int del_student_from_list(
		line_list_t *l,
		student_t *p_stu)
{
	if(is_list_empty(l))
		return -1;

	int index=0;
	int id=0;
	int i=0;

	printf("input id you want to delete : ");
	scanf("%d",&id);
	
	index=search_index_by_id(l,id);
	if(index==-1)
		return -1;
	if(p_stu!=NULL)
		*p_stu=l->data[index];

	for(i=index;i<l->count;i++)
		l->data[i]=l->data[i+1];
	l->count--;

	return 0;
}

int update_student_info(line_list_t *l)
{
	if(is_list_empty(l))
		return -1;

	int index=0;
	int id=0;

	printf("input id you want to update : ");
	scanf("%d",&id);

	index=search_index_by_id(l,id);

	if(index==-1)
		return -1;

	printf("current student info : \n");
	print_student_info(l->data[index]);

	printf("new name : ");
	scanf("%s",l->data[index].name);
	printf("new score : ");
	scanf("%d",&l->data[index].score);

	return 0;
}

int query_student_info(
		line_list_t *l,
		student_t *p_stu)
{
	if(is_list_empty(l))
		return -1;

	int index =0;
	int id = 0;

	printf("input id you want to query : ");
	scanf("%d",&id);

	index=search_index_by_id(l,id);

	if(index ==-1)
		return -1;

	if(p_stu!=NULL)
		*p_stu=l->data[index];

	return 0;
}

int search_index_by_id(line_list_t *l,int id)
{
	int i=0;
	for(i=0;i<l->count;i++)
	{
		if(l->data[i].id==id)
			return i;
	}

	return -1;
}
void print_students_info(line_list_t *l)
{
	int i=0;
	
	printf("id\tname\tscore\n");

	for(i=0;i<l->count;i++)
		print_student_info(l->data[i]);
}
void input_student_info(student_t *p_stu)
{
	if(p_stu==NULL)
		return;

	printf("id : ");
	scanf("%d",&(p_stu->id));
	printf("name: ");
	scanf("%s",p_stu->name);
	printf("score : ");
	scanf("%d",&(p_stu->score));
}

void print_student_info(student_t stu)
{
	printf("%d\t%s\t%d\n",stu.id,stu.name,stu.score);
}

int is_list_full(line_list_t *l)
{
	return l->count==MAX_STUDENT_LEN;
}

int is_list_empty(line_list_t *l)
{
	return l->count==0;
}








































































































