#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>

typedef struct Student
{
	int iId;
	char caName[32];
	float fScore;
}STU;

void showStuInfo(const STU *stu)
{
	if (NULL != stu)
	{
		printf("id=%d, name:%s, score:%.2f\n"
			   , stu->iId, stu->caName
			   , stu->fScore);	
	}
}

#endif
