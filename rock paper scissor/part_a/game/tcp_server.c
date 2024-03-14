#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {
    int server_fd, clientA_fd, clientB_fd;
    struct sockaddr_in server_addr, clientA_addr, clientB_addr;
    socklen_t clientA_len = sizeof(clientA_addr);
    socklen_t clientB_len = sizeof(clientB_addr);
    char bufferA[1024], bufferB[1024];
    
    // Create a TCP socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345); // Port number
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_fd, 2) == -1) { // Maximum of 2 clients
        perror("listen");
        exit(1);
    }

    printf("TCP Server is waiting for clients...\n");

    // Accept clientA connection
    if ((clientA_fd = accept(server_fd, (struct sockaddr *)&clientA_addr, &clientA_len)) == -1) {
        perror("accept");
        exit(1);
    }

    printf("Client A connected\n");

    // Accept clientB connection
    if ((clientB_fd = accept(server_fd, (struct sockaddr *)&clientB_addr, &clientB_len)) == -1) {
        perror("accept");
        exit(1);
    }

    printf("Client B connected\n");

    while (1) {
        // Receive decisions from clientA
        if (recv(clientA_fd, bufferA, sizeof(bufferA), 0) == -1) {
            perror("recv");
            exit(1);
        }
        printf("Received decision from Client A: %s\n", bufferA);

        // Receive decisions from clientB
        if (recv(clientB_fd, bufferB, sizeof(bufferB), 0) == -1) {
            perror("recv");
            exit(1);
        }
        printf("Received decision from Client B: %s\n", bufferB);

        // Decide the result (simplified)
        char result[50];
        if (strcmp(bufferA, bufferB) == 0) {
            strcpy(result, "Draw");
        } else if ((strcmp(bufferA, "Rock") == 0 && strcmp(bufferB, "Scissors") == 0) ||
                   (strcmp(bufferA, "Paper") == 0 && strcmp(bufferB, "Rock") == 0) ||
                   (strcmp(bufferA, "Scissors") == 0 && strcmp(bufferB, "Paper") == 0)) {
            strcpy(result, "Client A Wins!");
        } else {
            strcpy(result, "Client B Wins!");
        }

        // Send the result to both clients
        if (send(clientA_fd, result, strlen(result), 0) == -1) {
            perror("send");
            exit(1);
        }
        if (send(clientB_fd, result, strlen(result), 0) == -1) {
            perror("send");
            exit(1);
        }
        
        // Prompt for another game (simplified)
        char playAgain[10];
        if (recv(clientA_fd, playAgain, sizeof(playAgain), 0) == -1) {
            perror("recv");
            exit(1);
        }
        if (recv(clientB_fd, playAgain, sizeof(playAgain), 0) == -1) {
            perror("recv");
            exit(1);
        }

        if (strcmp(playAgain, "no") == 0) {
            break;
        }
    }

    // Close client sockets
    close(clientA_fd);
    close(clientB_fd);

    // Close the server socket
    close(server_fd);

    return 0;
}
