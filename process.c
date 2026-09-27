// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <stdlib.h>

// int main() {
//     pid_t pid;

//     printf("Parent PID: %d\n", getpid());

//     pid = fork();

//     if (pid < 0) {
//         printf("Fork failed\n");
//         return 1;
//     }

//     if (pid == 0) {
//         printf("\n--- Child Process ---\n");
//         printf("Child PID: %d\n", getpid());
//         printf("Child PPID: %d\n", getppid());
//         printf("Child is running...\n");
//         sleep(3);
//         printf("Child terminated.\n");
//         exit(0);
//     } else {
//         printf("\n--- Parent Process ---\n");
//         printf("Child PID: %d\n", pid);
//         printf("Parent is running...\n");
//         wait(NULL);
//         printf("Parent terminated.\n");
//     }

//     return 0;
// }


// #include<stdio.h>
// #include<unistd.h>
// #include<sys/wait.h>
// #include<stdlib.h>

// int main(){
//     pid_t pid;


//     printf("parent id : %d\n", getpid());
//     pid = fork();

//     if(pid < 0){
//         printf("\nFork failed\n");
//     }


//     if(pid == 0){
//         printf("--------- Child ----------\n");

//         printf("\nChild Pid : %d\n", getpid());
//         printf("\nChild p pid : %d\n", getppid());
//         printf("child pid runing.\n");
//         sleep(5);
//         printf("\nchild pid running\n");
//         printf("child id terminated.\n");
//         exit(0);
//     }
//     else{
//         printf("--------- Parents ----------\n");

//         printf("\nParent Pid : %d\n", getpid());
//         printf("\nParent p pid : %d\n", getppid());
//         printf("Parent pid runing.\n");
//         sleep(5);
//         printf("\nParent pid running\n");
//         printf("Parent id terminated.\n");
//     }

//     return 0;
// }

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    printf("Parent PID (before fork): %d\n", getpid());

    pid = fork();

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        exit(1);
    }
    else if (pid == 0) {
        // Child process
        printf("\nChild PID: %d\n", getpid());
        printf("Child's Parent PID: %d\n", getppid());

        printf("Numbers 6 to 10 from child process:\n");
        for (int i = 6; i <= 10; i++) {
            printf("%d ", i);
        }
        printf("\n");

        exit(0);
    }
    else {
        // Parent process
        printf("\nParent PID: %d\n", getpid());

        printf("Numbers 1 to 5 from parent process:\n");
        for (int i = 1; i <= 5; i++) {
            printf("%d ", i);
        }
        printf("\n");

        wait(NULL); // wait for child to finish before parent exits
    }

    return 0;
}