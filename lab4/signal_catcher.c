#include <sys/types.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
  
void catch_signal(int signal) {
    printf("Recived signal: %d, but continue working\n ", signal);
} 
  
int main(int argc, char *argv[]) {
    int i;
    printf("pid ofprocess: %d\n", getpid());
    for( i  = 1; i  < 64; i ++ ) {
        signal(i, catch_signal);
    }
    while(1) {
        printf("working");
        sleep(1000);
    }
    return 0;
}
