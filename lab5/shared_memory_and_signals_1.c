#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 
#include <unistd.h> 

int commonkey = 950806;
  
struct shared_memory { 
    char buff[100]; 
    int pid1, pid2; 
}; 
  
struct shared_memory* sm; 
  
void recive_signal(int signal) { 
    printf("Message from user2: "); 
    puts(sm->buff); 
} 
  
int main() { 
    int pid = getpid(); 
    int smid; 
  
    // create and attach shared memory 
    smid = shmget(commonkey, sizeof(struct shared_memory),IPC_CREAT | S_IRUSR | S_IWUSR | 0777); 
    sm = (struct shared_memory*)shmat(smid, NULL, 0); 
  
    // pass pid to shared memory
    sm->pid1 = pid; 
  
    // deal with signal 
    signal(SIGUSR2, recive_signal);
    signal(SIGUSR1, recive_signal); 
  
    while (1) { 
        sleep(1); 
        fgets(sm->buff, 100, stdin); 
        kill(sm->pid2, SIGUSR2); 
    } 

    //detach and remove shared memory
    shmdt((void*)sm); 
    shmctl(smid, IPC_RMID, NULL); 

    return 0; 
} 
