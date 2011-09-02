#ifndef UTILITY_H
#define UTILITY_H

#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<fcntl.h>

#include "error.h"
#define TMPLEN 20
#define ARGNUM 20

/* execute command */
void exec( const char* command );

/* set timeout */
int settimeout( int fd, int sec );

#endif
