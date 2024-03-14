#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char message[] = "Hello, Server!";

    // Create a TCP socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345); // Port number
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP

    // Connect to the server
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(1);
    }

    // Send data to the server
    if (send(client_fd, message, strlen(message), 0) == -1) {
        perror("send");
        exit(1);
    }

    printf("Message sent to server: %s\n", message);

    // Close the socket
    close(client_fd);

    return 0;
}
