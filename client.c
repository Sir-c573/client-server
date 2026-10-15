
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 3000
#define SIZE 1024

int main()
{
    int client_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock_fd == -1) {
        perror("Socket creation failed!");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr = {0};
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;

    int c = connect(client_sock_fd,
                    (struct sockaddr*)&addr, sizeof(addr));
    if (c == -1) {
        perror("Connect failed!");
        close(client_sock_fd);
        exit(EXIT_FAILURE);
    }

    char expression[SIZE];
    printf("Input your mathematical expression -> ");
    fflush(stdout);

    if (fgets(expression, SIZE, stdin) == NULL) {
        perror("Input failed!");
        close(client_sock_fd);
        exit(EXIT_FAILURE);
    }

    ssize_t bytes = send(client_sock_fd, expression,
                         strlen(expression), 0);
    if (bytes == -1) {
        perror("Send failed!");
        close(client_sock_fd);
        exit(EXIT_FAILURE);
    }

    char buffer_recv[SIZE];
    ssize_t bytes_recv = recv(client_sock_fd,
                              buffer_recv,
                              sizeof(buffer_recv) - 1, 0);

    if (bytes_recv > 0) {
        buffer_recv[bytes_recv] = '\0';
        printf("Server response: %s", buffer_recv);
    } else if (bytes_recv == 0) {
        printf("Server closed the connection.\n");
    } else {
        perror("Receive failed!");
    }

    close(client_sock_fd);
    return 0;
}
