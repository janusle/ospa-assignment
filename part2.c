#include<unistd.h>
#include<string.h>
#include<stdlib.h>

#include "error.h"

#define ARVMIN 3

int 
main( int argc , const char** argv )
{
   pid_t pid;
   int fd0[2], fd1[2];

   if( argc < ARVMIN )
   {
     usage();
     exit(EXIT_FAILURE);
   }

   if( (pid = fork() ) < 0 )
     err_quit("fork error\n");
   
   if( pipe(fd0) < 0 )
     err_quit("pipe error\n");

   if( pipe(fd1) < 0 )
     err_quit("pipe error\n");

   if( pid == 0 )  /* process 1 */
   {
      close(fd0[0]); /* close read end */
    
      if( dup2(fd[1], STDOUT_FILENO) == -1 )
      {
        err_quit("dup error\n"); 
      }

   }
   else
   {
      
   }

   return EXIT_SUCCESS;
}
