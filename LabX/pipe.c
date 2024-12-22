#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h> // For waitpid()

// Signal handler for the child process
void signal_handler(int sig) {
    printf("Child received signal: %d\n", sig);
}

int main() {
    int pipe_fd[2]; 
    pid_t pid;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) { // Fork error
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        close(pipe_fd[1]); // Close the write end of the pipe
        signal(SIGUSR1, signal_handler); // Register signal handler

        char buffer[1];
        // Wait to read a byte from the pipe
        if (read(pipe_fd[0], buffer, 1) > 0) {
            kill(getpid(), SIGUSR1); // Trigger the signal
        }
        close(pipe_fd[0]); // Close the read end
    } else { // Parent process
        close(pipe_fd[0]); // Close the read end of the pipe

        printf("Parent sending a signal to the child...\n");
        sleep(2); // Simulate some delay
        write(pipe_fd[1], "1", 1); // Send a byte through the pipe
        close(pipe_fd[1]); // Close the write end
        waitpid(pid, NULL, 0); // Wait for the child process to finish
        printf("Child process terminated.\n");
    }

    return 0;
}

