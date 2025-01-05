#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main() {
    pid_t pid;
    const char *filename = "pids.txt";
    int fd;

    // Create the file with write-only permission
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("File open failed");
        return 1;
    }

    pid = fork();  // Create a child process

    if (pid == -1) {
        // Error in fork
        perror("Fork failed");
        close(fd);
        return 1;
    }

    if (pid == 0) {
        // Child process
        dprintf(fd, "Child PID: %d\n", getpid());
        printf("Child process written its PID to the file.\n");
    } else {
        // Parent process
        dprintf(fd, "Parent PID: %d\n", getpid());
        printf("Parent process written its PID to the file.\n");

        // Wait for child to finish
        wait(NULL);
    }

    // Close the file after writing
    close(fd);
    return 0;
}
