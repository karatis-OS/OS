#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
    pid_t pid;
    int fd;
    
    // Open the file in write mode (create if not exists, truncate if exists)
    fd = open("pids.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) { // Fork error
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        // Write the child PID to the file
        dprintf(fd, "Child Process PID: %d\n", getpid());
        printf("Child process started. PID = %d\n", getpid());
    } else { // Parent process
        // Write the parent PID to the file
        dprintf(fd, "Parent Process PID: %d\n", getpid());
        printf("Parent process started. PID = %d\n", getpid());
    }

    // Close the file descriptor
    close(fd);

    return 0;
}

