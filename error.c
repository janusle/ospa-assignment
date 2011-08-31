#include "error.h"

#define USAGE "usage: ./part2 <program> ... \n"

void
err_quit( const char *st )
{ 
  write( STDERR_FILENO, st, strlen(st) );
  exit(EXIT_FAILURE);
}

void
usage()
{
  write( STDERR_FILENO, USAGE, strlen(USAGE) );
}
