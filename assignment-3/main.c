#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int pid = fork();
    if (pid == 0) {
        char *env[1] = {0};
        char *argv[1] = {"./writer"};
        execve("/bin/bash", argv, env);
    } else if (pid < 0) {
        printf("fork failed with error code %d\n", pid);
        exit(-1);
    }
    int status;
    wait(&status);
    printf("child pid was %d, it exited with %d\n", pid, status);

    int pid2 = fork();
    if (pid2 == 0) {
        char *env[1] = {0};
        char *argv[1] = {"./reader"};
        execve("/bin/bash", argv, env);
    } else if (pid2 < 0) {
        printf("fork failed with error code %d\n", pid2);
        exit(-1);
    }
    int status2;
    wait(&status2);
    printf("child pid was %d, it exited with %d\n", pid2, status2);
}