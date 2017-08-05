#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>

typedef unsigned int uint;
#define NAME_LEN 32
typedef struct Student
{
	uint uiId;
	char caName[NAME_LEN];
	float fScore;
}STU;

void showStuInfo(const STU *stu)
{
	printf("id:%u, name:%s, score:%.2f\n"
		   , stu->uiId, stu->caName, stu->fScore);
}

#endif 
