#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + N - 1) % N
#define RIGHT (phnum + 1) % N

int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };

pthread_mutex_t mutex;
pthread_cond_t cond[N];

void test(int phnum)
{
    if (state[phnum] == HUNGRY
        && state[LEFT] != EATING
        && state[RIGHT] != EATING) {
        // state that eating
        state[phnum] = EATING;

        sleep(2);

        printf("Philosopher %d takes fork %d and %d\n",
                      phnum + 1, LEFT + 1, phnum + 1);

        printf("Philosopher %d is Eating\n", phnum + 1);

        // signal to wake up hungry philosophers
        pthread_cond_signal(&cond[phnum]);
    }
}

// take up chopsticks
void take_fork(int phnum)
{
    pthread_mutex_lock(&mutex);

    // state that hungry
    state[phnum] = HUNGRY;

    printf("Philosopher %d is Hungry\n", phnum + 1);

    // eat if neighbours are not eating
    test(phnum);

    while (state[phnum] != EATING) {
        pthread_cond_wait(&cond[phnum], &mutex);
    }

    pthread_mutex_unlock(&mutex);

    sleep(1);
}

// put down chopsticks
void put_fork(int phnum)
{
    pthread_mutex_lock(&mutex);

    // state that thinking
    state[phnum] = THINKING;

    printf("Philosopher %d putting fork %d and %d down\n",
           phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is thinking\n", phnum + 1);

    test(LEFT);
    test(RIGHT);

    pthread_mutex_unlock(&mutex);
}

void* philosopher(void* num)
{
    while (1) {
        int* i = num;

        sleep(1);

        take_fork(*i);

        sleep(0);

        put_fork(*i);
    }
}

int main()
{
    int i;
    pthread_t thread_id[N];

    // initialize the mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < N; i++)
        pthread_cond_init(&cond[i], NULL);

    // create philosopher threads
    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    // join philosopher threads
    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    // destroy mutex and condition variables
    pthread_mutex_destroy(&mutex);
    for (i = 0; i < N; i++)
        pthread_cond_destroy(&cond[i]);

    return 0;
}