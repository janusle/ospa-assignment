#include "utility.h"

void
exec( const char* command )
{
  char *args[ARGNUM];
  char tmp[TMPLEN]; 
  int i, j, k, len; 

  /* explode the command */ 
  len = strlen(command);
  i = j = k = 0;
  while( i< len )
  { 
     while( isgraph(command[i]) )
     {
       tmp[j++] = command[i++];
     }
     tmp[j] = '\0'; 
     args[k] = (char*)malloc( sizeof(char) * strlen(tmp) ); 

     if( args[k] == NULL )
        err_quit("Memory error\n");
     strcpy( args[k] , tmp );

     /* skip space */
     while( isspace(command[i]) )
       i++;
     
     k++; /* next argument */
     j=0;
  }
  
  args[k] = NULL;
  

  if( execvp( args[0] , args ) == -1 )
    err_quit("Execv error\n");


}
