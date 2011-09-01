#include "error.h"

#define USAGE "usage: ./part2 <program> ... \n"
extern int errno;

void
err_quit( const char *st )
{ 
  if( errno != 0 )
  {
    perror("");
  }
  write( STDERR_FILENO, st, strlen(st) );
  exit(EXIT_FAILURE);
}

void
usage()
{
  write( STDERR_FILENO, USAGE, strlen(USAGE) );
}
