#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char decision[50], playAgain[10];

    // Create a TCP socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345); // Server's port number
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server's IP

    // Connect to the server
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(1);
    }

    while (1) {
        // Input decision (Rock, Paper, or Scissors)
        printf("Enter your decision (Rock, Paper, or Scissors): ");
        fgets(decision, sizeof(decision), stdin);
        decision[strcspn(decision, "\n")] = '\0';

        // Send decision to the server
        if (send(client_fd, decision, strlen(decision), 0) == -1) {
            perror("send");
            exit(1);
        }

        // Receive and display the result
        char result[50];
        if (recv(client_fd, result, sizeof(result), 0) == -1) {
            perror("recv");
            exit(1);
        }
        printf("Result: %s\n", result);

        // Prompt for another game
        printf("Do you want to play again? (yes/no): ");
        fgets(playAgain, sizeof(playAgain), stdin);
        playAgain[strcspn(playAgain, "\n")] = '\0';

        if (send(client_fd, playAgain, strlen(playAgain), 0) == -1) {
            perror("send");
            exit(1);
        }

        if (strcmp(playAgain, "no") == 0) {
            break;
        }
    }

    // Close the socket
    close(client_fd);

    return 0;
}
