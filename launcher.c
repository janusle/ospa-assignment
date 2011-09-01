#include<unistd.h>
#include<string.h>
#include<stdlib.h>

#include "error.h"
#include "utility.h"


#define ARVMIN 2
#define FILENAME "result"
#define NUMPROCESS 3

int 
main( int argc , const char** argv )
{
   pid_t pid;
   int fd0[2], fd1[2], i, fd;
   int result;   
   int pids[NUMPROCESS];

   if( argc < ARVMIN )
   {
     usage();
     exit(EXIT_FAILURE);
   }
 
   if( pipe(fd0) < 0 )
     err_quit("pipe error\n");

   if( pipe(fd1) < 0 )
     err_quit("pipe error\n");

   i = 0;
   if( (pid = fork() ) < 0 )
     err_quit("fork error\n");

   if( pid == 0 )  /* process 1 */
   {

      if( dup2(fd0[1], STDOUT_FILENO) == -1 )
      {
        err_quit("dup error\n"); 
      }
     
      if( argc == 2 )
      { 
            /* redirect stdout to file */
            fd = open( FILENAME, O_WRONLY | O_CREAT | O_TRUNC,
                     S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR );
            if( fd == -1 )
             err_quit("file open error\n");
   
            if( dup2(fd, STDOUT_FILENO) == -1 )
            {
              err_quit("dup error\n"); 
            }
            
      }

      /* close pipes */
      close(fd0[0]); 
      close(fd0[1]);
      close(fd1[0]);
      close(fd1[1]); 

      exec( argv[1] );
   }
   else if( argc == 2 ) /* only one argument, parent */
   {
     pids[i++] = pid; 
   }
   else if( argc > 2 ) /* parent */
   {
      pids[i++] = pid; /* record pid of process 1 */

      pid = fork();
  
      if( pid == 0 )  /* process 2 */
      {

         
         if( dup2(fd0[0], STDIN_FILENO) != STDIN_FILENO )
         {
           err_quit("dup error\n"); 
         }
        
         if( argc > 3 ) /* if there is three arguments */
         {
            if( dup2(fd1[1], STDOUT_FILENO) == -1 )/*redirect output to pipe*/
            {
              err_quit("dup error\n"); 
            }
         }
         else /* there is just two arguments, redirect to file */
         {
             
            fd = open( FILENAME, O_WRONLY | O_CREAT | O_TRUNC,
                     S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR );
            if( fd == -1 )
             err_quit("file open error\n");
   
            if( dup2(fd, STDOUT_FILENO) == -1 )
            {
              err_quit("dup error\n"); 
            }
            
         }
        
         close(fd0[0]);
         close(fd0[1]);
         close(fd1[0]);
         close(fd1[1]);

         exec( argv[2] );
      }
      else if ( pid > 0 ) /* parent */
      {
         pids[i++] = pid; /* record pid of process 2 */

         if( argc > 3 )
         {
           pid = fork(); 
           if( pid == 0 ) /* process 3 */
           {
             close(fd0[0]);
             close(fd0[1]);
             close(fd1[1]); /* close pipes */
             

             if( dup2(fd1[0], STDIN_FILENO) == -1 )
             {
               err_quit("dup error\n");
             }
             /* redirect ouput to file */
             
             fd = open( FILENAME, O_WRONLY | O_CREAT | O_TRUNC,
                      S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR );
             if( fd == -1 )
               err_quit("file open error\n");
   
             if( dup2(fd, STDOUT_FILENO) == -1 )
             {
                err_quit("dup error\n"); 
             }
            
             exec( argv[3] );
           }

           pids[i++] = pid; /* record pid of process 2 */
         }

      }
   }

   
   /* close unused pipes */
   close(fd0[0]);
   close(fd0[1]);
   close(fd1[0]);
   close(fd1[1]);


   for( i=0; i<argc-1; i++ )
   {
      pid = wait(&result);
      
      /* check if process is process one */
      if( pid == pids[0] )
      {
        printf("Process(1) with a pid of %d terminated with code %d\n",
                pid, result);
      }

      /* check if process is process two */
      if( pid == pids[1] )
      {
        printf("Process(2) with a pid of %d terminated with code %d\n",
                pid, result);
      }

      /* check if process is process three */
      if( pid == pids[2] )
      {
        printf("Process(3) with a pid of %d terminated with code %d\n",
                pid, result);
      }
   }

   return EXIT_SUCCESS;
}
