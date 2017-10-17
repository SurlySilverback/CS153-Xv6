#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  int status;		// Lab 01a: New line.
  argint(0, &status);	// Lab 01a: New line.
  exit(status);		// Lab 01a: Originally "exit(0);"

  return 0;  // not reached
}

int
sys_wait(void)
{
  int* status;				// Lab 01:1b: New line
  argptr(0, (char**)&status, 0);	// Lab 01:1b: New line
  return wait(status);  		// Lab 01:1b: Originally "return wait(0);"
}

int
sys_waitpid(void)			// Lab 01:1c: New function
{
  int pid;
  argint(0, &pid);
  int* status;
  argptr(1, (char**)&status, 0);
  return waitpid(pid, status);
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// Lab 00, added for test system call
int
sys_hello(void)
{
    hello();
    
    return 0;
}

// Lab 01:2, new function.
int
sys_setpriority()
{
    int pid;
    argint(0, &pid);

    int priority;
    argint(1, &priority);

    return setpriority(priority, pid);
}


// Lab 02:01 System call taking a virtual address and returning its physical address.
int sys_v2p(void)
{
    int virtual;
    int *physical;
    argint( 0, &virtual );
    argptr( 1, (char**)&physical, 0 );

    return v2p( virtual, physical );
}
