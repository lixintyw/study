
#include "print.h"
void print_start_menu()
{
char status='\0';
	char admin_name[20]={"lixin"};
	char admin_pwd[20]={"lixin"};
	char user_name[NAME_LEN]={'\0'};
	char user_pwd[PWD_LEN]={'\0'};
	char admin_operate='0';
	char teacher_operate='0';
	char student_operate='0';

	while(1)
	{
		system("clear");
//	printf("你是谁？\n");
//printf("1-->管理员\n2-->班主任\n3-->任课老师\n4-->学生\n5-->酱油党\n");
		printf("\033[1;34m\t\t**************************************\n");
		printf("\t\t*  ********************************  *\n");
		printf("\t\t*            学生管理系统            *\n");
		printf("\t\t*            1.管理员登录            *\n");
		printf("\t\t*            2.班主任登录            *\n");
		printf("\t\t*            3.任课老师登录          *\n");
		printf("\t\t*            4.学生登录              *\n");
		printf("\t\t*            5.游客登录              *\n");
		printf("\t\t*  ********************************  *\n\033[0m");

		scanf("%c",&status);
		while(getchar()!='\n');
 		switch(status)
	 	{
			case '1':
				printf("欢迎你管理员\n");
				int flag_a=login(admin_name,admin_pwd);
				while(flag_a)
				{		
					
					int index=speak();
					if(index==1)
					{
						delete_flag();
					}
			   		printf("选择你要执行的操作\n");
				//	delete_teacher();
        			 operate_for_admin();
					 break;

				}
//switch 判定预计

				break;
			case '2':
			
				printf("欢迎你班主任\n");
				int flagt=login_of_teacher();
				while(flagt)
				{
					int flagth=judge();
					while(flagth)
					{
						printf("选择你要执行的操作\n");
						operate_for_head_teacher();
						break;
					}
					break;
				}
				break;
			case '3':
			
			   
				printf("欢迎你任课老师\n");
				int flag_o=login_of_teacher();
				while(flag_o)
				{
					int flag_oth=login_of_other_teachers();
					while(flag_oth)
					{
					//科目判选
						other_teachers();	
						break;
					}
					break;
				}
				break;
 
			case '4':

				printf("欢迎你小朋友\n");
				int flags=login_of_student();
				while(flags)
				{
					printf("选择你要执行的操作\n");
					operate_for_student();
					break;
				}
				break;

			case '5':
				printf("对不起，尚未开通游客功能\n");
				break;
			default:
				printf("没有这样的操作\n");
			break;

		}

			printf("按回车键继续\n");
			while(getchar()!='\n');
	}


}


void operate_for_admin()
{
	int flag=1;
	while(flag)
	{		
		printf("\t\t 1-->教师信息的录入\t\t 2-->教师信息的修改\n"
			"\t\t 3-->查看教师信息\t\t 4-->删除教师信息\n"
		"\t\t 5-->返回登录界面\n");
		char choose='\0';
		scanf("%c",&choose);
		while(getchar()!='\n');
		switch(choose)
		{
			case '1':
				add_teacher();
			break;
			case '2':
				update_teacher();
			break;
			case '3':
				show_teacher();
			break;
			case '4':
			//	printf("此功能尚未开通\n");
			
			delete_teacher();
			break;
			case '5':
				flag=0;
			break;
			default:
				printf("请按正确方式操作\n");
			break;
		}
	}
}


void operate_for_head_teacher()
{
	int flag=1;
	while(flag)
	{
		printf("\t\t 1-->录入学生信息\t\t 2-->查看学生信息\n"
			"\t\t 3-->修改学生信息\t\t 4-->删除学生信息\n"
			"\t\t 5-->查看排名(学号\t\t 6-->查看排名（总分）\n"
			"\t\t 7-->修改登录密码\t\t 8-->辞职\n " 	 
			"\t\t 9-->查看留言    \t\t 0-->通过姓名查看\n"
			"\t\t q-->返回登录界面\n");
				
		char choose='\0';
		scanf("%c",&choose);
		while(getchar()!='\n');
		switch(choose)
		{
			case '1':
				add_student();
				break;
			case '2':
				show_student();
				break;
			case '3':
				update_student();
				break;
			case '4':
			    delete_student();
				break;
			case '5':
				sort_by_id();
				break;
			case '6':
				sort_by_total();
				break;
			case '7':
//				update_teacher();
				
				teacher_update();
				break;
			case '8':
				teacher_go_out();
				break;
			case '9':
				show_word();
				break;
			case '0':
				show_student_by_name();
				break;
			case 'q':
				flag=0;
				break;
			default:
				printf("请按正确方式操作\n");
				break;
		}
	}
}

void other_teachers()
{	
	int flag=1;
	while(flag)		
	{
		printf("选择你所执教的科目\n");
		printf("1-->数学\t2-->语文\tq-->离开\n");
		char shun='\0';
		scanf("%c",&shun);
		while(getchar()!='\n');
		switch(shun)
		{
			case '1':
				printf("数学老师好！！\n");
				operate_of_math_teacher();
				break;
			case '2':
				printf("语文老师好！！\n");
				operate_of_chinese_teacher();
				break;
			case 'q':
				flag=0;
				break;
			default:
				printf("暂无此科目\n");
				break;
		}

	}
}



void operate_of_math_teacher()
{
	int flag=1;
	while(flag)
	{
		printf("\t\t 1-->查看学生信息   \t\t 2-->修改学生信息\n"
			"\t\t 3-->查看学生该科目排名\t\t 4-->修改登录密码\n"
			"\t\t 5-->辞职       \t\t 6-->返回上一界面\n");
		
		
		char choose='\0';
		scanf("%c",&choose);
		while(getchar()!='\n');
		switch(choose)
		{
			case '1':
				show_student_by_math();
				break;
			case '2':
				update_student_by_math();
				break;
			case '3':
				sort_by_math();
				break;
			case '4':
				teacher_update();
				break;
			case '5':
				teacher_go_out();
				break;
			case '6':
				flag=0;
				break;
			default:
				printf("没有 此类 操作\n");
				break;
		}
	}
}


void operate_of_chinese_teacher()
{
	int flag=1;
	while(flag)
	{
		printf("\t\t 1-->查看学生信息   \t\t 2-->修改学生信息\n"
			"\t\t 3-->查看学生该科目排名\t\t 4-->修改登录密码\n"
			"\t\t 5-->辞职       \t\t 6-->返回上一界面\n");
		
		
		char choose='\0';
		scanf("%c",&choose);
		while(getchar()!='\n');
		switch(choose)
		{
			case '1':
				show_student_by_chinese();
				break;
			case '2':
				update_student_by_chinese();
				break;
			case '3':
				sort_by_chinese();
				break;
			case '4':
				teacher_update();
				break;
			case '5':
				teacher_go_out();
				break;
			case '6':
				flag=0;
				break;
			default:
				printf("没有 此类 操作\n");
				break;
		}
	}
}

void operate_for_student()
{
	int flag=1;
	while(flag)
	{		
	
		printf("\t\t 1-->查看本人总分排名\t\t 2-->修改本人登录密码\n"
			"\t\t 3-->对老师留言   \t\t 4-->返回登录界面\n");

		char choose='\0';
		scanf("%c",&choose);
		while(getchar()!='\n');
		switch(choose)
		{
			case '1':
				sort_by_total();
				break;
			case '2':
				student_update();
				break;
			case '3':
				speak_to_teacher();
				break;
			case '4':
				flag=0;
				break;
			default:
				printf("请按正确方式操作\n");
				break;
		}

	}
}




















