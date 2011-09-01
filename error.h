#ifndef ERROR_H
#define ERROR_H

#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

extern int errno;


void err_quit(const char* st);

void usage();


#endif
