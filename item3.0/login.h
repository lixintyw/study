#ifndef _LOG_H_
#define _LOG_H_
#include<stdio.h>

#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define NAME_LEN 20
#define PWD_LEN 20
/*struct tmessage
{
	char name[NAME_LEN];
	char pwd[PWD_LEN];
	int class;
};

typedef struct teacher
{
	struct tmessage tdata;
	struct teacher *next;
}l_teacher_t,*teacher_linklist_t;




struct smessage
{
	int id;
	char name[NAME_LEN];
	char pwd[NAME_LEN];
	float math;
	float chinese;
};

typedef struct student
{
	struct smessage sdata;
	struct student *next;
}l_student_t,*student_linklist_t;
*/
void myGets(char * str, int size);

int login(char * name , char * passwd);
#endif
