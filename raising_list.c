#include <stdio.h> 
#include <stdlib.h> 
  
struct Node { 
    double data; 
    struct Node* next; 
};  
  
int main(int argc, char *argv[]) { 
    int node_size = sizeof(struct Node)+8;
    node_size += 32%node_size;
    struct Node* head = NULL; 
    head = (struct Node*)malloc(sizeof(struct Node)); 
    head->data = 1.0;

    int memory = atoi(argv[1]) - 4504000;
    struct Node* previous = head;
    for(int i=0;i<memory/node_size;i++) {
        struct Node* next = (struct Node*)malloc(sizeof(struct Node));
        next->data = 1.0;
        previous->next = next;
        previous = next;
    }
    printf("Press any key to continue.\n");
    // char c;
    // scanf("%c\n", &c); 
    getchar();
    return 0; 
}