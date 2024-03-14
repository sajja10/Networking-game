#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char decision[50], playAgain[10];

    // Create a UDP socket
    if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345); // Server's port number
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server's IP

    while (1) {
        // Input decision (Rock, Paper, or Scissors)
        printf("Enter your decision (Rock, Paper, or Scissors): ");
        fgets(decision, sizeof(decision), stdin);
        decision[strcspn(decision, "\n")] = '\0';

        // Send decision to the server
        sendto(client_fd, decision, strlen(decision), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

        // Receive and display the result
        char result[50];
        recvfrom(client_fd, result, sizeof(result), 0, NULL, NULL);
        printf("Result: %s\n", result);

        // Prompt for another game
        printf("Do you want to play again? (yes/no): ");
        fgets(playAgain, sizeof(playAgain), stdin);
        playAgain[strcspn(playAgain, "\n")] = '\0';
        sendto(client_fd, playAgain, strlen(playAgain), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

        if (strcmp(playAgain, "no") == 0) {
            break;
        }
    }

    // Close the socket
    close(client_fd);

    return 0;
}
