
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define IP INADDR_ANY
#define PORT 3000
#define SIZE 1024

double evaluate_string_expression(const char* expr, int* valid)
{
    double num1 = 0;
    double num2 = 0;
    char op;

    *valid = 1;

    if (sscanf(expr, " %lf %c %lf", &num1, &op, &num2) != 3) {
        *valid = 0;
        return 0;
    }

    switch (op) {
        case '+':
            return num1 + num2;

        case '*':
            return num1 * num2;

        case '-':
            return num1 - num2;

        case '/':
            if (num2 == 0) {
                *valid = 0;
                return 0;
            }
            return num1 / num2;

        case '%':
            if (num2 == 0 ||
                num1 != (int)num1 ||
                num2 != (int)num2) {
                *valid = 0;
                return 0;
            }
            return (int)num1 % (int)num2;

        default:
            *valid = 0;
            return 0;
    }
}

int main()
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR,
               &opt, sizeof(opt));

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(IP);

    if (bind(sock_fd, (struct sockaddr*)&addr,
             sizeof(addr)) == -1) {
        perror("Bind failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    if (listen(sock_fd, SOMAXCONN) == -1) {
        perror("Listen failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr_client = {0};
    socklen_t len = sizeof(addr_client);

    int conn_sock = accept(sock_fd,
                           (struct sockaddr*)&addr_client,
                           &len);

    if (conn_sock == -1) {
        perror("Accept failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    char buffer1[SIZE] = {0};

    ssize_t bytes_received = recv(conn_sock, buffer1,
                                  sizeof(buffer1) - 1, 0);

    if (bytes_received <= 0) {
        if (bytes_received == -1) {
            perror("Receive failed");
        }
        close(conn_sock);
        close(sock_fd);
        return EXIT_FAILURE;
    }

    buffer1[bytes_received] = '\0';

    int valid = 0;
    double result = evaluate_string_expression(buffer1, &valid);

    char buf_for_client[SIZE];

    if (valid) {
        printf("Expression: %s", buffer1);
        printf("Result: %lf\n", result);

        snprintf(buf_for_client, sizeof(buf_for_client),
                 "Result: %lf\n", result);
    } else {
        printf("Invalid expression: %s", buffer1);

        snprintf(buf_for_client, sizeof(buf_for_client),
                 "ERROR: Invalid expression or division by zero.\n");
    }

    /* Send the response through the connected client socket. */
    if (send(conn_sock, buf_for_client,
             strlen(buf_for_client), 0) == -1) {
        perror("Sending failed");
    }

    close(conn_sock);
    close(sock_fd);

    return 0;
}
