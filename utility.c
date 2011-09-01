#include "utility.h"
/*
char* basename( char* pathname )
{
  int len;
  char *st, *tmp;

  len = strlen(pathname);
  st = (char*)malloc( sizeof(char) * (len+1) );
  if( st == NULL )
  {
    err_quit("Memory Error\n"); 
  }
  strcpy( st, pathname );
  
  for( tmp = strtok(st, "/"); 
       tmp;
       tmp = strtok(NULL, "/")
     )
  ;
   
  return tmp;  
}
*/

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

     /*printf("%s\n", tmp);*/
     /* skip space */
     while( isspace(command[i]) )
       i++;
     
     k++; /* next argument */
     j=0;
  }
  
  args[k] = NULL;
  
  /* for test */
  /* 
  for( i = 0; i<k; i++)
  {
    fprintf(stderr, "%s\n", args[i]);
  }
  */ 

  /*char* test[] = { "ls", NULL };*/
  if( execvp( args[0] , args ) == -1 )
    err_quit("Execv error\n");

  /*
  if ( execv( args[0], &args[1] ) == -1 )
    err_quit("Execv error\n");;
  */
  /* for test */

}
