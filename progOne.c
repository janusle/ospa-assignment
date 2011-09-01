#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>

#define TMPLEN 200

int 
main()
{
  pid_t pid;
  char *errmsg = "Fork error\n";
  char tmp[TMPLEN];

  int x = 10, y = 20, result;

  if( (pid = fork()) <0 )
  {
    perror("fork error");  
    exit(EXIT_FAILURE);
  }
  else if( pid == 0 ) /* child */
  {
    sprintf(tmp, "Hi I am the child, my PID is %d \n", getpid() );
    write( STDOUT_FILENO, tmp, strlen(tmp) );
    
    sprintf(tmp, "Child again, my parent\'s PID is %d \n", getppid() );
    write( STDOUT_FILENO, tmp, strlen(tmp) );

    sprintf(tmp, "Child again, the address of y before assignment is %p \n",
            (void*)&y);
    write( STDOUT_FILENO, tmp, strlen(tmp) );

    y = 20 * x;
 
    sprintf(tmp, "Child again, the address of y after assignment is %p \n",
            (void*)&y);
    write( STDOUT_FILENO, tmp, strlen(tmp) );

    sprintf(tmp, "Child: the value of y is %d \n", y );
    write( STDOUT_FILENO, tmp, strlen(tmp) );

  }
  else {             /* parent */
    
   sprintf(tmp, "Hi, I am the parent, my PID is %d \n", getpid() ); 
   write( STDOUT_FILENO, tmp, strlen(tmp) );

   sprintf(tmp, "Parent again, my child\'s PID is %d \n", pid );
   write( STDOUT_FILENO, tmp, strlen(tmp) );
    
   sprintf(tmp, "Parent again, the address of y is %p \n", (void*)&y ); 
   write( STDOUT_FILENO, tmp, strlen(tmp) );

   pid = wait( &result );
    
   sprintf(tmp,"The child process with a pid of %d terminated with code %d \n"
            , pid, result );
   write( STDOUT_FILENO, tmp, strlen(tmp) );

  }
  return 0;
}
