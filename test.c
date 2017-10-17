/*
#include "types.h"
#include "stat.h"
#include "user.h"

// TEST CODE LAB 1 PART 1
int main( int argc, char *argv[] )
{
    int pid = fork();

    if ( pid == 0 )
    {
        hello();
    }

    else if ( pid > 0 )
    {    
        waitpid(pid, 0);
        hello();
        hello();
    }

    exit(0);

    return 0;
}*/

/*
#include "types.h"
#include "user.h"

// TEST CODE LAB 1 PART 2
int main(int argc, char *argv[])
{
	
	int exitWait(void);
	int waitPid(void);
	int PScheduler(void);

  printf(1, "\n This program tests the correctness of your lab#1\n");
  
  if (atoi(argv[1]) == 1)
	exitWait();
  else if (atoi(argv[1]) == 2)
	waitPid();
  else if (atoi(argv[1]) == 3)
	PScheduler();
  else 
   printf(1, "\ntype \"lab1 1\" to test exit and wait, \"lab1 2\" to test waitpid and \"lab1 3\" to test the priority scheduler \n");
  
    // End of test
	 exit(0);
 }
  
  
int exitWait(void) {
	  int pid, ret_pid, exit_status;
       int i;
  // use this part to test exit(int status) and wait(int* status)
 
  printf(1, "\n  Step 1: testing exit(int status) and wait(int* status):\n");

  for (i = 0; i < 2; i++) {
    pid = fork();
    if (pid == 0) { // only the child executed this code
      if (i == 0)
      {
      printf(1, "\nThis is child with PID# %d and I will exit with status %d\n", getpid(), 0);
      exit(0);
  }
      else
      {
	 printf(1, "\nThis is child with PID# %d and I will exit with status %d\n" ,getpid(), -1);
      exit(-1);
  } 
    } else if (pid > 0) { // only the parent exeecutes this code
      ret_pid = wait(&exit_status);
      printf(1, "\n This is the parent: child with PID# %d has exited with status %d\n", ret_pid, exit_status);
    } else  // something went wrong with fork system call
    {  
	  printf(2, "\nError using fork\n");
      exit(-1);
    }
  }
  return 0;
}

int waitPid(void){
	
  int ret_pid, exit_status;
  int i;
  int pid_a[5]={0, 0, 0, 0, 0};
 // use this part to test wait(int pid, int* status, int options)

 printf(1, "\n  Step 2: testing waitpid(int pid, int* status, int options):\n");

  for (i = 0; i <5; i++) {
    pid_a[i] = fork();
	
    if (pid_a[i] == 0) { // only the child executed this code
     
      
      printf(1, "\n The is child with PID# %d and I will exit with status %d\n", getpid(), 0);
      exit(0);}}
       
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[3]);
      ret_pid = waitpid(pid_a[3], &exit_status);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[1]);
      ret_pid = waitpid(pid_a[1], &exit_status);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[2]);
      ret_pid = waitpid(pid_a[2], &exit_status);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[0]);
      ret_pid = waitpid(pid_a[0], &exit_status);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[4]);
      ret_pid = waitpid(pid_a[4], &exit_status);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      
      return 0;
  }
      
      
int PScheduler(void){
		 
// use this part to test the priority scheduler. Assuming that the priorities range between range between 0 to 63
// 0 is the highest priority. All processes have a default priority of 20 

    int pid, ret_pid, exit_status;
    int i,j,k;
  
    printf(1, "\n  Step 2: testing the priority scheduler and setpriority(int priority)) system call:\n");
    printf(1, "\n  Step 2: Assuming that the priorities range between range between 0 to 63\n");
    printf(1, "\n  Step 2: 0 is the highest priority. All processes have a default priority of 20\n");
    printf(1, "\n  Step 2: The parent processes will switch to priority 0\n");
   
    setpriority( 0, getpid() );
    
    for (i = 0; i <  4; i++) // Original test code: (i = 0; i <  3; i++)
    {
        pid = fork();
        if (pid > 0 )
        {
	    continue;
        }

	else if ( pid == 0)
        {
            if ( i == 0 )	// Lab 01:EC: Give the first child process a low priority to see how pri inheritance plays out.
            {
                setpriority( 60, getpid() );

                for ( j = 0; j < 50000; j++ )
                {
                     for( k = 0; k < 10000; k++ ) 
                     {
                         asm("nop"); 
                     }
                }
            }

	    else
            {
                setpriority( 60-15*i, getpid() ); // Original test code:	 setpriority( 60-20*i, getpid() ); 
            
                for ( j = 0; j < 50000; j++ ) 
                {
                    for( k = 0; k < 10000; k++ ) 
                    {
                        asm("nop"); 
                    }
                }
            }

	    printf(1, "\n child# %d with priority %d has finished! \n",getpid(),60-15*i); // Original test code: last arg was 60-20*i		
		
            exit(0);
        }
        
        else 
        {
            printf(2," \n Error \n");
            exit(-1);
        }
    }

    if(pid > 0)
    {
        for ( i = 0; i <  4; i++ )
        {
            ret_pid = wait(&exit_status);
            //printf(1,"\n This is the parent: child with PID# %d has finished with status %d \n",ret_pid,exit_status);
	}
        
        printf(1,"\n if processes with highest priority finished first then its correct \n");
    }
			
    return 0;
}
*/

#include "types.h"
#include "user.h"

int main(int argc, char *argv[]){

  int i = 500;
  int virtual =(int)&i;
  int physical=0;
  
  printf(1,"\n Testing Part 1: Memory translation system cal: \n system call v2p(int virtual, int *physical) \n\n");
  
  if( v2p(virtual, &physical) == 0 )
	printf(1,"\n Virtual address 0x%x is mapped to physical address 0x%x \n",virtual, physical);
  else
	printf(2,"\n v2p system call failed! \n");
	
   printf(1,"\n An example of correct output:\n Virtual address 0x2FCC is mapped to physical address 0xDEDFFCC  \n");
   printf(1,"\n But it is not a guarantee that the system call is correct. The code will be checked! \n");
  
  //____________________________________________________________________
  
   printf(1,"\n Testing Part 2: Null pointer dereference \n");

   int *p;
   p = &i;

   printf(1,"\n Now we will dereference a proper pointer, we should not get an error\n");

   printf(1,"\n the contents of the proper pointer are %d and it points to address:0x%x\n\n",*p,&p);
   printf(1,"\n We are going to dereference the null pointer now\n");
   p = 0;
   printf(1,"\n Before fixing the null pointer problem we would get an output like this:\n the contents of the null pointer are 0x83E58955 and it points to address: 0x0\n");
   printf(1,"\n The correct output should be:\n pid 3 lab2: trap 14 err 4 on cpu 0 eip 0x10ba addr 0x0--kill proc \n\n");
   
   printf(1,"\n The contents of the null pointer are 0x%x and it points to address: 0x%x\n",*p,p);
  exit(0);
}
