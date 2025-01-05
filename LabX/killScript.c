#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void signal_handler(int signum) {
    // Handler to respond to the signal
    if (signum == SIGUSR1) {
        printf("Child received SIGUSR1 signal from parent\n");
    }
}

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid == -1) {
        // Error in fork
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        // Set up a signal handler for SIGUSR1
        signal(SIGUSR1, signal_handler);

        // Wait for a signal from the parent
        printf("Child is waiting for signal...\n");
        while(1);  // Keep the child process alive to wait for the signal
    } else {
        // Parent process
        sleep(2);  // Allow child to set up signal handler
        printf("Parent is sending SIGUSR1 signal to child...\n");
        kill(pid, SIGUSR1);  // Send the signal to the child process

        // Wait for child to handle the signal
        sleep(2);
        printf("Parent has sent the signal and is now exiting.\n");
    }

    return 0;
}
