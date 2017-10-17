struct stat;
struct rtcdate;

// system calls
int fork(void);
void exit(int status) __attribute__((noreturn)); // Lab 01:1a: Originally "int exit(void) __attribute__((noreturn));"
int wait(int*); 		// Lab 01:1b: Originally "int wait(void);"
int waitpid(int, int*);		// Lab 01:1c: New code.
int pipe(int*);
int write(int, void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(char*, int);
int mknod(char*, short, short);
int unlink(char*);
int fstat(int fd, struct stat*);
int link(char*, char*);
int mkdir(char*);
int chdir(char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
void hello(void);		// Lab 00, added for test system call.
int setpriority(int, int);	// Lab 01:2 Adding priority scheduling.

// ulib.c
int stat(char*, struct stat*);
char* strcpy(char*, char*);
void *memmove(void*, void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, char*, ...);
char* gets(char*, int max);
uint strlen(char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
