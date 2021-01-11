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

#define LENGTH_NAME 31
#define LENGTH_MSG 101
#define LENGTH_SEND 201

// Zmienne globalne
int sockfd = 0;
char nickname[LENGTH_NAME] = {};

// Obsługa odebranej wiadomości 
void recv_msg_handler() {
    char receiveMessage[LENGTH_SEND] = {};
    while (1) {
        int receive = recv(sockfd, receiveMessage, LENGTH_SEND, 0);
        if (receive > 0) {
            printf("\r%s\n", receiveMessage);
        } else if (receive == 0) {
            break;
        }
    }
}

// Wysyłanie wiadomości
void send_msg_handler() {
    char message[LENGTH_MSG] = {};
    while (1) {
        while (fgets(message, LENGTH_MSG, stdin) != NULL) {
            if (strlen(message) == 0) {
            } else {
                break;
            }
        }
        send(sockfd, message, LENGTH_MSG, 0);
        if (strcmp(message, "exit") == 0) {
            break;
        }
    }
}

int main()
{
    printf("Please enter your name: ");
    fgets(nickname, LENGTH_NAME, stdin);

    if (strlen(nickname) < 2 || strlen(nickname) >= LENGTH_NAME-1) {
        printf("\nName must be more than one and less than thirty characters.\n");
        exit(EXIT_FAILURE);
    }

    // Utworzenie socketa
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    // Zapisanie informacji o serwerze
    struct sockaddr_in server_info, client_info;
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);
    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);
    server_info.sin_family = PF_INET;
    server_info.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_info.sin_port = htons(8888);

    // Połączenie z serwerem
    connect(sockfd, (struct sockaddr *)&server_info, s_addrlen);
    
    getsockname(sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);
    getpeername(sockfd, (struct sockaddr*) &server_info, (socklen_t*) &s_addrlen);
    printf("Connect to Server: %s:%d\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));
    printf("You are: %s:%d\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

    send(sockfd, nickname, LENGTH_NAME, 0);

    pthread_t send_msg_thread;
    pthread_create(&send_msg_thread, NULL, (void *) send_msg_handler, NULL);

    pthread_t recv_msg_thread;
    pthread_create(&recv_msg_thread, NULL, (void *) recv_msg_handler, NULL);

    while (1) {
        continue;
    }

    close(sockfd);
    return 0;
}