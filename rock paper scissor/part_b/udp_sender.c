// UDP Sender (Client) Program:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>

#define MAX_CHUNK_SIZE 256
#define NUM_CHUNKS 5  // Change as needed

// Define a custom packet structure for data chunks
struct ChunkPacket {
    int sequence_number;
    char data[MAX_CHUNK_SIZE];
};

int main() {
    int sender_fd;
    struct sockaddr_in receiver_addr;
    socklen_t receiver_len = sizeof(receiver_addr);

    // Create a UDP socket
    if ((sender_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Initialize receiver address structure
    memset(&receiver_addr, 0, sizeof(receiver_addr));
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(12345); // Receiver's port number
    receiver_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Receiver's IP

    // Send the total number of chunks
    int total_chunks = NUM_CHUNKS;
    sendto(sender_fd, &total_chunks, sizeof(total_chunks), 0, (struct sockaddr *)&receiver_addr, receiver_len);

    srand(time(NULL));

    for (int i = 0; i < NUM_CHUNKS; i++) {
        struct ChunkPacket packet;
        packet.sequence_number = i;

        // Simulate data (replace with your data source)
        snprintf(packet.data, sizeof(packet.data), "Chunk %d Data", i);

        // Send the data packet
        sendto(sender_fd, &packet, sizeof(packet), 0, (struct sockaddr *)&receiver_addr, receiver_len);

        // Simulate lost ACKs (remove in the final version)
        if (i % 3 != 0) {
            printf("Sent chunk %d, waiting for ACK...\n", i);
            sleep(1);  // Simulate waiting for ACK
        }
    }

    // Close the socket
    close(sender_fd);

    return 0;
}
