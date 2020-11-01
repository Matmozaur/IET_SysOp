#include <stdio.h> 
#include <stdlib.h> 
  
// definition of the list node
struct Node { 
    double data; 
    struct Node* next; 
};  
  
int main(int argc, char *argv[]) { 
    //size of our node plus size of pointer to that data 
    int node_size = sizeof(struct Node)+8;
    //system allocates 32-bytes blocks of memory so we have to take it into consider
    node_size += 32%node_size;
    struct Node* head = NULL; 
    head = (struct Node*)malloc(sizeof(struct Node)); 
    head->data = 1.0;
    //subtract memory allocate to program without any list
    //(checked in htop can be different in various systems)
    int memory = atoi(argv[1]) - 4504000;
    struct Node* previous = head;
    for(int i=0;i<memory/node_size;i++) {
        struct Node* next = (struct Node*)malloc(sizeof(struct Node));
        next->data = 1.0;
        previous->next = next;
        previous = next;
    }
    printf("Press any key to continue.\n");
    getchar();
    return 0; 
}