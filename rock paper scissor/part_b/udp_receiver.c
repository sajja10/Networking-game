#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>

#define MAX_CHUNK_SIZE 256
#define NUM_CHUNKS 5  // Define the number of chunks (adjust as needed)

// Define a custom packet structure for data chunks
struct ChunkPacket {
    int sequence_number;
    char data[MAX_CHUNK_SIZE];
};

int main() {
    int receiver_fd;
    struct sockaddr_in sender_addr;
    socklen_t sender_len = sizeof(sender_addr);

    // Create a UDP socket
    if ((receiver_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Initialize sender address structure
    memset(&sender_addr, 0, sizeof(sender_addr));
    sender_addr.sin_family = AF_INET;
    sender_addr.sin_port = htons(12345); // Sender's port number
    // sender_addr.sin_addr.s_addr = INADDR_ANY;
    sender_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use localhost



    return 0;
}
