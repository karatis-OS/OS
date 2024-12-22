#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h> 

// Signal handler for the child process
void handle_signal(int sig) {
    if (sig == SIGUSR1) {
        printf("Child process received SIGUSR1 from parent.\n");
    }
}

int main() {
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid < 0) { // Fork error
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        printf("Child process started. PID = %d\n", getpid());

        // Register signal handler for SIGUSR1
        signal(SIGUSR1, handle_signal);

        // Wait for a signal indefinitely
        pause();

        printf("Child process exiting.\n");
    } else { // Parent process
        printf("Parent process. PID = %d, Child PID = %d\n", getpid(), pid);

        // Sleep for 2 seconds to ensure the child is ready
        sleep(2);

        printf("Parent sending SIGUSR1 to child.\n");
        if (kill(pid, SIGUSR1) == -1) {
            perror("kill failed");
            exit(EXIT_FAILURE);
        }

        // Wait for the child to finish
        wait(NULL);
        printf("Parent process exiting.\n");
    }

    return 0;
}

