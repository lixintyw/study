#ifndef _TEACHER_H_
#define _TEACHER_H_

#include<stdio.h>

#include<stdlib.h>
#include<string.h>
#define NAME_LEN 20
#define PWD_LEN 20
struct tmessage
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


/*

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
teacher_linklist_t read_teacher_file();
void write_teacher_file(teacher_linklist_t head);
void add_teacher();
void teacher_update();
void show_teacher();
void update_teacher();
int  login_of_teacher();

void delete_teacher();
#endif
