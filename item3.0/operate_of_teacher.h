#ifndef _TEACHER_H_
#define _TEACHER_H_

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#define NAME_LEN 20
#define PWD_LEN 20
#define STATUS_LEN 20
#define SUBJECT_LEN 20
#define WORD_LEN 100
struct tmessage
{	
	int id_work;
	char name[NAME_LEN];
	char pwd[PWD_LEN];
	char status[STATUS_LEN];
	char subject[SUBJECT_LEN];
	char word[WORD_LEN];
	int flag;
	
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
int login_of_other_teachers();
int judge();
void teacher_go_out();
int speak();
void delete_teacher();
void speak_to_teacher();
void delete_flag();
void show_word();
void mygets(char * str, int size);
#endif
