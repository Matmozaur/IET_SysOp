#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <features.h>

#define LENGTH_NAME 31
#define LENGTH_MSG 101
#define LENGTH_SEND 201

//struktura klienta czatu
typedef struct ClientNode {
    int data;
    struct ClientNode* prev;
    struct ClientNode* next;
    char ip[16];
    char name[31];
} ClientNode;

// Tworzenie nowego klienta
ClientNode *newNode(int sockfd, char* ip) {
    ClientNode *np = (ClientNode *)malloc( sizeof(ClientNode) );
    np->data = sockfd;
    strncpy(np->ip, ip, 16);
    return np;
}

// Zmienne globalne
int server_sockfd = 0, client_sockfd = 0;
ClientNode *root, *now;

// Zamknięcie wszystkich klientów i wyłączenie serwera
void catch_ctrl_c_and_exit(int sig) {
    ClientNode *tmp;
    while (root != NULL) {
        printf("\nClose socketfd: %d\n", root->data);
        close(root->data);
        tmp = root;
        root = root->next;
        free(tmp);
    }
    exit(EXIT_SUCCESS);
}

// Wysłanie do wszystkich uczestników czatu
void send_to_all_clients(ClientNode *np, char tmp_buffer[]) {
    ClientNode *tmp = root->next;
    while (tmp != NULL) {
        if (np->data != tmp->data) { // all clients except itself.
            printf("Send to sockfd %d: \"%s\" \n", tmp->data, tmp_buffer);
            send(tmp->data, tmp_buffer, LENGTH_SEND, 0); //metoda wysyłająca tmp_buffer do odpowiedniego gniazda (<sys/socket.h>)
        }
        tmp = tmp->next;
    }
}

// Funkcja "opiekująca się" konkretnym klientem
void client_handler(void *p_client) {
    int leave_flag = 0;
    char nickname[LENGTH_NAME] = {};
    char recv_buffer[LENGTH_MSG] = {};
    char send_buffer[LENGTH_SEND] = {};
    ClientNode *np = (ClientNode *)p_client;

    strncpy(np->name, nickname, LENGTH_NAME);
    printf("%s(%s)(%d) join the chatroom.\n", np->name, np->ip, np->data);
    sprintf(send_buffer, "%s(%s) join the chatroom.", np->name, np->ip);
    send_to_all_clients(np, send_buffer);

    while (1) {
        if (leave_flag) {
            break;
        }
        int receive = recv(np->data, recv_buffer, LENGTH_MSG, 0);
        if (receive > 0) {
            if (strlen(recv_buffer) == 0) {
                continue;
            }
            sprintf(send_buffer, "%s：%s from %s", np->name, recv_buffer, np->ip);
        } else if (receive == 0 || strcmp(recv_buffer, "exit") == 0) {
            printf("%s(%s)(%d) leave the chatroom.\n", np->name, np->ip, np->data);
            sprintf(send_buffer, "%s(%s) leave the chatroom.", np->name, np->ip);
            leave_flag = 1;
        }
        send_to_all_clients(np, send_buffer);
    }

    // Usuwanie klienta
    close(np->data);
    if (np == now) { 
        now = np->prev;
        now->next = NULL;
    } else { 
        np->prev->next = np->next;
        np->next->prev = np->prev;
    }
    free(np);
}

int main()
{
    // Łapanie sygnałów
    signal(SIGINT, catch_ctrl_c_and_exit);

    // Utworzenie gniazda serwera
    server_sockfd = socket(AF_INET , SOCK_STREAM , 0);

    // Przygotowanie serwera
    struct sockaddr_in server_info, client_info;
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);
    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);
    server_info.sin_family = PF_INET;
    server_info.sin_addr.s_addr = INADDR_ANY;
    server_info.sin_port = htons(8888);

    // Rozpoczęcie nasłuchowania
    bind(server_sockfd, (struct sockaddr *)&server_info, s_addrlen);
    listen(server_sockfd, 5);

    // Wyświetlenie IP
    getsockname(server_sockfd, (struct sockaddr*) &server_info, (socklen_t*) &s_addrlen);
    printf("Start Server on: %s:%d\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));

    // Przygotowanie listy klientów
    root = newNode(server_sockfd, inet_ntoa(server_info.sin_addr));
    now = root;

    while (1) {
        // Zaakceptowanie połączenia
        client_sockfd = accept(server_sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);

        // Wypisanie IP klienta
        getpeername(client_sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);
        printf("Client %s:%d come in.\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

        // Dodanie klienta do listy
        ClientNode *c = newNode(client_sockfd, inet_ntoa(client_info.sin_addr));
        c->prev = now;
        now->next = c;
        now = c;

        pthread_t id;
        pthread_create(&id, NULL, (void *)client_handler, (void *)c);
    }

    return 0;
}