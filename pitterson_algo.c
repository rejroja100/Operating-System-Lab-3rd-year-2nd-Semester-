// #include <stdio.h>
// #include <pthread.h>

// int flag[2] = {0, 0};
// int turn;
// int counter = 0;

// void* process0(void* arg)
// {
//     flag[0] = 1;
//     turn = 1;

//     while (flag[1] && turn == 1);

//     // Critical Section
//     counter++;
//     printf("Process 0: Counter = %d\n", counter);

//     flag[0] = 0;

//     return NULL;
// }

// void* process1(void* arg)
// {
//     flag[1] = 1;
//     turn = 0;

//     while (flag[0] && turn == 0);

//     // Critical Section
//     counter++;
//     printf("Process 1: Counter = %d\n", counter);

//     flag[1] = 0;

//     return NULL;
// }

// int main()
// {
//     pthread_t p0, p1;

//     pthread_create(&p0, NULL, process0, NULL);
//     pthread_create(&p1, NULL, process1, NULL);

//     pthread_join(p0, NULL);
//     pthread_join(p1, NULL);

//     return 0;
// }

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

volatile int flag[2] = {0, 0};  // indicates if a process wants to enter
volatile int turn;              // whose turn it is

int counter = 0;  // shared variable (critical section resource)

void* process0(void* arg) {
    for (int i = 0; i < 5; i++) {
        flag[0] = 1;      // I want to enter
        turn = 1;         // but give priority to the other process
        while (flag[1] && turn == 1);  // wait if other wants in and it's their turn

        // ---- critical section ----
        printf("Process 0 in critical section, counter = %d\n", ++counter);
        sleep(2);
        // ---- end critical section ----

        flag[0] = 0;      // done, allow others
    }
    return NULL;
}

void* process1(void* arg) {
    for (int i = 0; i < 5; i++) {
        flag[1] = 1;
        turn = 0;
        while (flag[0] && turn == 0);

        // ---- critical section ----
        printf("Process 1 in critical section, counter = %d\n", ++counter);
        sleep(2);
        // ---- end critical section ----

        flag[1] = 0;
    }
    return NULL;
}

int main() {
    pthread_t t0, t1;

    pthread_create(&t0, NULL, process0, NULL);
    pthread_create(&t1, NULL, process1, NULL);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    return 0;
}