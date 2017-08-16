#ifndef FILE_H
#define FILE_H

#include "public.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "list.h"

#define USRINFO_PATH  "./usr.info"

int open_file(const char *pathname, int flags);
void save_usr_info_to_file(const char *pathname
				       , const List *list);
void get_usr_info_fromFile(const char *pathname
				        , List *list);

#endif
