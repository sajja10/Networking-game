#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd;
    struct sockaddr_in server_addr, clientA_addr, clientB_addr;
    socklen_t clientA_len = sizeof(clientA_addr);
    socklen_t clientB_len = sizeof(clientB_addr);
    char bufferA[1024], bufferB[1024];
    
    // Create a UDP socket
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
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

    printf("UDP Server is waiting for clients...\n");

    while (1) {
        // Receive decisions from clientA
        recvfrom(server_fd, bufferA, sizeof(bufferA), 0, (struct sockaddr *)&clientA_addr, &clientA_len);
        printf("Received decision from Client A: %s\n", bufferA);

        // Receive decisions from clientB
        recvfrom(server_fd, bufferB, sizeof(bufferB), 0, (struct sockaddr *)&clientB_addr, &clientB_len);
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
        sendto(server_fd, result, strlen(result), 0, (struct sockaddr *)&clientA_addr, clientA_len);
        sendto(server_fd, result, strlen(result), 0, (struct sockaddr *)&clientB_addr, clientB_len);
        
        // Prompt for another game (simplified)
        char playAgain[10];
        recvfrom(server_fd, playAgain, sizeof(playAgain), 0, (struct sockaddr *)&clientA_addr, &clientA_len);
        recvfrom(server_fd, playAgain, sizeof(playAgain), 0, (struct sockaddr *)&clientB_addr, &clientB_len);
    }

    // Close the socket (this will not be reached in this example)
    close(server_fd);

    return 0;
}
