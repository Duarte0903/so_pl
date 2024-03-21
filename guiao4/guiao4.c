#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int exec1(int arg_num) {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        close(fd[1]);

        int num;

        while (read(fd[0], &num, sizeof(int)) > 0) {
            printf("Received: %d\n by child process", num);
        }

        close(fd[0]);

        exit(0);
    }

    else {
        close(fd[0]);

        int num = arg_num;

        sleep(5);

        write(fd[1], &num, sizeof(int));

        printf("Sent: %d\n", num);

        close(fd[1]);
    }

    return 0;
}

int exec2(int arg_num) {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        close(fd[0]);

        int num = arg_num;

        write(fd[1], &num, sizeof(int));

        printf("Sent: %d by child process\n", num);

        close(1);
    }

    else {
        close(fd[1]);

        int num;

        while (read(fd[0], &num, sizeof(int)) > 0) {
            printf("Received: %d\n", num);
        }

        close(fd[0]);
    }

    return 0;
}

int exec2_1() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        close(fd[0]);

        int nums[] = {1, 2, 3, 4, 5};

        for (int i = 0; i < 5; i++) {
            write(fd[1], &nums[i], sizeof(int));
            printf("Sent: %d by child process\n", nums[i]);
        }

        close(1);
    }

    else {
        close(fd[1]);

        int num;

        sleep(2);

        while (read(fd[0], &num, sizeof(int)) > 0) {
            printf("Received: %d\n", num);
        }

        close(fd[0]);
    }

    return 0;

}

int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "1") == 0) {
        exec1(atoi(argv[2]));
    }

    if (strcmp(argv[1], "2") == 0) {
        exec2(atoi(argv[2]));
    }

    if (strcmp(argv[1], "2_1") == 0) {
        exec2_1();
    }

    return 0;
}