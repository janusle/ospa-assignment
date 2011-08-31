#include "utility.h"

char* basename( char* pathname )
{
  int len;
  char *st;

  len = strlen(pathname);
  st = (char*)malloc( sizeof(char) * (len+1) );
  if( st == NULL )
  {
    err_quit("Memory Error\n"); 
  }
  strcpy( st, pathname );
  
   
}


int 
exec( const char* command )
{
  char tmp[TMPLEN][TMPLEN];
  int i, j, k, len;

  /* explode the command */ 
  len = strlen(command);
  i = j = k = 0;
  while( i< len )
  {
     while( isgraph(command[i]) )
     {
       tmp[k][j++] = command[i++];
     }
     tmp[k][j] = '\0'; 

     /* skip space */
     while( isspace(command[i++]) )
     ;
     
     k++; /* next argument */
     j=0;
  }
  
  tmp[k][0] = '\0';
 

  /* for test */
}
