#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    // Loop to fork 3 times
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid < 0) { // Error handling
            perror("fork failed");
            return 1;
        }

        if (pid == 0) { // Child process
            printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
            break;
        }
    }

    // Parent process waits a bit to ensure output order
    sleep(1);
    return 0;
}

