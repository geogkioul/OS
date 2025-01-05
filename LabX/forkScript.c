#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            printf("Child process: PID = %d\n", getpid());
            exit(0);
        } else {
            // Parent process
            printf("Parent process: PID = %d created child with PID = %d\n", getpid(), pid);
        }
    }
    return 0;
}
