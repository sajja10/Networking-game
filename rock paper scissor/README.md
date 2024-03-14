# PART A
## Basic
In this, i just implemented a basic connection in TCP and another in UDP.

## Game(Rock-paper-scissor)
#### TCP Implementation:
Created a TCP server that listens for connections from two clients on different ports.
Developed TCP client programs, clientA and clientB, where users can input their choices (Rock, Paper, or Scissors).
Implemented error handling by checking the return status of relevant functions.
Upon receiving inputs from both clients, the server deliberates and sends back the judgment (Win, Lost, or Draw).
Clients display the judgment and prompt for another game, looping until both clients agree.

#### UDP Implementation:
Developed a UDP server to handle communication between two clients.
Created UDP client programs, clientA and clientB, similar to the TCP version.
Implemented error checking for all relevant functions.
The rest of the process remains the same as in the TCP implementation: sending choices, receiving judgments, displaying results, and prompting for another game.

# PART B
#### Functionalities that you have to implement are (10 marks):

Data Sequencing: The sender (client or server - both should be able to send as well as receive data) must divide the data (assume some text) into smaller chunks (using chunks of fixed size or using a fixed number of chunks). Each chunk is assigned a number which is sent along with the transmission (use structs). The sender should also communicate the total number of chunks being sent . After the receiver has data from all the chunks, it should aggregate them according to their sequence number and display the text.
Retransmissions: The receiver must send an ACK packet for every data chunk received (The packet must reference the sequence number of the received chunk). If the sender doesn’t receive the acknowledgement for a chunk within a reasonable amount of time (say 0.1 seconds), it must resend the data. However, the sender shouldn’t wait for receiving acknowledgement for a previously sent chunk before transmitting the next chunk .
