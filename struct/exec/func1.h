#ifndef _FUNC_H_
#define _FUNC_H_

#define MAX_NAME_LEN 50
#define MAX_STUDENT_LEN 100

#define MENU_ITEM_ADD 1
#define MENU_ITEM_DEL 2
#define MENU_ITEM_UPDATE 3
#define MENU_ITEM_QUERY 4
#define MENU_ITEM_PRINT 5
#define MENU_ITEM_EXIT 0

typedef struct student
{
	int id;
	char name[MAX_NAME_LEN];
	int score;
}student_t;

typedef struct line_list
{
	student_t data[MAX_STUDENT_LEN];
	int count;
}line_list_t;

void print_menu(void);

int add_student_to_list(
		line_list_t *l,
		student_t stu
		);

int del_student_from_list(
		line_list_t *l,
		student_t *p_stu
		);

int update_student_info(line_list_t *l);

int query_student_info(
		line_list_t *l,
		student_t *p_stu;
		);
int search_index_by_id(line_list_t *l,int id);

void print_students_info(line_list_t *l);

void input_student_info(student_t *p_stu);

void print_student_info(student_t stu);

int is_list_full(line_list_t *l);

int is_list_empty(line_list_t *l);

#endif
