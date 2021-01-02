#include <sys/types.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
  
  
int main(int argc, char *argv[]) {
    // memory allocation (static and dynamic) and opening a file
    FILE *fp;
    fp  = fopen ("data.txt", "w");
    static int c[1024*1024*1024/4];
    malloc(1024*1024*1024);
    /* fork a child process */
    pid_t pid = fork();
    if (pid < 0) { /* error occurred */ 
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if (pid == 0) { /* child process */ 
        // memory allocation for testing resource management
        static int d[1024*1024*1024/16];
        malloc(1024*1024*1024/2);
        printf("pid of child from child: %d\n", getpid());
        printf("pid of parent from child: %d\n", getppid());
        printf("Provide number child.\n");
        int x;
        scanf("%d", &x);
         printf("First scanned from child %d\n", x);
    }
    else { /* parent process */
        /* parent will wait for the child to complete */ 
        // static int d[1024*1024*1024/16];
        // malloc(1024*1024*1024/2);
        printf("pid of parent from parent: %d\n", getpid());
        printf("pid of child from parent: %d\n", pid);
        printf("Provide number parent.\n");
        int z;
        scanf("%d", &z);
         printf("First scanned from parent %d\n", z);
        fclose (fp);
        wait(NULL);
        printf("Provide number parent.\n");
        scanf("%d", &z);
        printf("Secound scanned from parent %d\n", z);
        return 0;
    }
    if(pid == 0) { /* child process */ 
        printf("Child running\n");
        int y;
        printf("Provide number.\n");
        scanf("%d", &y);
        printf("Secound scanned from child %d\n", y);
    }
    return 0;
}
