#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2]; // File descriptors for the pipe: fd[0] for reading, fd[1] for writing

    // Create a pipe for communication
    if (pipe(fd) == -1) {
        perror("Pipe failed"); // Print error message if pipe creation fails
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork(); // Create a new process
    if (pid < 0) {
        perror("Fork failed"); // Print error message if fork fails
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        close(fd[1]); // Close unused write end of the pipe

        char buffer[100]; // Buffer to store the message from the parent
        read(fd[0], buffer, sizeof(buffer)); // Read message from the pipe
        printf("Child process received: %s\n", buffer); // Print the received message

        close(fd[0]); // Close the read end of the pipe after reading
    } else {
        // Parent process
        close(fd[0]); // Close unused read end of the pipe

        char message[] = "Hello from parent"; // Message to send to the child
        write(fd[1], message, strlen(message) + 1); // Write the message to the pipe

        close(fd[1]); // Close the write end of the pipe after writing
        wait(NULL); // Wait for the child process to finish execution
    }

    return 0; // Exit the program
}
