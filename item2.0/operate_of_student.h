
#ifndef _STUDENT_H_
#define _STUDENT_H_

#include<stdio.h>

#include<stdlib.h>
#include<string.h>
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


*/

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

student_linklist_t read_student_file();
void write_student_file(student_linklist_t head);
void add_student();

void show_student();
void update_student();
void show_student_by_math();
void show_student_by_chinese();
int  login_of_student();
void delete_student();
void sort_by_id();
void sort_by_math();
void sort_by_chinese();
void update_student_by_math();
void update_student_by_chinese();
void student_update();
void sort_by_total();
#endif
